#include "game.h"
#include <stdio.h>
#include <nds.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#define SHIP_COUNT  1


// ----- Game Varibles -----

bool answer_received = true;
bool wait_answer = false;
bool finished = false;
bool opponent_ready = false;
bool player_ready = false;
bool game_starter = true;
bool respond = false;
bool my_move = true;
bool win = false;
int home_score = 0;
int opponent_score = 0;

//adjust the maximum hits according to the ship creating algorithm
const int MAX_SCORE = ((SHIP_COUNT+1)*(SHIP_COUNT+1)) >> 1;

//sent and received missle indexes
int missle_x, missle_y, missle_rx, missle_ry;

//last received land status
Land_status received_status = EMPTY;

//pointer array
Ship* ships[SHIP_COUNT];


void init_game(){
	//Stop blinking if there is
	irqDisable(IRQ_TIMER0);
	irqDisable(IRQ_TIMER1);
	REG_DISPCNT = REG_DISPCNT & ~DISPLAY_BG0_ACTIVE;
	REG_DISPCNT_SUB = REG_DISPCNT_SUB & ~DISPLAY_BG0_ACTIVE;

	//setup game parameters
	answer_received = true;
	finished = false;
	home_score = 0;
	opponent_score = 0;
	opponent_ready = false;
	player_ready = false;
	respond = false;
	game_starter = true;
	my_move = true;
	wait_answer = false;
	win = false;

	//initialize sound effects
	mmInitDefaultMem((mm_addr)soundbank_bin);
	mmLoadEffect(SFX_CLICK);
	mmLoadEffect(SFX_BOOM);
	mmLoadEffect(SFX_LOSE);
	mmLoadEffect(SFX_MISS);
	mmLoadEffect(SFX_WIN);
	mmLoadEffect(SFX_HURRY);



	//initalize console and connect to wifi
	consoleDemoInit();
	printf("Connecting to WiFi...\n\n");
	mmEffect(SFX_HURRY);
	connect_wifi();
	mmEffect(SFX_CLICK);
}

