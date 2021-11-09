#ifndef __COMMON_H__
#define __COMMON_H__

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_timer.h>

#include "defs.h"
#include "structs.h"
#include "util.h"

extern App app;
extern Stage stage;
extern Entity *player;
extern Star stars[MAX_STARS];
extern SDL_Texture *explosionTexture;

/*
 * Function to print a errno to the console
 * @warning does not work on widows
 *
 * @param fmt the formatted message to show to the user (like printf)
 */
void err(const char *fmt, ...);

#endif
