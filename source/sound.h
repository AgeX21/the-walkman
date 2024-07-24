#include <nds.h>
#include <stdio.h>
#include <maxmod9.h>

#include "soundbank.h"
#include "soundbank_bin.h"

#ifndef SOUND
#define SOUND

/*
	Sound is controlled through the MaxMod library and libnds. ARM9 processes the main program instructions and converts 
	the MaxMod functions to IPC (interprocessor communication) commands that are then buffered and handled by the ARM7.
*/

typedef enum 
{
	BUTTON
} sfx;

typedef enum {
    ENJOY,
	MR_DROICHEN,	
	BADAPPLE,	
	BLUE_PHOEBE_LOVE,
	CODA_SPINER,	
	SLEEP_WELL,	
	MUSIC_FOR_CHIPS,	
	MOD_PAPER_DRIP,	
	ON_THE_MOON,	
    NUM_MUSIC_TRACKS
} music;

extern music current_track;

// Initialize the sound system and starts the main theme
void sound_init();

// Plays the sound effect specified witht the sfx variable
void play_SFX(sfx sound);

// Plays the module music
void play_music(music music);

// Stops the currently playing module.
void stop_music();

// Pauses the currently playing module.
void pause_music();

// Resumes playback of a paused module.
void resume_music();

// Skips to the next track/module
void skip_to_next_track();

// Skips to the previous track/module
void skip_to_previous_track();

#endif
