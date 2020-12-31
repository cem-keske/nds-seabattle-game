#include "graphics_manager.h"
#include "string.h"
#include "hitship.h"

#define EMPTYTILE_RAM_POS  	EMPTYTILE_IDX * 32
#define FULLTILE_RAM_POS  	FULLTILE_IDX * 32
#define MISSTILE_RAM_POS  	MISSTILE_IDX * 32
#define EMPTYTILE2_RAM_POS 	EMPTYTILE2_IDX*32
#define TILES_END_RAM_POS 	TILE_END_IDX*32
#define HITSIP_TILES_RAM_POS 	TILES_END_RAM_POS
#define HITSIP_TILES_IDX	TILE_END_IDX


typedef enum {EMPTYTILE_IDX = 0, EMPTYTILE2_IDX,  FULLTILE_IDX, MISSTILE_IDX, TRANSPARENT_TILE_IDX, TILE_END_IDX} Tile_indexes ;
typedef enum {BLUE1_IDX = 51, BLUE2_IDX, BLUE3_IDX, BLUE4_IDX, BLUE5_IDX, RED_IDX, GREEN_IDX, WHITE_IDX, BLACK_IDX, CYAN_IDX, CYAN2_IDX}Color_indexes ;


u8 empty_tile[64] = {
		 BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,
		 BLACK_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,
		 BLACK_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,
		 BLACK_IDX,  WHITE_IDX,  BLUE3_IDX,  BLUE3_IDX,  BLUE3_IDX,  BLUE3_IDX,  BLUE3_IDX,  WHITE_IDX,
		 BLACK_IDX,  BLUE4_IDX,  WHITE_IDX,  BLUE4_IDX,  BLUE4_IDX,  BLUE4_IDX,  WHITE_IDX,  BLUE4_IDX,
		 BLACK_IDX,  BLUE3_IDX,  BLUE3_IDX,  WHITE_IDX,  WHITE_IDX,  WHITE_IDX,  BLUE3_IDX,  BLUE3_IDX,
		 BLACK_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,
		 BLACK_IDX,  BLUE5_IDX,  BLUE5_IDX,  BLUE5_IDX,  BLUE5_IDX,  BLUE5_IDX,  BLUE5_IDX,  BLUE5_IDX
};
u8 miss_tile[64] = {
		 BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,
		 BLACK_IDX,  WHITE_IDX,  BLACK_IDX,  BLACK_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,
		 BLACK_IDX,  BLACK_IDX,  WHITE_IDX, BLACK_IDX,  BLACK_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,
		 BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  WHITE_IDX,  BLACK_IDX,  BLACK_IDX, BLUE3_IDX,  WHITE_IDX,
		 BLACK_IDX,  BLUE4_IDX,  BLACK_IDX,  BLACK_IDX,  WHITE_IDX,  BLACK_IDX,  BLACK_IDX,  BLUE4_IDX,
		 BLACK_IDX,  BLUE3_IDX,  BLUE3_IDX,  BLACK_IDX,  BLACK_IDX,  WHITE_IDX,  BLACK_IDX,  BLACK_IDX,
		 BLACK_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLACK_IDX,  BLACK_IDX,  WHITE_IDX,  BLACK_IDX,
		 BLACK_IDX,  BLUE5_IDX,  BLUE5_IDX,  BLUE5_IDX,  BLUE5_IDX,  BLACK_IDX,  BLACK_IDX,  WHITE_IDX,
};

u8 hit_tile[64] = {
		 BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,
		 BLACK_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,   BLUE1_IDX,
		 BLACK_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,     BLUE2_IDX,  RED_IDX ,   RED_IDX ,   RED_IDX,
		 BLACK_IDX,  WHITE_IDX,  BLUE3_IDX,  BLUE3_IDX,    BLACK_IDX,  RED_IDX ,   RED_IDX ,   RED_IDX,
		 BLACK_IDX,  BLUE4_IDX,  BLUE4_IDX,   BLACK_IDX,   BLACK_IDX,   BLACK_IDX,  RED_IDX ,   RED_IDX ,
		 BLACK_IDX,  BLUE3_IDX,  BLUE3_IDX,   RED_IDX ,   BLACK_IDX,   BLACK_IDX, BLACK_IDX,   RED_IDX ,
		 BLACK_IDX,  BLUE2_IDX,   RED_IDX ,   RED_IDX ,    RED_IDX ,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,
		 BLACK_IDX,  BLUE5_IDX,   RED_IDX ,   RED_IDX ,    RED_IDX ,  RED_IDX ,   BLACK_IDX,   BLACK_IDX,
};
u8 full_tile[64] = {
		 BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,  BLACK_IDX,
		 BLACK_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE1_IDX,
		 BLACK_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE2_IDX,  BLUE1_IDX,  BLUE1_IDX,
		 BLACK_IDX,  WHITE_IDX,  BLUE3_IDX,  BLUE3_IDX,  BLUE1_IDX,  BLUE1_IDX, BLUE5_IDX,  BLUE5_IDX,
		 BLACK_IDX,  BLUE4_IDX,  WHITE_IDX,  BLUE1_IDX,  BLUE1_IDX,  BLUE5_IDX,  BLUE2_IDX,  BLUE2_IDX,
		 BLACK_IDX,  BLUE3_IDX,  BLUE3_IDX,  BLUE1_IDX,  BLUE5_IDX,  BLUE2_IDX,  BLUE3_IDX,  BLUE3_IDX,
		 BLACK_IDX,  BLUE2_IDX,  BLUE1_IDX,  BLUE5_IDX,  BLUE2_IDX,  BLUE3_IDX,  BLUE4_IDX,  BLUE4_IDX,
		 BLACK_IDX,  BLUE5_IDX,  BLUE1_IDX,  BLUE5_IDX,  BLUE2_IDX,  BLUE3_IDX,  BLUE4_IDX,  WHITE_IDX,
};

