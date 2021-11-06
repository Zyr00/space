#ifndef __COMMON_H__
#define __COMMON_H__

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "defs.h"
#include "structs.h"
#include "util.h"

extern App app;
extern Stage stage;
extern Entity *player;
extern int enemySpawnTimer, stageResetTimer;

void err(const char *, ...);

#endif
