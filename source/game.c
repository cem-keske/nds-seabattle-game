#include "game.h"
#include <stdio.h>
#include <nds.h>

#define SHIP_COUNT  6

bool opponent_ready = false;
bool player_ready = false;
bool game_starter = true;
bool respond = false;
bool my_move = true;

int missle_x, missle_y, missle_rx, missle_ry;//sent and received missle indexes

Land_status received_status = EMPTY;

Ship* ships[SHIP_COUNT];


void init_game(){
	opponent_ready = false;
	player_ready = false;
	respond = false;
	game_starter = true;
	my_move = true;
	consoleDemoInit();
	connect_wifi();
}

void find_pair(){
	send_pairing_packet();
	wait_pairing_packet();
}

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
			if(opponent_ships == SHIP_COUNT) {
				printf("Your opponent finished \nplacing their ships. \nHurry up! \n \n");
				game_starter = false; //opponent will start because you are late!
				my_move = false;
			}
			swiWaitForVBlank();
		}
	}
	if(game_starter){
		printf("You placed your ships... \n\nPlease wait for your \nopponent to place their \nships... \n\n");
		printf("You will start the game \n \n");

	}
	while(game_starter){//if you finished placing, wait for your opponent...
		opponent_ships = listen_placed_ships();
		if(opponent_ships != 0)
			printf("Opponent placed ship %d/%i \n\n", opponent_ships, SHIP_COUNT);
		if(opponent_ships == SHIP_COUNT)
			break;
		swiWaitForVBlank();
	}

	//Destroy ships before quitting
	for(i=0; i<SHIP_COUNT; ++i){
		destroy_ship(ships[i]);
	}
	return field;
}
void play_game(Battlefield* home){
	Battlefield* opponent = create_battlefield(SUB);
	if(my_move){
		show_missle_sub(missle_x, missle_y);
	}
	while(true){
		if(respond == true){ //need to answer a missle packet
			Land_status result = fire(home, missle_rx, missle_ry);
			if(result == HIT)
				send_missle_response(missle_rx, missle_ry,true);
			else if(result == MISS)
				send_missle_response(missle_rx, missle_ry, false);
			respond = false; //the answer has been given...
			my_move = true; //can play now
			show_missle_sub(missle_x, missle_y);//show the missle to play
		}

		//manage user input
		if(my_move){
			scanKeys();
			unsigned keys = keysDown();
			if(keys & KEY_LEFT){
				--missle_x;
				if(missle_pos_inside(missle_x, missle_y) == false){//missle is outside
					++missle_x;
				} else { //new position is valid
					remove_missle_sub(++missle_x, missle_y);//remove from the old position
					show_missle_sub(--missle_x, missle_y);//add to the new position
				}
			}
			if(keys & KEY_DOWN){
				++missle_y;
				if(missle_pos_inside(missle_x, missle_y) == false){//missle is outside
					--missle_y;
				} else { //new position is valid
					remove_missle_sub(missle_x, --missle_y);//remove from the old position
					show_missle_sub(missle_x, ++missle_y);//add to the new position
				}
			}
			if(keys & KEY_UP){
				--missle_y;
				if(missle_pos_inside(missle_x, missle_y) == false){//missle is outside
					++missle_y;
				} else { //new position is valid
					remove_missle_sub(missle_x, ++missle_y);//remove from the old position
					show_missle_sub(missle_x, --missle_y);//add to the new position
				}
			}
			if(keys & KEY_RIGHT){
				++missle_x;
				if(missle_pos_inside(missle_x, missle_y) == false){//missle is outside
					--missle_x;
				} else { //new position is valid
					remove_missle_sub(--missle_x, missle_y);//remove from the old position
					show_missle_sub(++missle_x, missle_y);//add to the new position
				}
			}
			if(keys & KEY_X){//validate missle
				if(fire_available(opponent, missle_x, missle_y) == true){
					send_missle(missle_x, missle_y);
					my_move = false; //move played
					remove_missle_sub(missle_x, missle_y);
				}
			}
		}


		//receive packets and act accordingly
		int received_packet = receive(&missle_rx, &missle_ry, &received_status);

		if(received_packet != R_NONE){
			if(received_packet == R_MISSLE){
				respond = true; //an answer will be sent
			} else if(received_packet == R_ANSWER){
				//show the answer on your map
				set(received_status, missle_rx, missle_ry, opponent);
			}
		}
		swiWaitForVBlank();
	}
	destroy_battlefield(opponent);
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
