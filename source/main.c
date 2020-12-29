/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "graphics_manager.h"

int main(void) {
	
	configure_graphics_main();
    //consoleDemoInit();
    //printf("\nTemplate nds\n");

    while(1)
        swiWaitForVBlank();	
}
