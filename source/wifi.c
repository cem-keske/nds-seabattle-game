#include "wifi.h"
#include <stdio.h>

const char PAIRING_REQ = 0x01;
const char PAIRING_ACK = 0x02;
const char READY = 0x03;

bool connect_wifi(){
	if(initWiFi() && openSocket())
		printf("Connected to WiFi! \n\n");
	return true;
}


/**
 * Sends a pairing packet
 */
void send_pairing_packet(){
	char msg[1] = {PAIRING_REQ};
	sendData(msg,1);
	printf("Sent a pairing packet! \n\n");
}

/**
 * Waits for a pairing packet to arrive, if the pairing packet arrives, prints it
 * and responds with a pairing packet.
 */
void wait_pairing_packet(){
	printf("Waiting for pairing packet! \n\n");
	while(1){
		char msg[1];

		if(receiveData(msg, 1) > 0){
			//a message is received
			if(msg[0] == PAIRING_REQ){
				printf("Received a pairing request! \n\n");
				msg[0] = PAIRING_ACK;
				sendData(msg, 1);
				printf("Sent pairing ACK! \n\n");
				printf("Pairing successful! \n\n");
				break;
			} else if(msg[0] == PAIRING_ACK) {
				printf("Received pairing ACK! \n\n Pairing succesful. \n\n");
				break;
			}
		}
	swiWaitForVBlank();
	}
}
void send_ready_packet(){
	char msg[1] = {READY};
		sendData(msg,1);
}
bool ready_packet_received(){
	char msg[1];
	if(receiveData(msg, 1) > 0)
		if(msg[0] == READY)
			return true;
	return false;
}

