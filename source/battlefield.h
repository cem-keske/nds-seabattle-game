/*
 * battlefield.h
 *
 *  Created on: Dec 23, 2020
 *      Author: nds
 */



#ifndef BATTLEFIELD_H_
#define BATTLEFIELD_H_

#include "graphics_manager.h"
#include "ship.h"
#include <stdbool.h>


typedef struct{
	Land_status* battle_grid;
	Screen display;
} Battlefield;

/**
 * Creates an empty battlefield.
 */
Battlefield* create_battlefield(Screen display);

/**
 * C-type struct destructor, frees up the memory
 */
void destroy_battlefield(Battlefield* battlefield);

/**
 * Takes a shot to the corresponding index, returns the resulting land status
 * updates the graphics.
 *
 * EMPTY -> MISS
 * FULL  -> HIT
 * MISS  -> MISS (INVALID)
 * HIT	 -> HIT  (INVALID)
 *
 */
Land_status fire(Battlefield* battlefield ,int x, int y);

/**
 * Returns true if the index has NOT previously been shot.
 */
bool fire_valid(Battlefield* battlefield ,int x, int y);

/**
 * Adds the ship to the battlefield and shows it.
 * Returns true if the place is empty and the operation is successful.
 */
bool add(Ship* ship, Battlefield* field);

/**
 * Returns true if the operation of adding the ship to the given index doesn't
 * create any conflict.
 */
bool available(Ship* ship, Battlefield* field);


#endif /* BATTLEFIELD_H_ */
