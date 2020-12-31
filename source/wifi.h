/*
 * wifi.h
 *
 *  Created on: Dec 30, 2020
 *      Author: nds
 */
#ifndef WIFI_H_
#define WIFI_H_

#include "WiFi_minilib.h"
#include <stdbool.h>

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

#endif /* WIFI_H_ */
