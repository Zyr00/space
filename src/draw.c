/**
 * @file draw.c
 * @author João Cunha
 * @brief Render/Draw to screen
 *
 * Prepare the scene and draw on the scene
 */
#include "../includes/draw.h"
#include "../includes/common.h"

/**
 * Draw bullets fired in the game.
 */
static void drawBullets(void);

/**
 * Draw the player and enemies.
 */
static void drawFighters(void);

/**
 * Draw on screen the background stars.
 */
static void drawStarfield(void);

/**
 * Draw debris after explosion.
 */
static void drawDebris(void);

/**
 * Draw a explosion
 */
static void drawExplosions(void);

/**
 * Draw trails of the player and enemies
 */
static void drawTrails(void);

void prepareScene() {
  SDL_SetRenderDrawColor(app.renderer, COLOR_R, COLOR_G, COLOR_B, SDL_ALPHA_OPAQUE);
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

void blitRect(SDL_Texture *texture, SDL_Rect *src, const int x, const int y) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;
  dest.w = src->w;
  dest.h = src->h;

  SDL_RenderCopy(app.renderer, texture, src, &dest);
}

void draw(void) {
  drawStarfield();
  drawFighters();
  drawBullets();
  drawDebris();
  drawExplosions();
  drawTrails();
}

static void drawBullets(void)  {
  Entity *b;

  for (b = stage.bulletHead.next; b != NULL;  b = b->next)
    blit(b->texture, b->x, b->y);
}

static void drawFighters(void) {
  Entity *b;

  for (b = stage.fighterHead.next; b != NULL;  b = b->next)
    blit(b->texture, b->x, b->y);
}

static void drawStarfield(void) {
  int i, c;

  for (i = 0; i < MAX_STARS; i++) {
    c = 32 * stars[i].speed;
    SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);
    SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
  }
}

static void drawDebris(void) {
  Debris *d;

  for (d = stage.debrisHead.next; d != NULL; d = d->next) {
    blitRect(d->texture, &d->rect, d->x, d->y);
  }
}

static void drawExplosions(void) {
  Explosion *e;

  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
  SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);

  for (e = stage.explosionHead.next; e != NULL; e = e->next) {
    SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);
    SDL_SetTextureAlphaMod(explosionTexture, e->a);

    blit(explosionTexture, e->x, e->y);
  }

  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

static void drawTrails(void) {
  Trail *t;

  for (t = stage.trailHead.next; t != NULL; t = t->next) {
    blit(t->texture, t->x, t->y);
  }
}
