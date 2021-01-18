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


/**
 * Connects to WiFi and prints the states
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
 * Return the number of the ship placed, 0 otherwise (no ship placed).
 */
unsigned char listen_placed_ships();

/**
 * Sends a missle response packet indicating if the result was hit or miss.
 */
void send_missle_response(int x, int y, bool hit);

/**
 * Sends a missle packet to the given index
 */
void send_missle(int x, int y);

//Receive constants
#define R_NONE -1
#define R_MISSLE 1
#define R_ANSWER 2

/**
 * Receives a packet and parses it.
 *
 * The received packet can be:
 *
 * -A missle response packet
 * -A missle packet
 * -Nothing
 *
 */
int receive(int* x, int* y, Land_status* status);

#endif /* WIFI_H_ */
