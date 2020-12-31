/*
 * graphics_manager.h
 *
 *  Created on: Dec 27, 2020
 *      Author: nds
 */
#ifndef GRAPHICS_MANAGER_H_
#define GRAPHICS_MANAGER_H_

#include <nds.h>

typedef enum {SUB, MAIN} Screen;
typedef enum {EMPTY, FULL, HIT, MISS} Land_status;




void configure_graphics_main();

void configure_map();

void show_land(Land_status status, int x, int y);

void tile_shower(u16 tile_index, u16* map, int grid_x, int grid_y);

void tile_shower_2x2(u16 tile_2x2_index, u16* map, int grid_x, int grid_y);


void configure_graphics_sub();

void configure_map_sub();

void show_land_sub(Land_status status, int x, int y);

void tile_shower_sub(u16 tile_index, u16* map, int grid_x, int grid_y);

void tile_shower_2x2_sub(u16 tile_2x2_index, u16* map, int grid_x, int grid_y);

#endif /* GRAPHICS_MANAGER_H_ */
