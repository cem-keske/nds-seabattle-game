#include "battlefield.h"

#include <stdlib.h>
#include <stdio.h>


Battlefield* create_battlefield(Screen display){
	Battlefield* f = malloc(sizeof(Battlefield));
	f->battle_grid = malloc(sizeof(Land_status) * FIELD_WIDTH * FIELD_HEIGHT);
	f->display = display;
	int i;
	for(i = 0; i < FIELD_WIDTH * FIELD_HEIGHT; ++i){
		f->battle_grid[i] = EMPTY;
	}
	return f;
}


void destroy_battlefield(Battlefield* battlefield){
	free(battlefield->battle_grid);
	free(battlefield);
}

Land_status fire(Battlefield* battlefield ,int x, int y){
	Land_status* current = &battlefield->battle_grid[y*FIELD_WIDTH + x];

	switch(*current){

	case EMPTY: *current = MISS; break;
	case FULL:  *current = HIT; break;
	default: break;
	}
	if(battlefield->display == SUB)
		show_land_sub(*current,x,y);
	else if(battlefield->display == MAIN)
		show_land(*current,x,y);
	return *current;
}

void set(Land_status status, int x, int y, Battlefield* field){
	field->battle_grid[y*FIELD_WIDTH + x] = status;
	if(field->display == SUB)
			show_land_sub(status,x,y);
	else if(field->display == MAIN)
			show_land(status,x,y);
}

bool fire_available(Battlefield* battlefield, int x, int y){
	if(battlefield->battle_grid[y*FIELD_WIDTH + x] == FULL ||
			battlefield->battle_grid[y*FIELD_WIDTH + x] == EMPTY)
			return true;
	return false;
}

bool missle_pos_inside(int x, int y){
	if(x < 0 || x >= FIELD_WIDTH || y < 0 || y >= FIELD_HEIGHT)
		return false;
	return true;
}


bool add(Ship* ship, Battlefield* field){
	if(available(ship,field)){
		int i;
		if(ship->orientation == HORIZONTAL){
			for(i = ship->topleft_x; i < ship->topleft_x + ship->length; ++i){
				field->battle_grid[ship->topleft_y * FIELD_WIDTH + i] = FULL;
				if(field->display == MAIN)
					show_land(FULL, i, ship->topleft_y);
				else if(field->display == SUB)
					show_land_sub(FULL, i, ship->topleft_y);

			}

		}else if(ship->orientation == VERTICAL){
			for(i = ship->topleft_y; i < ship->topleft_y + ship->length; ++i){
				field->battle_grid[i * FIELD_WIDTH + ship->topleft_x] = FULL;
				if(field->display == MAIN)
					show_land(FULL, ship->topleft_x, i);
				else if(field->display == SUB)
					show_land_sub(FULL,  ship->topleft_x, i);
			}
		}
		return true;
	}

	return false;

}


bool add_temp(Ship* ship, Battlefield* field){
	if(inside(ship) == false){
		return false;
	}
	int i;
	if(ship->orientation == HORIZONTAL){
		for(i = ship->topleft_x; i < ship->topleft_x + ship->length; ++i){
			if(field->display == MAIN)
				show_land_toplevel(FULL, i, ship->topleft_y);
		}
	}else if(ship->orientation == VERTICAL){
		for(i = ship->topleft_y; i < ship->topleft_y + ship->length; ++i){
			if(field->display == MAIN)
				show_land_toplevel(FULL, ship->topleft_x, i);
		}
	}
	return true;
}

/**
 * Removes the temporary ship on the battlefield. (not included in grid)
 */
bool remove_temp(Ship* ship, Battlefield* field){
	if(valid(ship) == false)
			return false;
		int i;
		if(ship->orientation == HORIZONTAL){
			for(i = ship->topleft_x; i < ship->topleft_x + ship->length; ++i){
				if(field->display == MAIN)
					show_land_toplevel(TRANSPARENT, i, ship->topleft_y);
			}
		}else if(ship->orientation == VERTICAL){
			for(i = ship->topleft_y; i < ship->topleft_y + ship->length; ++i){
				if(field->display == MAIN)
					show_land_toplevel(TRANSPARENT, ship->topleft_x, i);
			}
		}
		return true;
}

/**
 * Returns true if the topleft index is valid
 */
bool valid(Ship* ship){
	//check if the topleft index is valid
		if(ship->topleft_x < 0 || ship->topleft_x >= FIELD_WIDTH ||
				ship->topleft_y < 0 || ship->topleft_y >= FIELD_HEIGHT)
			return false;
		return true;
}

bool inside(Ship* ship){
	//check if the topleft index is valid
		if(valid(ship) == false){
			//printf("Not valid\n");
			return false;
		}
		//check bounds
		if(ship->orientation == HORIZONTAL){
			if(ship->topleft_x + ship->length > FIELD_WIDTH)
				return false;
		}else if(ship->orientation == VERTICAL){
			if(ship->topleft_y + ship->length > FIELD_HEIGHT)
				return false;
		}
		return true;
}

/**
 * Returns true if the operation of adding the ship to the given index doesn't
 * create any conflict. Collisions included.
 */
bool available(Ship* ship, Battlefield* field){
	//check if the topleft index is valid
	if(valid(ship) == false){
		return false;
	}
	//check boundaries and other things
	int i;
	if(ship->orientation == HORIZONTAL){
		if(ship->topleft_x + ship->length > FIELD_WIDTH)
			return false;
		for(i = ship->topleft_x; i < ship->topleft_x + ship->length; ++i){
			if(field->battle_grid[ship->topleft_y * FIELD_WIDTH + i] == FULL)
				return false;
		}
	}else if(ship->orientation == VERTICAL){
			if(ship->topleft_y + ship->length > FIELD_HEIGHT)
				return false;
			for(i = ship->topleft_y; i < ship->topleft_y + ship->length; ++i){
				if(field->battle_grid[i * FIELD_WIDTH + ship->topleft_x] == FULL)
					return false;
			}
		}
	return true;
}




void add_temp_missle(int x, int y){
	show_missle_sub(x,y);
}

void remove_temp_missle(int x, int y){
	remove_missle_sub(x,y);
}

