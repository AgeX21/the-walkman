#include <nds.h>
#include "timer.h"
#include "graphics.h"
#include "sound.h"
#include "controls.h"
#include "sprite.h"

void timer_init()
{
    // Init timer for menu animations
    TIMER0_DATA = TIMER_FREQ_1024(2);
    TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
    irqSet(IRQ_TIMER0, &timer_menu_animations);

    TIMER1_DATA = TIMER_FREQ_1024(5);
    TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
    irqSet(IRQ_TIMER1, &timer_walk_animations);

    TIMER2_DATA = TIMER_FREQ_1024(10);
    TIMER2_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
    irqSet(IRQ_TIMER2, &timer_100ms_isr);
    irqEnable(IRQ_TIMER2);
}

void timer_menu_animations()
{   
 
    irqDisable(IRQ_TIMER0);
    // Change next frame displayed
    play_SFX(BUTTON);
    curr_wm_frame = WM_PLAY_1;
    // On release of button resume the music
    resume_music();
}

void timer_walk_animations()
{
    change_sprite(NEXT_SPRITE);
}

void timer_100ms_isr()
{   
    // Update walkman playing frame if necessary
    if(curr_wm_frame != WM_BASE && curr_wm_frame != WM_PAUSE && curr_wm_frame != WM_NEXT && curr_wm_frame != WM_PREV && curr_wm_frame != WM_SPECIAL)
    {
        // Increment the frame
        curr_wm_frame++;

        // Check if the frame has exceeded WM_PLAY_8, and loop back to WM_PLAY_1
        if (curr_wm_frame > WM_PLAY_8) 
        {
            curr_wm_frame = WM_PLAY_1;
        }
        animate_menu(curr_wm_frame);
    }

    // Always update the menu background frame
    curr_menu_bg_frame++;
    if(curr_menu_bg_frame > MENU_BG_13)
    {
        curr_menu_bg_frame = MENU_BG_1;
    }
    animate_menu(curr_menu_bg_frame);

}
