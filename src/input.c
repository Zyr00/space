/**
 * @file input.c
 * @author João Cunha
 * @brief Control input
 *
 * User input controller
 */
#include "../includes/input.h"
#include "../includes/common.h"

void doInput(void) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
          app.running = 0;
          break;
      case SDL_KEYDOWN:
          handleKeyPress(&event.key);
          break;
      case SDL_KEYUP:
          handleKeyPress(&event.key);
          break;
      default:
          break;
    }
  }
}

void handleKeyPress(SDL_KeyboardEvent *event) {
  if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = !app.keyboard[event->keysym.scancode];
  }
}
