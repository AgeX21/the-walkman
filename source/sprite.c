#include <nds.h>
#include "sprite.h"
#include "player.h"
#include "player0.h"
#include "player1.h"
#include "player2.h"
#include "player3.h"
#include "player4.h"
#include "player5.h"
#include "player6.h"
#include "player7.h"
#include "player8.h"
#include "player9.h"
#include "player10.h"
#include "player11.h"
#include "player12.h"
#include "player13.h"
#include "player14.h"
#include "player15.h"
#include "player16.h"
#include "player17.h"
#include "player18.h"
#include "player19.h"
#include "player20.h"
#include "player21.h"
#include "player22.h"
#include "player23.h"

#define SPRITE_SIZE 32*32

player_t* player_init(u16 x, u16 y)
{
	VRAM_F_CR = VRAM_ENABLE | VRAM_F_MAIN_SPRITE_0x06400000;
	player_t* player = malloc(sizeof(player_t));

	player->x = x;
	player->y = y;
	player->sprite_num = 0;
	player->priority = 2;
	player->animation = 0;

	oamInit(&oamMain, SpriteMapping_1D_32, false);
	player->gfx = oamAllocateGfx(&oamMain, SpriteSize_16x32, SpriteColorFormat_256Color );
/*
	dmaCopy(player0Pal,SPRITE_PALETTE,player0PalLen);
	dmaCopy(player1Pal,&SPRITE_PALETTE[(player0PalLen/2)],player1PalLen);
	dmaCopy(player2Pal,&SPRITE_PALETTE[(player0PalLen/2)*2],player2PalLen);
	dmaCopy(player3Pal,&SPRITE_PALETTE[(player0PalLen/2)*3],player3PalLen);
	dmaCopy(player4Pal,&SPRITE_PALETTE[(player0PalLen/2)*4],player4PalLen);
	dmaCopy(player5Pal,&SPRITE_PALETTE[(player0PalLen/2)*5],player5PalLen);
	dmaCopy(player6Pal,&SPRITE_PALETTE[(player0PalLen/2)*6],player6PalLen);
	dmaCopy(player7Pal,&SPRITE_PALETTE[(player0PalLen/2)*7],player7PalLen);
	dmaCopy(player8Pal,&SPRITE_PALETTE[(player0PalLen/2)*8],player8PalLen);
	dmaCopy(player9Pal,&SPRITE_PALETTE[(player0PalLen/2)*9],player9PalLen);
	dmaCopy(player10Pal,&SPRITE_PALETTE[(player0PalLen/2)*10],player10PalLen);
	dmaCopy(player11Pal,&SPRITE_PALETTE[(player0PalLen/2)*11],player11PalLen);
	dmaCopy(player4Pal,&SPRITE_PALETTE[(player0PalLen/2)*12],player12PalLen);
	dmaCopy(player5Pal,&SPRITE_PALETTE[(player0PalLen/2)*13],player13PalLen);
	dmaCopy(player6Pal,&SPRITE_PALETTE[(player0PalLen/2)*14],player14PalLen);
	dmaCopy(player7Pal,&SPRITE_PALETTE[(player0PalLen/2)*15],player15PalLen);
	//dmaCopy(hexagonPal,&SPRITE_PALETTE[arrowPalLen/2],hexagonPalLen);
*/
	animation_map[0] = player0Tiles;
	animation_map[1] = player1Tiles;
	animation_map[2] = player2Tiles;
	animation_map[3] = player3Tiles;
	animation_map[4] = player4Tiles;
	animation_map[5] = player5Tiles;
	animation_map[6] = player6Tiles;
	animation_map[7] = player7Tiles;
	animation_map[8] = player8Tiles;
	animation_map[9] = player9Tiles;
	animation_map[10] = player10Tiles;
	animation_map[11] = player11Tiles;
	animation_map[12] = player12Tiles;
	animation_map[13] = player13Tiles;
	animation_map[14] = player14Tiles;
	animation_map[15] = player15Tiles;
	animation_map[16] = player16Tiles;
	animation_map[17] = player17Tiles;
	animation_map[18] = player18Tiles;
	animation_map[19] = player19Tiles;
	animation_map[20] = player20Tiles;
	animation_map[21] = player21Tiles;
	animation_map[22] = player22Tiles;
	animation_map[23] = player23Tiles;

	pal_map[0] = player0Pal;
	pal_map[1] = player1Pal;
	pal_map[2] = player2Pal;
	pal_map[3] = player3Pal;
	pal_map[4] = player4Pal;
	pal_map[5] = player5Pal;
	pal_map[6] = player6Pal;
	pal_map[7] = player7Pal;
	pal_map[8] = player8Pal;
	pal_map[9] = player9Pal;
	pal_map[10] = player10Pal;
	pal_map[11] = player11Pal;
	pal_map[12] = player12Pal;
	pal_map[13] = player13Pal;
	pal_map[14] = player14Pal;
	pal_map[15] = player15Pal;
	pal_map[16] = player16Pal;
	pal_map[17] = player17Pal;
	pal_map[18] = player18Pal;
	pal_map[19] = player19Pal;
	pal_map[20] = player20Pal;
	pal_map[21] = player21Pal;
	pal_map[22] = player22Pal;
	pal_map[23] = player23Pal;

	dmaCopy(player0Tiles, player->gfx, 32*16);

	dmaCopy(player0Pal, SPRITE_PALETTE, 256);



	oamSet(&oamMain, 	// oam handler
				0,				// Number of sprite
				x, y,			// Coordinates
				2,				// Priority
				0,				// Palette to use
				SpriteSize_16x32,			// Sprite size
				SpriteColorFormat_256Color,	// Color format
				player->gfx,			// Loaded graphic to display
				-1,				// Affine rotation to use (-1 none)
				false,			// Double size if rotating
				false,			// Hide this sprite
				false, false,	// Horizontal or vertical flip
				false			// Mosaic
				);

	player_ = player;
	return player;
}

