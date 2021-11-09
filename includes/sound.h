#ifndef __SOUND_H__
#define __SOUND_H__

#include "common.h"

extern Mix_Chunk *sounds[SND_MAX];
extern Mix_Music *music;

/**
 * Initialize sounds with the SDL_Mixer lib.
 */
void initSounds(void);

/**
 * Load music file into memory.
 *
 * @param filename the path of the file to load.
 */
void loadMusic(char *);

/**
 * Start the music
 *
 * @param loop 1 to loop forever, 0 to play until the end.
 */
void playMusic(int);

/**
 * Stop the music.
 */
void stopMusic(void);

/**
 * Play a specific sound.
 *
 * @param id the sound id (see the enums in defs.h).
 * @param channel the channel where the sound is going to be played.
 */
void playSound(int, int);

#endif
