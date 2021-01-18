/*
 * ship.c
 *
 *  Created on: Dec 30, 2020
 *      Author: nds
 */

#include "ship.h"
#include <stdlib.h>

Ship* create_ship(int topleft_x, int topleft_y, int length, Orientation orientation){
	Ship* ship = malloc(sizeof(Ship));
	ship->length = length;
	ship->orientation = orientation;
	ship->topleft_x = topleft_x;
	ship->topleft_y = topleft_y;
	return ship;
}

void destroy_ship(Ship* ship){
	free(ship);
}
