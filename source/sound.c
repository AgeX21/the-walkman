#include <nds.h>
#include <stdio.h>
#include "sound.h"

// Current music played variable
music current_track = ENJOY;

void sound_init()
{
    mmInitDefaultMem((mm_addr)soundbank_bin);

    // Load each module
    mmLoad(MOD_00ENJOY);
    mmLoad(MOD_02_MR_DROICHEN);
    mmLoad(MOD_BADAPPLE);
    mmLoad(MOD_BLUE_PHOEBE_LOVE);
    mmLoad(MOD_CODA___SPINER);
    mmLoad(MOD_MAHOGANY___SLEEP_WELL);
    mmLoad(MOD_MUSIC_FOR_CHIPS);
    mmLoad(MOD_PAPER___DRIP);
    mmLoad(MOD_SMH___ON_THE_MOON);

    // Load effects
    mmLoadEffect(SFX_WALKMANCLICK);
    
    // Launch main theme music and pause
    play_music(ENJOY);
    pause_music();

}

void play_SFX(sfx sound)
{
    switch(sound)
    {
        case BUTTON:
            mmEffect(SFX_WALKMANCLICK);
            break;
        default:
            break;
    }
}


void play_music(music music)
{
    switch(music)
    {
        case ENJOY:
            mmStart(MOD_00ENJOY, MM_PLAY_LOOP);
            //Set module volume (range 0-1024) using the function mmSetVolume()
            mmSetModuleVolume(768);
            break;
        case MR_DROICHEN:
            mmStart(MOD_02_MR_DROICHEN, MM_PLAY_LOOP);
            //Set module volume (range 0-1024) using the function mmSetVolume()
            mmSetModuleVolume(768);
            break;
        case BADAPPLE:
            mmStart(MOD_BADAPPLE, MM_PLAY_LOOP);
            //Set module volume (range 0-1024) using the function mmSetVolume()
            mmSetModuleVolume(768);
            break;
        case BLUE_PHOEBE_LOVE:
            mmStart(MOD_BLUE_PHOEBE_LOVE, MM_PLAY_LOOP);
            //Set module volume (range 0-1024) using the function mmSetVolume()
            mmSetModuleVolume(768);
            break;
        case CODA_SPINER:
            mmStart(MOD_CODA___SPINER, MM_PLAY_LOOP);
            //Set module volume (range 0-1024) using the function mmSetVolume()
            mmSetModuleVolume(768);
            break;
        case SLEEP_WELL:
            mmStart(MOD_MAHOGANY___SLEEP_WELL, MM_PLAY_LOOP);
            //Set module volume (range 0-1024) using the function mmSetVolume()
            mmSetModuleVolume(768);
            break;
        case MUSIC_FOR_CHIPS:
            mmStart(MOD_MUSIC_FOR_CHIPS, MM_PLAY_LOOP);
            //Set module volume (range 0-1024) using the function mmSetVolume()
            mmSetModuleVolume(768);
            break;
        case MOD_PAPER_DRIP:
            mmStart(MOD_PAPER___DRIP, MM_PLAY_LOOP);
            //Set module volume (range 0-1024) using the function mmSetVolume()
            mmSetModuleVolume(768);
            break;
        case ON_THE_MOON:
            mmStart(MOD_SMH___ON_THE_MOON, MM_PLAY_LOOP);
            //Set module volume (range 0-1024) using the function mmSetVolume()
            mmSetModuleVolume(768);
            break;
        default:
            break;
    }
}

// Stops the currently playing module.
void stop_music()
{
    mmStop();
}


// Pauses the currently playing module.
void pause_music()
{
    mmPause();
}

// Resumes playback of a paused module.
void resume_music()
{
    mmResume();
}

// Skips to the next track/module
void skip_to_next_track() {
    // Increment the current track and wrap around if necessary
    current_track = (current_track + 1) % NUM_MUSIC_TRACKS;

    // Stop current music, if playing
    mmStop();

    // Start playing the next track
    play_music(current_track);
}

// Skips to the previous track/module
void skip_to_previous_track() {
    // Decrement the current track and wrap around if necessary
    current_track = (current_track - 1 + NUM_MUSIC_TRACKS) % NUM_MUSIC_TRACKS;

    // Stop current music, if playing
    mmStop();

    // Start playing the previous track
    play_music(current_track);
}

