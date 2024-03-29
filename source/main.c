/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include "graphics_manager.h"
#include "battlefield.h"
#include "game.h"


int main(void) {


		init_game();
		find_pair();
	while(true){
		reset_game_parameters();
		configure_graphics_main(); //upper screen to show the user
		wait_start();
		Battlefield* field = place_ships();
		configure_graphics_sub();  //sub screen to throw missles
		play_game(field);
		end_game();
		destroy_battlefield(field);
	}
    while(1)
        swiWaitForVBlank();	
}
