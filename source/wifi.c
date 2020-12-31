#include "wifi.h"
#include <stdio.h>

const char PAIRING_REQ = 0x01;
const char PAIRING_ACK = 0x02;
const char READY = 0x03;
const char SHIP_PLACED = 0x04;

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

/**
 * Sends a packet informing the opponent that a ship was placed.
 */
void send_ship_placed(unsigned char ship_nbr){
	char msg[2];
	msg[0] = SHIP_PLACED;
	msg[1] = ship_nbr;
	sendData(msg,2);
}


/**
 * Receive a packet from the opponent informing that a ship was placed.
 * \return The number of the ship placed, 0 otherwise.
 */
unsigned char listen_placed_ships(){
	unsigned char placed_ship_nbr = 0;
	char msg[2];
	if(receiveData(msg, 2) > 0)
		if(msg[0] == SHIP_PLACED)
			placed_ship_nbr = (unsigned char)msg[1];
	return placed_ship_nbr;
}

