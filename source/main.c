/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "graphics_manager.h"
#include "battlefield.h"
#include "game.h"
#include "wifi.h"


int main(void) {
		init_game();
		find_pair();
		wait_start();

	while(true){
		configure_graphics_main(); //upper screen to show the user
		Battlefield* field = place_ships();
		configure_graphics_sub();  //sub screen to throw missles
		play_game(field);
		end_game();
		destroy_battlefield(field);


	}

    while(1)
        swiWaitForVBlank();	

}
