/*
 * game.h
 *
 *  Created on: Dec 30, 2020
 *      Author: nds
 */

#ifndef GAME_H_
#define GAME_H_

#include "wifi.h"
#include "ship.h"
#include "battlefield.h"
#include <stdbool.h>

typedef enum {LEFT, RIGHT, UP, DOWN, ROT} Directions;

/**
 * Initialize the game parameters and connect to Wifi.
 */
void init_game();


/**
 * Finds a pair on the network, this function blocks
 * the execution until an opponent is found.
 */
void find_pair();

/**
 * The main algorithm of the game
 */
void play_game(Battlefield* home);

/**
 * Wait for both players to get ready(press start). This function blocks
 * the execution until both players press start.
 */
void wait_start();

/**
 * Asks the user to place ship on the home fields,
 * receives packets from the opponent indicating the opponent
 * ships were placed.
 * Sets game_starter boolean accordingly.
 * (The first player to place their ship starts the game.)
 */
Battlefield* place_ships();

/**
 * Change the position of the ship and refresh the temporary display
 * Return false if not movable
 */
bool move_temp(Ship* ship, Battlefield* field, Directions dir);

/**
 * Change the position of the ship and refresh the temporary display
 * Return false if not movable
 */
bool move_temp_touch(Ship* ship, Battlefield* field, int x, int y);

/**
 * Shows the end of the game. Returns when START pressed.
 */
void end_game();

#endif /* GAME_H_ */
