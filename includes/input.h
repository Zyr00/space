#ifndef __INPUT_H__
#define __INPUT_H__

#include "common.h"

/**
 * Read user input
 */
void doInput(void);

/**
 * Read the key pressed
 *
 * @param event the SDL_KeyboardEvent to read.
 */
void handleKeyPress(SDL_KeyboardEvent *);

#endif
