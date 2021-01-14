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
		/*
		while(1){
			scanKeys();
			unsigned keys = keysDown();
			if(keys & KEY_A){
				send_missle_response(true);
			}
			if(keys & KEY_X){
				send_missle_response(false);
			}
			Land_status status;
			if(receive_missle_response(&status)){
				if(status == HIT)
					printf("Response hit received \n");
				else if(status == MISS)
					printf("Response miss received \n");
			}
			swiWaitForVBlank();
		}

		*/
	while(true){
		init_game();
		find_pair();
		wait_start();
		configure_graphics_main(); //upper screen to show the user
		Battlefield* field = place_ships();
		configure_graphics_sub();  //sub screen to throw missles
		play_game(field);
		end_game();
		destroy_battlefield(field);
	}


	//configure_graphics_sub();//all empty

	//place_ships();
	//play_game();

	//Battlefield* field2 = create_battlefield(MAIN);
	//Battlefield* field = create_battlefield(SUB);
/*
	Ship* big = create_ship(5,5,3,VERTICAL);
	Ship* big2 = create_ship(9,7,7,HORIZONTAL);
	Ship* big3 = create_ship(11,5,6,VERTICAL);

	add(big,field2);
	add_temp(big2,field2);
	add(big3, field);
	show_missle_sub(11,5);
*/

    while(1)
        swiWaitForVBlank();	

    //destroy_battlefield(field);
    //destroy_battlefield(field2);
    //destroy_ship(big2);
    //destroy_ship(big);

}
