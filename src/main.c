#include <stdio.h>
#include "../includes/main.h"
#include "../includes/common.h"
#include "../includes/init.h"
#include "../includes/logic.h"
#include "../includes/draw.h"
#include "../includes/input.h"
#include <stdlib.h>
#include <time.h>

static void capFramerate(long *then, float  *remainder);

App app;
Stage stage;
Entity *player;
int enemySpawnTimer, stageResetTimer;

int main(void) {
  long then;
  float remainder;

  srand((unsigned) time(NULL));
  memset(&app, 0, sizeof(App));

  initSDL();
  initStage();

  then = SDL_GetTicks();
  remainder = 0;

  while (app.running) {
    prepareScene();
    doInput();

    app.delegate.logic();
    app.delegate.draw();

    presentScene();
    // SDL_Delay(16);
    capFramerate(&then, &remainder);
  }

  finishSDL();

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
