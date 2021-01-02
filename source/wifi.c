#include "wifi.h"

#include "WiFi_minilib.h"
#include <stdio.h>



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
	printf("Searching for another player! \n\n");
}


void wait_pairing_packet(){
	printf("Waiting for another player to join! \n\n");
	while(1){
		char msg[1];

		if(receiveData(msg, 1) > 0){
			//a message is received
			if(msg[0] == PAIRING_REQ){
				printf("A new player has joined the network! \n\n");
				msg[0] = PAIRING_ACK;
				sendData(msg, 1);
				printf("Pairing successful! \n\n");
				break;
			} else if(msg[0] == PAIRING_ACK) {
				printf("Connected to another player! \n\nPairing succesful. \n\n");
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


/**
 * Sends a response to the opponent inticating if the previous missle
 * resulted in a hit
 */
/*
void send_missle_response(bool hit){
	char msg[2];
	msg[0] = MISSLE_RESPONSE_ID;
	if(hit == true){
		msg[1] = MISSLE_RESPONSE_HIT;
		printf("Hit ");
	} else {
		msg[1] = MISSLE_RESPONSE_MISS;
		printf("miss ");
	}
	sendData(msg, 2);
	printf("Message sent\n");
}
*/
/*
bool wait_missle_response() {
	char response[2];
	while(1){
		if(receiveData(response, 2) > 0){
			if(response[0] == MISSLE_RESPONSE_ID){
				if(response[1] == MISSLE_RESPONSE_HIT)
					return true;
				else if(response[1] == MISSLE_RESPONSE_MISS)
					return false;
			}
		}
	swiWaitForVBlank();
	}
	return false;
}
*/
/*
bool receive_missle_response(Land_status* status){
	char response[2];
	if(receiveData(response, 2) > 0){
		if(response[0] == MISSLE_RESPONSE_ID){
			if(response[1] == MISSLE_RESPONSE_HIT)
				*status = HIT;
			else if(response[1] == MISSLE_RESPONSE_MISS)
				*status = MISS;
		}
		return true;
	}
	return false;
}
*/
/**
 * Sends a missle packet to the opponent indicating the position of the missle
 */
void send_missle_packet(char x, char y){
	char msg[3] = {MISSLE_PACKET_ID, x, y};
	sendData(msg, 3);
}


/**
 * Receives the missle sent by opponent
 * Returns true if a missle was sent, false otherwise
 */
bool receive_missle_packet(int* x, int* y){
	char msg[3];
	bool received = false;
	if(receiveData(msg,3) > 0){//a message was received
		if(msg[0] == MISSLE_PACKET_ID){//it is a missle packet
			received = true;
			*x = (int)msg[1];
			*y = (int)msg[2];
		}
	}
	return received;
}


void send_missle_response(int x, int y, bool hit){
	char message[4];
	message[0] = MISSLE_RESPONSE_PACKET_ID;
	message[1] = (char)(x);
	message[2] = (char)(y);
	if(hit == true){
		message[3] = HIT_CONTENT;
	}else{
		message[3] = MISS_CONTENT;
	}
	sendData(message, 4);
}

void send_missle(int x, int y){
	char message[4];
	message[0] = MISSLE_PACKET_ID;
	message[1] = (char)(x);
	message[2] = (char)(y);
	message[3] = HIT_CONTENT;//dummy...
	sendData(message, 4);
}

int receive(int* x, int* y, Land_status* status){
	char message[4];
	if(receiveData(message,4) > 0) { //a message is received
		*x = message[1];
		*y = message[2];
		if(message[3] == HIT_CONTENT){
			*status = HIT;
		} else if (message[3] == MISS_CONTENT){
			*status = MISS;
		}
		if(message[0] == MISSLE_PACKET_ID){
			return R_MISSLE;
		}else if(message[0] == MISSLE_RESPONSE_PACKET_ID){
			return R_ANSWER;
		}
	}
	return R_NONE; //no packet received
}

