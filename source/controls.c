#include <nds.h>
#include <stdio.h>
#include "controls.h"

player_t* player;

void controls_init(player_t* player_)
{
    REG_KEYCNT = (1<<14) | KEY_A;
    irqSet(IRQ_KEYS, &controls_interrupt_handler);
    irqEnable(IRQ_KEYS);
    player = player_;
    key_pressed_r = false;
    key_pressed_l = false;
    key_pressed_d = false;
    key_pressed_u = false;
    key_pressed_a = false;
    change_song = false;
    direction = 0;
}

// Function to check if a touch input is within a rectangle
bool isInRectangle(touchPosition touch, u16 x1, u16 x2, u16 y1, u16 y2)
{
    return (touch.px >= x1 && touch.px <= x2 && touch.py >= y1 && touch.py <= y2);
}

void controls_handler()
{
        // Read the touch position and the state of the keys
    touchPosition touch;
    scanKeys();
    int keys = keysHeld();

    if(keys & KEY_A) {}
    else key_pressed_a = false;

    if(keys & KEY_RIGHT)
    {
        key_pressed_l = false;
        key_pressed_d = false;
        key_pressed_u = false;
        player_move(player, 1, 0, RELATIVE);
        if(key_pressed_r == false)
        {
            key_pressed_r = true;
            swiWaitForVBlank();
            change_sprite(RIGHT);
            irqEnable(IRQ_TIMER1);
        }
    }
    /*else if (key_pressed_r == true)
    {
        key_pressed_r = false;
        if (direction == 3){direction = 0; irqDisable(IRQ_TIMER1);}
    }
    */

    else if(keys & KEY_LEFT)
    {
        key_pressed_r = false;
        key_pressed_d = false;
        key_pressed_u = false;
        player_move(player, -1, 0, RELATIVE);
        if(key_pressed_l == false)
        {
            key_pressed_l = true;
            swiWaitForVBlank();
            change_sprite(LEFT);
            irqEnable(IRQ_TIMER1);
        }
    }
    /*else if (key_pressed_l == true)
    {
        key_pressed_l = false;
        if (direction == 2){direction = 0; irqDisable(IRQ_TIMER1);}
    }
    */
    
    else if(keys & KEY_UP)
    {
        key_pressed_r = false;
        key_pressed_l = false;
        key_pressed_d = false;
        player_move(player, 0, -1, RELATIVE);
        if(key_pressed_u == false)
        {
            key_pressed_u = true;
            swiWaitForVBlank();
            change_sprite(BACKWARD);
            irqEnable(IRQ_TIMER1);
        }
    }
    /*else if (key_pressed_u == true)
    {
        key_pressed_u = false;
        if (direction == 4){direction = 0; irqDisable(IRQ_TIMER1);}
    }
    */
    
    else if(keys & KEY_DOWN)
    {
        key_pressed_r = false;
        key_pressed_l = false;
        key_pressed_u = false;
        player_move(player, 0, 1, RELATIVE);
        if(key_pressed_d == false)
        {
            key_pressed_d = true;
            swiWaitForVBlank();
            change_sprite(FORWARD);
            irqEnable(IRQ_TIMER1);
        }
    }
    /*else if (key_pressed_d == true)
    {
        key_pressed_d = false;
        if (direction == 1){direction = 0; irqDisable(IRQ_TIMER1);}


    }
    */
    else 
    {
        key_pressed_r = false;
        key_pressed_l = false;
        key_pressed_d = false;
        key_pressed_u = false;
        change_sprite(player->animation%4);
        irqDisable(IRQ_TIMER1);
    }
}

void touchpad_handler()
{
    // Read the touch position and the state of the keys
    touchPosition touch;
    scanKeys();
    int keys = keysHeld();

    if (keys & KEY_TOUCH) {

        touchRead(&touch);

        if (!touch_pressed) {
            // New touch detected
            touch_pressed = true;
            
            // Check if touch is within Special button boundaries
            if(isInRectangle(touch,79,92,144,167) && curr_wm_frame != WM_SPECIAL) 
            {
                play_SFX(BUTTON);

                animate_menu(WM_SPECIAL);
                curr_wm_frame = WM_SPECIAL;

                trigger_handler();
            }
            // Check if touch is within Pause button
            else if(isInRectangle(touch, 103, 142, 30, 51) && !isInRectangle(touch, 138, 142, 30, 34) && curr_wm_frame != WM_PAUSE)
            {
                play_SFX(BUTTON);
                pause_music();

                animate_menu(WM_PAUSE);
                curr_wm_frame = WM_PAUSE;
            }
            // Check if touch is within Play button
            else if(isInRectangle(touch, 138, 177, 13, 34) && (curr_wm_frame == WM_PAUSE || curr_wm_frame == WM_PREV || curr_wm_frame == WM_NEXT || curr_wm_frame == WM_SPECIAL || curr_wm_frame == WM_BASE))
            {   
                play_SFX(BUTTON);
                resume_music();

                animate_menu(WM_PLAY_1);
                curr_wm_frame = WM_PLAY_1;
            }
            // Check if touch is within Prev button
            else if(isInRectangle(touch, 65, 89, 56, 69) && !isInRectangle(touch, 84, 89, 56, 60) && curr_wm_frame != WM_PREV)
            {
                play_SFX(BUTTON);
                skip_to_previous_track();
                pause_music();

                animate_menu(WM_PREV);
                curr_wm_frame = WM_PREV;

            }
            // Check if touch is within Next button
            else if(isInRectangle(touch, 84, 107, 47, 60) && !isInRectangle(touch, 103, 107, 47, 51) && curr_wm_frame != WM_NEXT)
            {
                play_SFX(BUTTON);
                skip_to_next_track();
                pause_music();

                animate_menu(WM_NEXT);
                curr_wm_frame = WM_NEXT;
            }
        }
    } else {
        // No touch detected or touch ended, reset the touch state
        if(touch_pressed)
        {
            touch_pressed = false;
        }
        if(curr_wm_frame == WM_SPECIAL || curr_wm_frame == WM_NEXT || curr_wm_frame == WM_PREV) 
        {
            // Launch animation delay 
            irqEnable(IRQ_TIMER0);
        }
    }
}

void trigger_handler()
{
    background_switch();
    if(bg_num == 0) player_move(player, 60, 130, ABSOLUTE);
    else player_move(player, 20, 355, ABSOLUTE);
    change_sprite(FORWARD);
    key_pressed_d = false;
    key_pressed_u = false;
    key_pressed_l = false;
    key_pressed_r = false;
}

void controls_interrupt_handler()
{
        // Read the touch position and the state of the keys
    u16 keys = ~(REG_KEYINPUT);

    if(keys & KEY_A) 
    {
        if(key_pressed_a == false)
        {
            key_pressed_a = true;
            int temp = get_collision(player, player->x, player->y, ABSOLUTE);
            if (temp == TRIGGER)
            {
                trigger_handler();
            }
        }
    }
}