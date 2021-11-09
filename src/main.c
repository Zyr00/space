/**
 * @file main.c
 * @author João Cunha
 *
 * The main.c file is where the main loop resides
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../includes/main.h"
#include "../includes/common.h"
#include "../includes/init.h"
#include "../includes/logic.h"
#include "../includes/draw.h"
#include "../includes/input.h"
#include "../includes/sound.h"
#include "../includes/text.h"

/**
 *  Cap the frame rate at 60 FPS
 *
 *  @param then a pointer with the ticks
 *  @param remainder the rest.
 */
static void capFramerate(long *then, float  *remainder);

App app;
Stage stage;
Entity *player;
Star stars[MAX_STARS];
int highscore;

int main(void) {
  long then;
  float remainder;

  srand((unsigned) time(NULL));
  highscore = 0;
  memset(&app, 0, sizeof(App));

  initSDL();
  initSounds();
  initStage();
  initFonts();

  then = SDL_GetTicks();
  remainder = 0;

  atexit(finishSDL);

  while (app.running) {
    prepareScene();
    doInput();

    app.delegate.logic();
    app.delegate.draw();

    presentScene();
    // SDL_Delay(16);
    capFramerate(&then, &remainder);
  }

  return 0;
}

static void capFramerate(long *then, float  *remainder)  {
  long wait, frameTime;
  wait = 16 + *remainder;

  *remainder -= (int) *remainder;
  frameTime = SDL_GetTicks() - *then;
  wait -= frameTime;

  if (wait < 1) wait = 1;

  SDL_Delay(wait);

  *remainder += 0.667;
  *then = SDL_GetTicks();
}
