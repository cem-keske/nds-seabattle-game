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

#endif /* WIFI_H_ */
