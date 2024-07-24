#include <nds.h>
#include "graphics.h"
#include "timer.h"
#include "controls.h"
#include "map.h"
#include "dungeon.h"
#include "collision.h"
#include "collision2.h"
#include "menu.h"
#include "cityfront.h"
#include "dungeonFront.h"

#define DISP_BITMAP_SIZE 256*192/4
#define DISP_SIZE 256*192

// Frame variable that stores the current frame of the menu displayed
#define MAP_SIZE 32*32
#define TILE_SIZE 8

menu_png_frame curr_wm_frame = WM_BASE;
menu_png_frame curr_menu_bg_frame = MENU_BG_1;

void graphics_init()
{
    // Top Screen - Tiled
    background_x = 0;
    background_y = 0;
	bg_num = 0;

	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_BG_0x06020000;
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;
    BGCTRL[3] = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2) | BG_PRIORITY(3);
    BGCTRL[2] = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(8) | BG_TILE_BASE(10) | BG_PRIORITY(1);

	REG_BG0HOFS = background_x;
	REG_BG0VOFS = background_y;

	bg_map[0] = mapMap;
	bg_map[1] = mapMap+32*32;
	bg_map[2] = mapMap+32*32*2;
	bg_map[3] = mapMap+32*32*3;

	bg_map[4] = dungeonMap;
	bg_map[5] = dungeonMap+32*32;
	bg_map[6] = dungeonMap+32*32*2;
	bg_map[7] = dungeonMap+32*32*3;

	bg_map[8] = cityfrontMap;
	bg_map[9] = cityfrontMap+32*32;
	bg_map[10] = cityfrontMap+32*32*2;
	bg_map[11] = cityfrontMap+32*32*3;

	bg_map[12] = dungeonFrontMap;
	bg_map[13] = dungeonFrontMap+32*32;
	bg_map[14] = dungeonFrontMap+32*32*2;
	bg_map[15] = dungeonFrontMap+32*32*3;

    swiCopy(mapTiles, BG_TILE_RAM(2), mapTilesLen/2);
    swiCopy(mapPal, BG_PALETTE, mapPalLen/2);
    swiCopy(bg_map[0], BG_MAP_RAM(0), MAP_SIZE);
    swiCopy(bg_map[1], BG_MAP_RAM(1), MAP_SIZE);
    swiCopy(bg_map[2], BG_MAP_RAM(2), MAP_SIZE);
    swiCopy(bg_map[3], BG_MAP_RAM(3), MAP_SIZE);

    swiCopy(dungeonTiles, BG_TILE_RAM(6), dungeonTilesLen/2);
	swiCopy(bg_map[4], BG_MAP_RAM(4), MAP_SIZE);
    swiCopy(bg_map[5], BG_MAP_RAM(5), MAP_SIZE);
    swiCopy(bg_map[6], BG_MAP_RAM(6), MAP_SIZE);
    swiCopy(bg_map[7], BG_MAP_RAM(7), MAP_SIZE);

    swiCopy(cityfrontTiles, BG_TILE_RAM(10), cityfrontTilesLen/2);
	swiCopy(bg_map[8], BG_MAP_RAM(8), MAP_SIZE);
    swiCopy(bg_map[9], BG_MAP_RAM(9), MAP_SIZE);
    swiCopy(bg_map[10], BG_MAP_RAM(10), MAP_SIZE);
    swiCopy(bg_map[11], BG_MAP_RAM(11), MAP_SIZE);

    swiCopy(dungeonFrontTiles, BG_TILE_RAM(13), dungeonFrontTilesLen/2);
	swiCopy(bg_map[12], BG_MAP_RAM(12), MAP_SIZE);
    swiCopy(bg_map[13], BG_MAP_RAM(13), MAP_SIZE);
    swiCopy(bg_map[14], BG_MAP_RAM(14), MAP_SIZE);
    swiCopy(bg_map[15], BG_MAP_RAM(15), MAP_SIZE);
