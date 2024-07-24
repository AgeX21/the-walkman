/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "graphics.h"
#include "sound.h"
#include "controls.h"
#include "timer.h"
#include "sprite.h"
#include "utils.h"

player_t* player;

void init_main()
{
    sound_init();
    graphics_init();
    timer_init();
    player = player_init(50, 130);
    controls_init(player);
    
}

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

    //consoleDemoInit();
    init_main();
    scanKeys();

    while(1)
    {
        
    	oamUpdate(&oamMain);
        touchpad_handler();
        controls_handler();
        swiWaitForVBlank();	
    }

    return 0;
}

