#include "../includes/init.h"
#include "../includes/common.h"
#include "../includes/draw.h"
#include "../includes/logic.h"

static void initPlayer(void);

void initSDL(void) {
  int rendererFlags, windowsFlags;
  rendererFlags = SDL_RENDERER_ACCELERATED;
  windowsFlags = 0;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    err("Error initializing SDL: %s\n", SDL_GetError());

  app.window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowsFlags);

  if (!app.window)
    err("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

  if (!app.renderer)
    err("Failed tocreate renderer", SDL_GetError());

  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
    err("Failed to load suport of images: %s\n", IMG_GetError());

  app.running = 1;
}

void initStage(void) {
 app.delegate.logic = logic;
 app.delegate.draw = draw;

 memset(&stage, 0, sizeof(Stage));
 stage.fighterTail = &stage.fighterHead;
 stage.bulletTail = &stage.bulletHead;

 initPlayer();

 bulletTexture = loadTexture("./assets/bullet.png");
}

static void initPlayer(void) {
  player = (Entity *) malloc(sizeof(Entity));
  memset(player, 0, sizeof(Entity));
  stage.fighterTail->next = player;
  stage.fighterTail = player;

  player->x = 100;
  player->y = 100;
  player->texture = loadTexture("./assets/player.png");
  SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void finishSDL(void) {
  IMG_Quit();
  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyWindow(app.window);
  SDL_Quit();
}
