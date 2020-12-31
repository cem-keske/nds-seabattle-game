#include "game.h"
#include <stdio.h>
#include <nds.h>

#define SHIP_COUNT  6

bool opponent_ready = 0;
bool player_ready = 0;

Ship* ships[SHIP_COUNT];

void play_game(){}

void wait_start(){
	printf("Press start if you are ready...\n\n");

	scanKeys();
	while(1){
		if(player_ready == false){
			scanKeys();
			unsigned keys = keysDown();
			if(keys == KEY_START){
				send_ready_packet();
				player_ready = true;
				printf("You are ready... \n\n");
				printf("Waiting on your opponent...\n\n");
			}
		}

		if(opponent_ready == false){
			if(ready_packet_received() == true){
				printf("Your opponent is ready...\n\n");
				opponent_ready = true;
			}
		}

		if(player_ready == true && opponent_ready == true)
			break;

		swiWaitForVBlank();
	}
}

Battlefield * place_ships(){
	Battlefield* field = create_battlefield(MAIN);
	//initialize ship array
	int i;
	for(i = 0; i < SHIP_COUNT; ++i){
		ships[i] = create_ship(0,0,2*(i/2+1),VERTICAL);
	}
	//show all
	unsigned char opponent_ships;
	i = 0;
	scanKeys();
	for(i = 0 ; i<SHIP_COUNT; ++i){
		printf("Place ship no: %i / %i \n\n", i+1, SHIP_COUNT);
		add_temp(ships[i], field);
		while(1){
			scanKeys();
			unsigned keys = keysDown();
			if(keys & KEY_LEFT){
				//printf("<- pressed\n");
				if(move_temp(ships[i],field,LEFT) == false)
					printf("Invalid move left\n\n");
			}
			if(keys & KEY_DOWN){
				//printf("DOWN pressed\n");
				if(move_temp(ships[i],field,DOWN) == false)
					printf("Invalid move down \n\n");
			}
			if(keys & KEY_UP){
				//printf("UP pressed\n");
				if(move_temp(ships[i],field,UP) == false)
					printf("Invalid move up\n\n");
			}
			if(keys & KEY_RIGHT){
				//printf("-> pressed\n");
				if(move_temp(ships[i],field,RIGHT) == false)
					printf("Invalid move right\n\n");
			}
			if(keys & KEY_B){
				//printf("B pressed\n");
				if(move_temp(ships[i],field,ROT) == false)
					printf("Invalid rotation \n\n");
			}
			if(keys & KEY_A){//validate move
				if(available(ships[i],field) == false){
					printf("Cant place the ship here! \n\n");
				} else {//place available
					remove_temp(ships[i], field);
					add(ships[i], field);
					send_ship_placed(i + 1);
					break; //place the next ship
				}

			}
			opponent_ships = listen_placed_ships();
			if(opponent_ships != 0)
				printf("Opponent placed ship %d/%i \n\n", opponent_ships, SHIP_COUNT);
			if(opponent_ships == SHIP_COUNT)
				printf("Your opponent finished \n placing their ships. \n Hurry up! \n \n");
			swiWaitForVBlank();
		}
		/*
			for(i = 0; i < SHIP_COUNT; ++i){
				add_temp(ships[i], field);
		}*/
	}
	printf("You placed your ships... \n\nPlease wait for your \nopponent to place their \nships... \n\n");
	while(1){
		opponent_ships = listen_placed_ships();
		if(opponent_ships != 0)
			printf("Opponent placed ship %d/%i \n\n", opponent_ships, SHIP_COUNT);
		if(opponent_ships == SHIP_COUNT)
			break;
		swiWaitForVBlank();
	}
	return field;
}

bool move_temp(Ship* ship, Battlefield* field, Directions dir){
	switch(dir){
	case UP:
		ship->topleft_y = ship->topleft_y - 1;
		if(inside(ship) == false){//if not valid
			ship->topleft_y = ship->topleft_y + 1; //return to original point
			return false;
		}

		//the move is valid
		ship->topleft_y = ship->topleft_y + 1; //return to original point
		remove_temp(ship,field);
		ship->topleft_y = ship->topleft_y - 1; //move to the new point
		add_temp(ship,field);
		break;



	case DOWN:
		ship->topleft_y = ship->topleft_y + 1;
		if(inside(ship) == false){//if not valid
			ship->topleft_y = ship->topleft_y - 1; //return to original point
			return false;
		}
		//the move is valid
		ship->topleft_y = ship->topleft_y - 1; //return to original point
		remove_temp(ship,field);
		ship->topleft_y = ship->topleft_y + 1; //move to the new point
		add_temp(ship,field);
		break;


	case LEFT:
		ship->topleft_x = ship->topleft_x - 1;
		if(inside(ship) == false){//if not valid
			ship->topleft_x = ship->topleft_x + 1; //return to original point
			return false;
		}
		//the move is valid
		ship->topleft_x = ship->topleft_x + 1; //return to original point
		remove_temp(ship,field);
		ship->topleft_x = ship->topleft_x - 1; //move to the new point
		add_temp(ship,field);
		break;


	case RIGHT:
		ship->topleft_x = ship->topleft_x + 1;
		if(inside(ship) == false){//if not valid
			ship->topleft_x = ship->topleft_x - 1; //return to original point
			return false;
		}
		//the move is valid
		ship->topleft_x = ship->topleft_x - 1; //return to original point
		remove_temp(ship,field);
		ship->topleft_x = ship->topleft_x + 1; //move to the new point
		add_temp(ship,field);
		break;

	case ROT:
		if(ship->orientation == HORIZONTAL){
			ship->orientation = VERTICAL;
			if(inside(ship) == false){//if not valid
				ship->orientation = HORIZONTAL; //return to original point
				return false;
			}
			//the move is valid
			ship->orientation = HORIZONTAL; //return to original point
			remove_temp(ship,field);
			ship->orientation = VERTICAL; //move to the new point
			add_temp(ship,field);
		} else if(ship->orientation == VERTICAL){

			ship->orientation = HORIZONTAL;
			if(inside(ship) == false){//if not valid
				ship->orientation = VERTICAL; //return to original point
				return false;
			}
			//the move is valid
			ship->orientation = VERTICAL; //return to original point
			remove_temp(ship,field);
			ship->orientation = HORIZONTAL; //move to the new point
			add_temp(ship,field);
		}
		break;
	default: break;
	}
	return true;
}
