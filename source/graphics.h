#include <nds.h>
#include <stdio.h>
#include "utils.h"

#ifndef GRAPHICS
#define GRAPHICS

#define BACKGROUND_NUM 8
#define PALETTE_NUM 16
#define BACKGROUND_COLLISION 3

#define COLOR_COLLISION 0x001F
#define COLOR_NOTHING 0xFFFF
#define COLOR_TRIGGER 0x03FF

#define ABSOLUTE 1
#define RELATIVE 0

// Typedef that matches the frame to the actual order of pngs in the combined png
typedef enum {
    WM_BASE,
	WM_SPECIAL,
	WM_PREV,
	WM_NEXT,
	WM_PAUSE,
	WM_PLAY_1,
    WM_PLAY_2,
    WM_PLAY_3,
    WM_PLAY_4,
    WM_PLAY_5,
    WM_PLAY_6,
    WM_PLAY_7,
    WM_PLAY_8,
	MENU_BG_1,
    MENU_BG_2,
    MENU_BG_3,
    MENU_BG_4,
    MENU_BG_5,
    MENU_BG_6,
    MENU_BG_7,
    MENU_BG_8,
    MENU_BG_9,
    MENU_BG_10,
    MENU_BG_11,
    MENU_BG_12,
    MENU_BG_13,
    MENU_NUMBER_FRAMES
} menu_png_frame;

extern menu_png_frame curr_wm_frame;
extern menu_png_frame curr_menu_bg_frame;

int background_x;
int background_y;
int bg_num;

// contains every pointer to the different map        have a separate map to know which background equals to what bg_map+size starting index or have a function with a size_map* that calculate the correct index based on an enum
/*
	0 : ...
	1 : ...
	5 : ...
	...
*/
short** bg_map[BACKGROUND_NUM];
short collision_palette[PALETTE_NUM];

/*
	initialize VRAM, background, Map... (try to load everything to memory)

*/

void graphics_init();

/*
	check the position of the player and the position of the background and update the corresponding object
*/
void update_sprite_position(player_t* player);


/*
	move the background
*/
void move_background(u16 nb, int x, int y, u16 absolute);

void animate_menu(menu_png_frame frame);

void background_switch();

u16 get_collision_color(int x, int y);

#endif