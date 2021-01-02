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
 * Set the given index (x,y) to the given status and show it on the map
 */
void set(Land_status status, int x, int y, Battlefield* field);

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
bool fire_available(Battlefield* battlefield ,int x, int y);

/**
 * Returns true if the given index is inside the grid.
 */
bool missle_pos_inside(int x, int y);

/**
 * Adds the ship to the battlefield and shows it.
 * Returns true if the place is empty and the operation is successful.
 */
bool add(Ship* ship, Battlefield* field);

/**
 * Shows a temporary ship on the battlefield. (not included in grid)
 */
bool add_temp(Ship* ship, Battlefield* field);

/**
 * Removes the temporary ship on the battlefield. (not included in grid)
 */
bool remove_temp(Ship* ship, Battlefield* field);

/**
 * Returns true if the operation of adding the ship to the given index doesn't
 * create any conflict.
 */
bool available(Ship* ship, Battlefield* field);


bool valid(Ship* ship);

/**
 * Returns true if the operation of adding the ship to the given index doesn't
 * exceed bounds of the map.
 */
bool inside(Ship* ship);

#endif /* BATTLEFIELD_H_ */