u8 transparent_tile[64] = {
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0
};



void configure_graphics_main(){
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE;
	BGCTRL[0] = BG_TILE_BASE(0) | BG_COLOR_256 | BG_MAP_BASE(1) | BG_32x32 | BG_PRIORITY_1;
	BGCTRL[1] = BG_TILE_BASE(0) | BG_COLOR_256 | BG_MAP_BASE(2) | BG_32x32 | BG_PRIORITY_0;
	VRAM_A_CR = VRAM_A_MAIN_BG | VRAM_ENABLE;

	//copy grit palette
	memcpy(BG_PALETTE, hitshipPal, hitshipPalLen);

	//add additional colors
	BG_PALETTE[BLUE1_IDX] = ARGB16(1,0,0,13);
	BG_PALETTE[BLUE2_IDX] = ARGB16(1,1,3,31);
	BG_PALETTE[BLUE3_IDX] = ARGB16(1,0,20,29);
	BG_PALETTE[BLUE4_IDX] = ARGB16(1,19,27,29);
	BG_PALETTE[BLUE5_IDX] = ARGB16(1,0,0,20);
	BG_PALETTE[RED_IDX] = ARGB16(1,31,0,0);
	BG_PALETTE[GREEN_IDX] = ARGB16(1,0,31,0);
	BG_PALETTE[WHITE_IDX] = ARGB16(1,31,31,31);
	BG_PALETTE[BLACK_IDX] = ARGB16(1,0,0,0);
	BG_PALETTE[CYAN_IDX] = ARGB16(1,0,15,15);
	BG_PALETTE[CYAN2_IDX] = ARGB16(1,0,10,31);


	memcpy(&BG_TILE_RAM(0)[EMPTYTILE_RAM_POS], empty_tile, 64);
	memcpy(&BG_TILE_RAM(0)[HITSIP_TILES_RAM_POS], hitshipTiles, 64*4); //copy 4 tiles
	memcpy(&BG_TILE_RAM(0)[MISSTILE_RAM_POS], miss_tile, 64);
	memcpy(&BG_TILE_RAM(0)[FULLTILE_RAM_POS], full_tile, 64);

	//initalize an empty game grid
	int i,j;
	for(i = 0; i<12; i = i + 1)
				for(j = 0; j < 16; j = j + 1)
					tile_shower(EMPTYTILE_IDX, BG_MAP_RAM(1),j,i);

	//init the upper background
	init_toplevel();
}

void init_toplevel(){
	int i,j;
		for(i = 0; i<12; i = i + 1)
					for(j = 0; j < 16; j = j + 1)
						tile_shower(TRANSPARENT_TILE_IDX, BG_MAP_RAM(2),j,i);
}

void show_land(Land_status status, int x, int y){
	switch(status){
	case HIT: 	tile_shower_2x2(HITSIP_TILES_IDX, BG_MAP_RAM(1),x,y); break;
	case MISS:	tile_shower(MISSTILE_IDX, BG_MAP_RAM(1),x,y); break;
	case FULL:	tile_shower(FULLTILE_IDX, BG_MAP_RAM(1),x,y); break;
	case EMPTY:	tile_shower(EMPTYTILE_IDX, BG_MAP_RAM(1),x,y); break;
	default: break;
	}
}

