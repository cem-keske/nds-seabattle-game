/*
 * ship.h
 *
 *  Created on: Dec 30, 2020
 *      Author: nds
 */

#ifndef SHIP_H_
#define SHIP_H_

typedef enum {HORIZONTAL, VERTICAL} Orientation;

typedef struct{
	int topleft_x;
	int topleft_y;
	int length;
	Orientation orientation;
} Ship;


/*
 * Allocate memory for a new ship.
 */
Ship* create_ship(int topleft_x, int topleft_y, int length, Orientation orientation);

/*
 * Free memory pointed by the ship pointer.
 */
void destroy_ship(Ship* ship);

#endif /* SHIP_H_ */
