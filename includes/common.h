#ifndef __COMMON_H__
#define __COMMON_H__

#include <errno.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "defs.h"
#include "structs.h"

extern App app;
extern Stage stage;
extern Entity *player;
extern SDL_Texture *bulletTexture, *enemyTexture;
extern int enemySpawnTimer;

void err(const char *, ...);

#endif
