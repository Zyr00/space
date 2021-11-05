#include <stdio.h>
#include "../includes/main.h"
#include "../includes/common.h"
#include "../includes/init.h"
#include "../includes/draw.h"
#include "../includes/input.h"
#include <stdlib.h>
#include <time.h>

App app;
Stage stage;
Entity *player;
SDL_Texture *bulletTexture, *enemyTexture1, *enemyTexture2;
int enemySpawnTimer;

int main(void) {

  srand((unsigned) time(NULL));

  memset(&app, 0, sizeof(App));

  initSDL();
  initStage();

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