/*
    swiCopy(collisionTiles, BG_TILE_RAM(7), collisionTilesLen/2);
    swiCopy(collisionPal, collision_palette, collisionPalLen/2);
    swiCopy(collisionMap, BG_MAP_RAM(12), MAP_SIZE);
    swiCopy(collisionMap+32*32, BG_MAP_RAM(13), MAP_SIZE);
    swiCopy(collisionMap+32*32*2, BG_MAP_RAM(14), MAP_SIZE);
    swiCopy(collisionMap+32*32*3, BG_MAP_RAM(15), MAP_SIZE);
*/
    // Bottom Screen - Rotoscale

	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B8_256x256 | BG_PRIORITY(0); // BG_BMP_BASE(16) is the start of VRAM C
    BGCTRL_SUB[3] = BG_BMP_BASE(3) | BgSize_B8_256x256 | BG_PRIORITY(1); // Starts 3x16KB after the beginning of VRAM C

	//Affine Marix Transformation for BG2
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    //Affine Marix Transformation for BG3
    REG_BG3PA_SUB = 256;
    REG_BG3PC_SUB = 0;
    REG_BG3PB_SUB = 0;
    REG_BG3PD_SUB = 256;

    // Loading the menu palette
    memcpy(BG_PALETTE_SUB, menuPal, menuPalLen);

    // Loading the backgrounds
	memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[0], DISP_SIZE);
    memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_1*DISP_BITMAP_SIZE], DISP_SIZE);
}

// Function that updates the display based on the next frame
void animate_menu(menu_png_frame next_frame)
{
    switch(next_frame)
    {
        case WM_BASE:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[0], DISP_SIZE);

            break;
        case WM_PAUSE:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_PAUSE*DISP_BITMAP_SIZE], DISP_SIZE);
			
            break;
        case WM_PLAY_1:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_PLAY_1*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case WM_PLAY_2:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_PLAY_2*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case WM_PLAY_3:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_PLAY_3*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case WM_PLAY_4:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_PLAY_4*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case WM_PLAY_5:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_PLAY_5*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case WM_PLAY_6:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_PLAY_6*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case WM_PLAY_7:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_PLAY_7*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case WM_PLAY_8:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_PLAY_8*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case WM_PREV:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_PREV*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case WM_NEXT:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_NEXT*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case WM_SPECIAL:
            memcpy(BG_BMP_RAM_SUB(0), &menuBitmap[WM_SPECIAL*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_1:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_1*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_2:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_2*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_3:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_3*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_4:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_4*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_5:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_5*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_6:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_6*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_7:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_7*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_8:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_8*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_9:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_9*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_10:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_10*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_11:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_11*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_12:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_12*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        case MENU_BG_13:
            memcpy(BG_BMP_RAM_SUB(3), &menuBitmap[MENU_BG_13*DISP_BITMAP_SIZE], DISP_SIZE);

            break;
        default:
            break;
    }

}

/*
    move the background
*/
void move_background(u16 nb, int x, int y, u16 absolute)
{
    background_x = (absolute == 1) ? x : background_x + x;
    background_x = (background_x <= 0) ? 0 : background_x;
    background_x = (background_x > 256) ? 256 : background_x;

    background_y = (absolute == 1) ? y : background_y + y;
    background_y = (background_y <= 0) ? 0 : background_y;
    //background_y = (background_y > 256) ? 256 : background_y;
    switch(nb)
    {
        case 0:
            REG_BG0HOFS = background_x;
            REG_BG0VOFS = background_y;
            break;
        case 1:
            REG_BG1HOFS = background_x;
            REG_BG1VOFS = background_y;
            break;
        case 2:
            REG_BG2HOFS = background_x;
            REG_BG2VOFS = background_y;
            break;
        case 3:
            REG_BG3HOFS = background_x;
            REG_BG3VOFS = background_y;
            break;
    }
}

