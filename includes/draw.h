#ifndef __DRAW_H__
#define __DRAW_H__

#include "common.h"

/*
 * Prepare the scene to show to the user (background)
 */
void prepareScene(void);

/*+
 * Render the scene
 */
void presentScene(void);

/**
 * Load texture to the memory
 *
 * @param filename the path of the texture
 */
SDL_Texture *loadTexture(const char *);

/**
 * Blit a texture in a x y position
 *
 * @param texture the texture to blit
 * @param x the x position of the texture
 * @param y the y position of the texture
 */
void blit(SDL_Texture *, const int, const int);

/**
 * Blit a rect and texture
 *
 * @param texture the texture to blit
 * @param src the SDL_Rect to blit
 * @param x the x position of the src
 * @param y the y position of the src
 */
void blitRect(SDL_Texture *, SDL_Rect *, const int, const int);

/**
 * Draw all of the elements like explosions, bullets, fighters, etc.
 */
void draw(void);

/**
 * Draw on screen the background stars.
 */
void drawStarfield(void);


#endif
