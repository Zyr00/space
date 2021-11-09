#ifndef __SOUND_H__
#define __SOUND_H__

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