void update_sprite_position(player_t* player)
{
    int x, y;
    if (player->x > 112 && player-> x < 512-144)
        x = 112;
    else x = (player->x > 256) ? player->x - 256: player->x;
    if (player->y > 80 && player-> y < 512-96-16)
        y = 80;
    else y = (player->y > 256) ? player->y - 320: player->y;
    move_background(2, player->x-x, player->y-y, ABSOLUTE);
    move_background(3, player->x-x, player->y-y, ABSOLUTE);

    x = (x > 256-16) ? 256-16 : x;
    y = (y > 192-16) ? 192-16 : y;

    oamSet(&oamMain,    // oam handler
                player->sprite_num,             // Number of sprite
                x, y,                           // Coordinates
                player->priority,               // Priority
                0,              // Palette to use
                SpriteSize_16x32,               // Sprite size
                SpriteColorFormat_256Color,      // Color format
                player->gfx,                    // Loaded graphic to display
                -1,                             // Affine rotation to use (-1 none)
                false,                          // Double size if rotating
                false,                          // Hide this sprite
                false, false,                   // Horizontal or vertical flip
                false                           // Mosaic
                );
}


void background_switch()
{
	bg_num = (bg_num + 1) % 2;
	switch(bg_num)
	{
		case 0:
		    //swiCopy(mapTiles, BG_TILE_RAM(1), dungeonTilesLen/2);
			oamInit(&oamMain, SpriteMapping_1D_32, false);
    		BGCTRL[3] = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(2) | BG_PRIORITY(3);
    		BGCTRL[2] = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(8) | BG_TILE_BASE(10) | BG_PRIORITY(1);
		    swiCopy(mapPal, BG_PALETTE, mapPalLen/2);

		    //swiCopy(bg_map[0], BG_MAP_RAM(0), MAP_SIZE);
		    //swiCopy(bg_map[1], BG_MAP_RAM(1), MAP_SIZE);
		    //swiCopy(bg_map[2], BG_MAP_RAM(2), MAP_SIZE);
		    //swiCopy(bg_map[3], BG_MAP_RAM(3), MAP_SIZE);
			break;
		case 1:
			//swiCopy(dungeonTiles, BG_TILE_RAM(1), dungeonTilesLen/2);
			oamInit(&oamMain, SpriteMapping_1D_32, false);
			BGCTRL[3] = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(4) | BG_TILE_BASE(6) | BG_PRIORITY(3);
			BGCTRL[2] = BG_64x64 | BG_COLOR_256 | BG_MAP_BASE(12) | BG_TILE_BASE(13) | BG_PRIORITY(1);
			swiCopy(dungeonPal, BG_PALETTE, dungeonPalLen/2);
			//swiCopy(bg_map[4], BG_MAP_RAM(4), MAP_SIZE);
		    //swiCopy(bg_map[5], BG_MAP_RAM(5), MAP_SIZE);
		    //swiCopy(bg_map[6], BG_MAP_RAM(6), MAP_SIZE);
		    //swiCopy(bg_map[7], BG_MAP_RAM(7), MAP_SIZE);
			break;
	}

}

u16 get_collision_color(int x, int y)
{
	int tile_x = (x / TILE_SIZE) % 32;
    int tile_offset_x = x % TILE_SIZE;
    int tile_y = (y / TILE_SIZE) % 32;
    int tile_offset_y = y % TILE_SIZE;
    int a = (x >= 256) ? 1 : 0;
    int b = (y >= 256) ? 2 : 0;
	switch(bg_num)
	{
		case 0:
		{
		    u16 tile_num = (collisionMap+(a+b)*32*32)[tile_x+tile_y*32];
		    char palette_index = ((char*)collisionTiles)[64*tile_num+tile_offset_x+tile_offset_y*8];
		    return collisionPal[palette_index];
			break;
		}
		case 1:
		{
		    u16 tile_num = (collision2Map+(a+b)*32*32)[tile_x+tile_y*32];
		    char palette_index = ((char*)collision2Tiles)[64*tile_num+tile_offset_x+tile_offset_y*8];
		    return collision2Pal[palette_index];
			break;
		}
	}

    
}
