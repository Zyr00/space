#ifndef __DRAW_H__
#define __DRAW_H__

#include "common.h"

void prepareScene(void);
void presentScene(void);
SDL_Texture *loadTexture(const char *);
void blit(SDL_Texture *, const int, const int);
void blitRect(SDL_Texture *, SDL_Rect *, const int, const int);
void draw(void);

#endif
