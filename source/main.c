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

	consoleDemoInit();
	connect_wifi();
	send_pairing_packet();
	wait_pairing_packet();
	wait_start();
	configure_graphics_main();//all empty
	//configure_graphics_sub();//all empty
	place_ships();
	//play_game();
	/*
	Battlefield* field = create_battlefield(MAIN);
	//Battlefield* field2 = create_battlefield(SUB);

	//Ship* big = create_ship(5,5,3,VERTICAL);
	Ship* big2 = create_ship(9,7,7,HORIZONTAL);
	Ship* big3 = create_ship(11,5,6,VERTICAL);
	//add(big,field2);

	add_temp(big3, field);
	//remove_temp(big3, field);
	move_temp(big3,field, LEFT);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, UP);
	move_temp(big3,field, UP);
	move_temp(big3,field, UP);
	move_temp(big3,field, UP);
	move_temp(big3,field, UP);
	move_temp(big3,field, UP);
	move_temp(big3,field, UP);
	move_temp(big3,field, UP);
	move_temp(big3,field, UP);
	move_temp(big3,field, UP);
	move_temp(big3,field,ROT);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, DOWN);
	move_temp(big3,field, DOWN);
	move_temp(big3,field,ROT);

	//remove_temp(big2, field);

	fire(field, 5, 5);
	fire(field, 3, 5);
	fire(field, 3, 4);
	fire(field, 3, 6);
	fire(field, 3, 6);
	fire(field, 6, 7);
	fire(field, 7, 7);
	fire(field, 12, 7);

    printf("\nTemplate nds\n");
	*/
    while(1)
        swiWaitForVBlank();	

    //destroy_battlefield(field);
    //destroy_battlefield(field2);
    //destroy_ship(big2);
    //destroy_ship(big);

}
