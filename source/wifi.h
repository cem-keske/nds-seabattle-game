/*
 * wifi.h
 *
 *  Created on: Dec 30, 2020
 *      Author: nds
 */
#ifndef WIFI_H_
#define WIFI_H_


#include "graphics_manager.h"
#include <stdbool.h>


#define PAIRING_REQ  	1
#define PAIRING_ACK  	2
#define READY  			3
#define SHIP_PLACED		4
#define MISSLE_RESPONSE_PACKET_ID 	5
#define MISSLE_PACKET_ID  6
#define HIT_CONTENT  'H'
#define MISS_CONTENT 'M'
#define R_NONE -1
#define R_MISSLE 1
#define R_ANSWER 2

/**
 * Connects wifi and prints the states
 */
bool connect_wifi();


/**
 * Sends a pairing packet
 */
void send_pairing_packet();

/**
 * Waits for a pairing packet to arrive, if the pairing packet arrives, prints it
 * and responds with a pairing ACK packet.
 */
void wait_pairing_packet();

/**
 * Sends a packet indicating that the player is ready
 */
void send_ready_packet();

/**
 * Returns true if a ready packet was received
 */
bool ready_packet_received();

/**
 * Sends a packet informing the opponent that a ship was placed.
 */
void send_ship_placed(unsigned char ship_nbr);


/**
 * Receive a packet from the opponent informing that a ship was placed.
 * \return The number of the ship placed, 0 otherwise.
 */
unsigned char listen_placed_ships();

/**
 * Sends a response to the opponent inticating if the previous missle
 * resulted in a hit
 */
//void send_missle_response(bool hit);

/**
*	Wait for a missle response, return true if hit, false if miss
 */
//bool wait_missle_response();

/**
 * True if a packet is received,
 * set status accordingly
 */
//bool receive_missle_response(Land_status* status);

/**
 * Sends a missle packet to the opponent indicating the position of the missle
 */
//void send_missle_packet(char x, char y);


/**
 * Receives the missle sent by opponent
 * Returns true if a missle was sent, false otherwise
 */
//bool receive_missle_packet(int* x, int* y);

void send_missle_response(int x, int y, bool hit);

void send_missle(int x, int y);

int receive(int* x, int* y, Land_status* status);

#endif /* WIFI_H_ */
