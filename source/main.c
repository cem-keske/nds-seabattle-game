/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "graphics_manager.h"
#include "battlefield.h"

int main(void) {
	

	configure_graphics_main();//all empty
	show_land(HIT, 9, 8);
	show_land(HIT, 9, 9);
	show_land(FULL,9,10);
	show_land(FULL,9,11);
	show_land(MISS, 10,11);
	show_land(MISS, 10, 9);

	show_land(FULL,3,5);
	show_land(FULL,4,5);
	show_land(FULL,5,5);
	show_land(FULL,6,5);
	show_land(FULL,7,5);

	show_land(MISS, 1,1);
	show_land(MISS, 5,2);
	show_land(MISS, 7,9);

	show_land(HIT, 6, 3);
	show_land(HIT, 7, 3);
	show_land(HIT, 8, 3);




    //consoleDemoInit();
    //printf("\nTemplate nds\n");

    while(1)
        swiWaitForVBlank();	
}
