#include <nds.h>
#include "utils.h"
#include "graphics.h"

#ifndef CUSTOM_SPRITE
#define CUSTOM_SPRITE

#define NUM_SPRITE 24

#define ERROR -1
#define WALL 0
#define NOTHING 1
#define TRIGGER 2

#define NEXT_SPRITE -1
#define FORWARD 0
#define BACKWARD 3
#define RIGHT 2
#define LEFT 1

player_t* player_;
short** animation_map[NUM_SPRITE];
short** pal_map[NUM_SPRITE];


player_t* player_init(u16 x, u16 y);


/*
 *	@brief modify the player x and y coordinate
 *
 *	@param	player_t 		player
 *	@param	x				x offset
 *  @param	y 				y offset
 *  @param 	absolution		0 : relative, 1 : absolution
 */
void player_move(player_t* player, int x, int y, u16 absolute);

/*
	check for collision in a certain direction
*/

int get_collision(player_t* player, int x, int y, u16 absolute);

int collision_handler(int collision);

void change_sprite(int num);

#endif
