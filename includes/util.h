#ifndef __UTIL_H__
#define __UTIL_H__

// #include <sys/param.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/**
 * Check for collision
 *
 * @param x1 x position of the sprite
 * @param y1 y position of the sprite
 * @param w1 width of the sprite
 * @param h1 height of the sprite
 * @param x2 x position of the sprite
 * @param y2 y position of the sprite
 * @param w2 width of the sprite
 * @param h2 height of the sprite
 *
 * @return 1 if is colliding 0 if not.
 */
int collision(int, int, int, int, int, int, int, int);

/**
 * Calculate the slop between positions
 *
 * @param x1 x position of sprite
 * @param y1 y position of sprite
 * @param x2 x position of sprite
 * @param y2 y position of sprite
 * @param dx a pointer to contain the movement of the x position
 * @param dy a pointer to contain the movement of the y position
 */
void calcSlope(int, int, int, int, float *, float *);

/**
 * Generate a random number between a max and min
 *
 * @param min the minimum number
 * @param max the maximum number
 *
 * @return the generated number between min and max
 */
float randomNumber(const float, const float);

#endif
