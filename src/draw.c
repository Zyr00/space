#include "../includes/draw.h"
#include "../includes/common.h"

static void drawPlayer(void);
static void drawBullets(void);

void prepareScene() {
  SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(app.renderer);
}

void presentScene() {
  SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(const char *filename) {
  SDL_Texture *texture;
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

  texture = IMG_LoadTexture(app.renderer, filename);

  return texture;
}

void blit(SDL_Texture *texture, const int x, const int y)  {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
  SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void draw(void) {
  drawPlayer();
  drawBullets();
}

static void drawPlayer(void)  {
  blit(player->texture, player->x, player->y);
}

static void drawBullets(void)  {
  Entity *b;

  for (b = stage.bulletHead.next; b != NULL;  b = b->next)
    blit(b->texture, b->x, b->y);
}