void player_move(player_t* player, int x, int y, u16 absolute)
{
	if(absolute == RELATIVE)
	{
		int i = 0;
		int j = 0;
		int temp = NOTHING;
		int increment = (x >= 0)? 1 : -1;
		while(i < x*increment)
		{
			temp = get_collision(player, increment, 0, RELATIVE);
			if (temp > NOTHING) temp = collision_handler(temp);
			if (temp == ERROR) return;
			if (temp > WALL) i++;
			else break;
		}
		x = i*increment;
		player->x += x;
		//player->x = (player->x <= 0) ? 0 : player->x;
		//player->x = (player->x > 512-32+64) ? 512-32+64 : player->x;

		increment = (y >= 0)? 1 : -1;
		while(j < y*increment)
		{
			temp = get_collision(player, 0, increment, absolute);
			if (temp > NOTHING) temp = collision_handler(temp);
			if (temp == ERROR) return;
			if (temp != WALL) j++;
			else break;
		}
		y = j*increment;
		player->y += y;
	    //player->y = (player->y <= 0) ? 0 : player->y;
	    //player->y = (player->y > 512-32) ? 512-32: player->y;
	}

	else 
	{
		/*
		int temp = get_collision(player, 0, 1, ABSOLUTE);
		if (temp > NOTHING) temp = collision_handler(temp);
		if (temp == ERROR) return;
		if (temp == WALL) return;
		player->x = (absolute == 1) ? x : player->x + x;
		player->y = (absolute == 1) ? y : player->y + y;
		*/
		player->x = x;
		player->y = y;
	}

    update_sprite_position(player);
}


int get_collision(player_t* player, int x, int y, u16 absolute)
{
	if(absolute == ABSOLUTE)
	{
		int i, j;
		for (i = x; i < x+16; ++i)
		{
			for (j = y-1; j < y+33; ++j)
			{
				if(i < 512 && j < 512 && j >= 0)
				{
				u16 color = get_collision_color(i, j);
				if(color == COLOR_TRIGGER) return TRIGGER;
				}
			}
		}
		return NOTHING;
	}

	else 
	{
		if(x != 0) 
		{
			int offset = 8 + 8 * x;
			int i = player->y+24;
			if(player->x + x < 0 || player->x + x > 512-32+16) {return WALL;}
			int temp;
			for (; i < player->y + 32; i++)
			{
				u16 color = get_collision_color(player->x+x+offset, i);
				if(color == COLOR_COLLISION) return WALL;
			}
			return NOTHING;
		}
		
		if (y != 0)
		{
			int offset = 28 + 4 * y;
			int i;
			if(player->y + y < 0 || player->y + y > 512-32) return WALL;
			for (i = player->x; i < player->x + 16; i++)
			{
				u16 color = get_collision_color(i, player->y+y+offset);
				if(color == COLOR_COLLISION) return WALL;
			}
			return NOTHING;
		}
		return NOTHING;
	}
}

int collision_handler(int collision)
{
	return collision;
	switch(collision)
	{
		//case TRIGGER_0 :
			//do_something();
		//	return NOTHING;
		//	break;
		default:
			break;
	}
	return collision;
}


void change_sprite(int num)
{
	if(num < 0)
	{
		player_->animation = (player_->animation + 4) % NUM_SPRITE;
		//printf("%d\n", player_->animation);
		dmaCopy(animation_map[player_->animation],player_->gfx,32*16);
		dmaCopy(pal_map[player_->animation], SPRITE_PALETTE, 256);

		update_sprite_position(player_);
		return;
	}
	else if (num <= NUM_SPRITE)
	{
		player_->animation = num;
		dmaCopy(animation_map[player_->animation],player_->gfx,32*16);
		dmaCopy(pal_map[player_->animation], SPRITE_PALETTE, 256);

		update_sprite_position(player_);
	}
}
