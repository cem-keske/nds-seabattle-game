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
typedef enum {EMPTY, FULL, HIT, MISS, TRANSPARENT} Land_status;




void configure_graphics_main();

void configure_map();

void show_land(Land_status status, int x, int y);

/**
 * Shows a 2x2 tiled display by using a symmetry for the given tile
 *
 * Example:   tile: /   -->  display:  / \
 * 									   \ /
 */
void tile_shower(u16 tile_index, u16* map, int grid_x, int grid_y);

/**
 * Shows a 2x2 tiled display using the given tile of length 64*4 (bytes).
 *
 * Example:   tile: /\/\  --> display:   / \
 * 									   	 \ /
 */
void tile_shower_2x2(u16 tile_2x2_index, u16* map, int grid_x, int grid_y);

/**
 * Initialize the toplevel backround for blinking effect on MAIN screen.
 */
void init_toplevel();

/**
 * Show land on toplevel background of MAIN screen.
 */
void show_land_toplevel(Land_status status, int x, int y);

/**
 * Show blinking missle image on SUB screen on the given index.
 */
void show_missle_sub(int x, int y);

/**
 * Remove blinking missle image on SUB screen on the given index.
 */
void remove_missle_sub(int x, int y);

void configure_graphics_sub();

void configure_map_sub();

void show_land_sub(Land_status status, int x, int y);

void tile_shower_sub(u16 tile_index, u16* map, int grid_x, int grid_y);

void tile_shower_2x2_sub(u16 tile_2x2_index, u16* map, int grid_x, int grid_y);

#endif /* GRAPHICS_MANAGER_H_ */
