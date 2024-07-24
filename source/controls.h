#include <nds.h>
#include <stdio.h>
#include "sound.h"
#include "graphics.h"
#include "sprite.h"

#ifndef CONTROLS
#define CONTROLS

// Static variable to keep track of the touch state
static bool touch_pressed = false;
bool key_pressed_r;
bool key_pressed_l;
bool key_pressed_u;
bool key_pressed_d;
bool key_pressed_a;
bool change_song;
int direction;

/*
	Define ISR function : control_handler()
*/ 
void controls_init(player_t* player_);

/*
	Handles the touchpad input trough libnds
*/
void touchpad_handler();

/*
	Check for button pressed and touchscreen input :
		button pressed :
			- key : call player_move
			- button a : ...

		touchscreen :
			- check color for function to call
*/
void controls_handler();

void controls_interrupt_handler();

void timer_menu_animations();

bool isInRectangle(touchPosition touch, u16 x1, u16 x2, u16 y1, u16 y2);

void trigger_handler();

#endif