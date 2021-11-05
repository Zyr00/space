#include <stdio.h>
#include "../includes/main.h"
#include "../includes/common.h"
#include "../includes/init.h"
#include "../includes/draw.h"
#include "../includes/input.h"

App app;
Stage stage;
Entity *player;
SDL_Texture *bulletTexture;

int main(void) {
  long then;
  float remainder;

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
    SDL_Delay(16);
  }

  finishSDL();

  return 0;
}
