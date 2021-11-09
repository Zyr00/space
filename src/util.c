/**
 * @file util.c
 * @author João Cunha
 * @brief Utils for the game
 *
 * All of the utils needed for the game like the generating
 * random numbers
 */
#include "../includes/util.h"
#include "../includes/common.h"

int collision(int x1, int y1, int w1, int h1,
    int x2, int y2, int w2, int h2) {
  return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy) {
  int steps = MAX(abs(x1 - x2), abs(y1 - y2));

  if (steps == 0)  {
    *dx = *dy = 0;
    return;
  }

  *dx = (x1 - x2);
  *dx /= steps;

  *dy = (y1 - y2);
  *dy /= steps;

}

float randomNumber(const float min, const float max) {
  return min + ((double) rand() / ((double) RAND_MAX + 1)) * (max - min + 1);
}

