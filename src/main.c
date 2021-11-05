#include <stdio.h>
#include "../includes/main.h"
#include "../includes/common.h"
#include "../includes/init.h"
#include "../includes/draw.h"
#include "../includes/input.h"

App app;
Stage stage;
Entity *player;
SDL_Texture *bulletTexture, *enemyTexture;
int enemySpawnTimer;

int main(void) {
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