void reset_game_parameters(){
		answer_received = true;
		finished = false;
		home_score = 0;
		opponent_score = 0;
		opponent_ready = false;
		player_ready = false;
		respond = false;
		game_starter = true;
		my_move = true;
		wait_answer = false;
		win = false;
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
				//send three times to ensure...
				send_ready_packet();
				send_ready_packet();
				send_ready_packet();
				player_ready = true;
				printf("You are ready... \n\n");
				printf("Waiting on your opponent...\n\n");
				mmEffect(SFX_CLICK);
			}
		}

		if(opponent_ready == false){
			if(ready_packet_received() == true){
				printf("Your opponent is ready...\n\n");
				mmEffect(SFX_CLICK);
				opponent_ready = true;
			}
		}

		if(player_ready == true && opponent_ready == true){

			//Loop to empty wifi buffer
			int x,y;
			Land_status tmp;
			while(receive(&x,&y,&tmp) != R_NONE){}

			//quit the loop
			break;
		}


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

	unsigned char opponent_ships;
	i = 0;
	scanKeys();

	for(i = 0 ; i<SHIP_COUNT; ++i){
		printf("Place ship no: %i / %i \n\n", i+1, SHIP_COUNT);
		add_temp(ships[i], field);
		while(1){

			//-------Manage keys----------
			scanKeys();
			unsigned keys = keysDown();
			if(keys & KEY_LEFT){
				mmEffect(SFX_CLICK);
				if(move_temp(ships[i],field,LEFT) == false)
					printf("Invalid move left\n\n");
			}
			if(keys & KEY_DOWN){
				mmEffect(SFX_CLICK);
				if(move_temp(ships[i],field,DOWN) == false)
					printf("Invalid move down \n\n");
			}
			if(keys & KEY_UP){
				mmEffect(SFX_CLICK);
				if(move_temp(ships[i],field,UP) == false)
					printf("Invalid move up\n\n");
			}
			if(keys & KEY_RIGHT){
				mmEffect(SFX_CLICK);
				if(move_temp(ships[i],field,RIGHT) == false)
					printf("Invalid move right\n\n");
			}
			if(keys & KEY_B){
				mmEffect(SFX_CLICK);
				if(move_temp(ships[i],field,ROT) == false)
					printf("Invalid rotation \n\n");
			}
			if(keys & KEY_A){
				mmEffect(SFX_CLICK);

				//validate move
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
			if(opponent_ships != 0){
				printf("Opponent placed ship %d/%i \n\n", opponent_ships, SHIP_COUNT);
				mmEffect(SFX_HURRY);
			}
			if(opponent_ships == SHIP_COUNT) {
				printf("Your opponent finished \nplacing their ships. \nHurry up! \n \n");
				game_starter = false; //opponent will start because the player is late!
				my_move = false;
			}
			swiWaitForVBlank();
		}
	}
	if(game_starter){
		printf("You placed your ships... \n\nPlease wait for your \nopponent to place their \nships... \n\n");
		printf("You will start the game \n \n");
	}
	while(game_starter){//if finished placing, wait for the opponent...
		opponent_ships = listen_placed_ships();
		if(opponent_ships != 0){
			mmEffect(SFX_HURRY);
			printf("Opponent placed ship %d/%i \n\n", opponent_ships, SHIP_COUNT);
		}
		if(opponent_ships == SHIP_COUNT)
			break;
		swiWaitForVBlank();
	}

	//Destroy ships before quitting, as these are added to the battlefield
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
			bool first_answer = fire_available(home, missle_rx, missle_ry);
			Land_status result = fire(home, missle_rx, missle_ry);
				if(result == HIT){
					if(first_answer){
						++opponent_score;
						mmEffect(SFX_BOOM);
					}
					send_missle_response(missle_rx, missle_ry,true);

				}
				else if(result == MISS){
					send_missle_response(missle_rx, missle_ry, false);
					if(first_answer)
						mmEffect(SFX_MISS);
				}
				respond = false; //the answer has been given...
				my_move = true; //can play now
				show_missle_sub(missle_x, missle_y);//show the missle to play
		}

		if(!answer_received){//resend last missle
			send_missle(missle_x, missle_y);
		}

		//manage user input
		if(my_move){
			touchPosition tp;
			touchRead(&tp);
			if((tp.px | tp.py) != 0){//screen touched
				int grid_x = (int) (tp.px*((double)FIELD_WIDTH/SCREEN_WIDTH));
				int grid_y = (int) (tp.py*((double)FIELD_HEIGHT/SCREEN_HEIGHT));
				if((grid_x != missle_x) || (grid_y != missle_y))
					mmEffect(SFX_CLICK);
				if(missle_pos_inside(grid_x, grid_y)){

					//remove graphics
					remove_missle_sub(missle_x, missle_y);

					//move missle
					missle_x = grid_x;
					missle_y = grid_y;

					//refresh graphics
					show_missle_sub(missle_x, missle_y);
				}
			}

			scanKeys();
			unsigned keys = keysDown();
			if(keys & KEY_LEFT){
				mmEffect(SFX_CLICK);
				--missle_x;
				if(missle_pos_inside(missle_x, missle_y) == false){//missle is outside
					++missle_x;
				} else { //new position is valid
					remove_missle_sub(++missle_x, missle_y);//remove from the old position
					show_missle_sub(--missle_x, missle_y);//add to the new position
				}
			}
			if(keys & KEY_DOWN){
				mmEffect(SFX_CLICK);
				++missle_y;
				if(missle_pos_inside(missle_x, missle_y) == false){//missle is outside
					--missle_y;
				} else { //new position is valid
					remove_missle_sub(missle_x, --missle_y);//remove from the old position
					show_missle_sub(missle_x, ++missle_y);//add to the new position
				}
			}
			if(keys & KEY_UP){
				mmEffect(SFX_CLICK);
				--missle_y;
				if(missle_pos_inside(missle_x, missle_y) == false){//missle is outside
					++missle_y;
				} else { //new position is valid
					remove_missle_sub(missle_x, ++missle_y);//remove from the old position
					show_missle_sub(missle_x, --missle_y);//add to the new position
				}
			}
			if(keys & KEY_RIGHT){
				mmEffect(SFX_CLICK);
				++missle_x;
				if(missle_pos_inside(missle_x, missle_y) == false){//missle is outside
					--missle_x;
				} else { //new position is valid
					remove_missle_sub(--missle_x, missle_y);//remove from the old position
					show_missle_sub(++missle_x, missle_y);//add to the new position
				}
			}
			if(keys & KEY_X){
				mmEffect(SFX_CLICK);
				//validate missle
				if(fire_available(opponent, missle_x, missle_y) == true){
					send_missle(missle_x, missle_y);
					my_move = false; //move played
					answer_received = false; //wait for an answer
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
					answer_received = true;

					//if it is a new packet then act
					if(fire_available(opponent, missle_x, missle_y)){
						if(received_status == HIT){
							++home_score;
							mmEffect(SFX_BOOM);
						} else if (received_status == MISS){
							mmEffect(SFX_MISS);
						}
				    }
					//show the answer on your map
					set(received_status, missle_rx, missle_ry, opponent);
			}
		}

		//loop breaker, boolean "finished" will be true if everything is ok
		if(finished){
			break;
		}

		//Check for a winner
		if(home_score == MAX_SCORE){
			win = true;
			finished = true;
		} else if(opponent_score == MAX_SCORE){
			win = false;
			finished = true;
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

bool move_temp_touch(Ship* ship, Battlefield* field, int x, int y){
	int old_x = ship->topleft_x;
	int old_y = ship->topleft_y;

	//move to the new location
	ship->topleft_x = x = (int) (x*((double)FIELD_WIDTH/SCREEN_WIDTH));
	ship->topleft_y = y = (int) (y*((double)FIELD_HEIGHT/SCREEN_HEIGHT));


	if(inside(ship) == false){//if not valid
		ship->topleft_x = old_x;
		ship->topleft_y = old_y; //return to original point
				return false;
	}

			//the move is valid
			ship->topleft_x = old_x;
			ship->topleft_y = old_y;//return to original point
			remove_temp(ship,field);

			ship->topleft_x = x;
			ship->topleft_y = y;//move to the new point
			add_temp(ship,field);
			return true;
}


void end_game(){

	//Loop to empty wifi buffer
	int x,y;
	Land_status tmp;
	while(receive(&x,&y,&tmp) != R_NONE){}

	//Stop blinking if any
	irqDisable(IRQ_TIMER0);
	irqDisable(IRQ_TIMER1);
	REG_DISPCNT = REG_DISPCNT & ~DISPLAY_BG0_ACTIVE;
	REG_DISPCNT_SUB = REG_DISPCNT_SUB & ~DISPLAY_BG0_ACTIVE;


	consoleDemoInit();


	if(win){
		mmEffect(SFX_WIN);
		printf("\n\n    _________\n");
			printf("   |         |\n");
			printf("	| VICTORY |\n");
			printf("	|_________|\n\n");
			printf("Press START to play again...\n\n\n");

	} else if(!win){
		mmEffect(SFX_LOSE);
		printf("\n\n    __________\n");
			printf("   |          |\n");
			printf("	|  DEFEAT  |\n");
			printf("	|__________|\n\n");
			printf("Press START to play again...\n\n\n");
	}
}
