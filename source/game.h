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

void init_game();

void play_game();

void wait_start();

Battlefield* place_ships();

/**
 * Change the position of the ship and refresh the temporary display
 * Return false if not movable
 */
bool move_temp(Ship* ship, Battlefield* field, Directions dir);

#endif /* GAME_H_ */