void show_land_toplevel(Land_status status, int x, int y){
	switch(status){
		case HIT: 	tile_shower_2x2(HITSIP_TILES_IDX, BG_MAP_RAM(2),x,y); break;
		case MISS:	tile_shower(MISSTILE_IDX, BG_MAP_RAM(2),x,y); break;
		case FULL:	tile_shower(FULLTILE_IDX, BG_MAP_RAM(2),x,y); break;
		case EMPTY:	tile_shower(EMPTYTILE_IDX, BG_MAP_RAM(2),x,y); break;
		case TRANSPARENT: tile_shower(TRANSPARENT_TILE_IDX,BG_MAP_RAM(2),x,y);
		default: break;
		}
}


void configure_graphics_sub(){
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG0_ACTIVE;
	BGCTRL_SUB[0] = BG_TILE_BASE(0) | BG_COLOR_256 | BG_MAP_BASE(1) | BG_32x32;
	VRAM_C_CR = VRAM_C_SUB_BG | VRAM_ENABLE;

	//copy grit palette
	memcpy(BG_PALETTE_SUB, hitshipPal, hitshipPalLen);

	//add additional colors
	BG_PALETTE_SUB[BLUE1_IDX] = ARGB16(1,0,0,13);
	BG_PALETTE_SUB[BLUE2_IDX] = ARGB16(1,1,3,31);
	BG_PALETTE_SUB[BLUE3_IDX] = ARGB16(1,0,20,29);
	BG_PALETTE_SUB[BLUE4_IDX] = ARGB16(1,19,27,29);
	BG_PALETTE_SUB[BLUE5_IDX] = ARGB16(1,0,0,20);
	BG_PALETTE_SUB[RED_IDX] = ARGB16(1,31,0,0);
	BG_PALETTE_SUB[GREEN_IDX] = ARGB16(1,0,31,0);
	BG_PALETTE_SUB[WHITE_IDX] = ARGB16(1,31,31,31);
	BG_PALETTE_SUB[BLACK_IDX] = ARGB16(1,0,0,0);
	BG_PALETTE_SUB[CYAN_IDX] = ARGB16(1,0,15,15);
	BG_PALETTE_SUB[CYAN2_IDX] = ARGB16(1,0,10,31);


	memcpy(&BG_TILE_RAM_SUB(0)[EMPTYTILE_RAM_POS], empty_tile, 64);
	memcpy(&BG_TILE_RAM_SUB(0)[HITSIP_TILES_RAM_POS], hitshipTiles, 64*4); //copy 4 tiles
	memcpy(&BG_TILE_RAM_SUB(0)[MISSTILE_RAM_POS], miss_tile, 64);
	memcpy(&BG_TILE_RAM_SUB(0)[FULLTILE_RAM_POS], full_tile, 64);

	//initalize an empty game grid
	int i,j;
	for(i = 0; i<12; i = i + 1)
				for(j = 0; j < 16; j = j + 1)
					tile_shower(EMPTYTILE_IDX, BG_MAP_RAM_SUB(1),j,i);
}

void show_land_sub(Land_status status, int x, int y){
	switch(status){
	case HIT: 	tile_shower_2x2(HITSIP_TILES_IDX, BG_MAP_RAM_SUB(1),x,y); break;
	case MISS:	tile_shower(MISSTILE_IDX, BG_MAP_RAM_SUB(1),x,y); break;
	case FULL:	tile_shower(FULLTILE_IDX, BG_MAP_RAM_SUB(1),x,y); break;
	case EMPTY:	tile_shower(EMPTYTILE_IDX, BG_MAP_RAM_SUB(1),x,y); break;
	default: break;
	}
}



const u16 V_SYM_MASK = 1<<11;
const u16 H_SYM_MASK  = 1<<10;

void tile_shower(u16 tile_index, u16* map, int grid_x, int grid_y){
	int upleft_x = grid_x*2;
	int upleft_y = grid_y*2;
	map[upleft_y * 32 + upleft_x] = tile_index;
	map[upleft_y * 32 + upleft_x+1] = tile_index | H_SYM_MASK;
	map[(upleft_y+1) * 32 + upleft_x] = tile_index | V_SYM_MASK;
	map[(upleft_y+1) * 32 + upleft_x+1] = tile_index | V_SYM_MASK | H_SYM_MASK;

}

void tile_shower_2x2(u16 tile_2x2_index, u16* map, int grid_x, int grid_y){
	int upleft_x = grid_x*2;
	int upleft_y = grid_y*2;
	map[upleft_y * 32 + upleft_x] = tile_2x2_index;
	map[upleft_y * 32 + upleft_x+1] = tile_2x2_index + 1;
	map[(upleft_y+1) * 32 + upleft_x] = tile_2x2_index + 2;
	map[(upleft_y+1) * 32 + upleft_x+1] = tile_2x2_index + 3;

}


void configure_map();
