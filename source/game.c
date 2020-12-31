#include "game.h"
#include <stdio.h>
#include <nds.h>

bool opponent_ready = 0;
bool player_ready = 0;


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
