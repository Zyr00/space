#include "../includes/logic.h"
#include "../includes/common.h"

static void doPlayer(void);
static void fireBullet(void);
static void doBullets(void);

void logic(void) {
  doPlayer();
  doBullets();
}

static void doPlayer(void) {
  player->dx = player->dy = 0;

  if (player->reload > 0)  player->reload--;

  if (app.keyboard[SDL_SCANCODE_UP])
    player->dy = -PLAYER_SPEED;
  if (app.keyboard[SDL_SCANCODE_DOWN])
    player->dy = PLAYER_SPEED;

  if (app.keyboard[SDL_SCANCODE_LEFT])
    player->dx = -PLAYER_SPEED;
  if (app.keyboard[SDL_SCANCODE_RIGHT])
    player->dx = PLAYER_SPEED;

  if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0) {
    fireBullet();
  }

  player->x += player->dx;
  player->y += player->dy;
}

static void fireBullet(void) {
  Entity *b;

  b = (Entity *) malloc(sizeof(Entity));
  memset(b, 0, sizeof(Entity));

  stage.bulletTail->next = b;
  stage.bulletTail = b;

  b->x = player->x;
  b->y = player->y;
  b->dx = BULLET_SPEED;
  b->health = 1;
  b->texture = bulletTexture;
  SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);

  b->y += (player->h / 2) - (b->h / 2);
  player->reload = 0;
}

static void doBullets(void) {
  Entity *b, *prev;

  prev = &stage.bulletHead;

  for (b = stage.bulletHead.next; b != NULL; b = b->next) {
    b->x += b->dx;
    b->y += b->dy;

    if (b->x > SCREEN_WIDTH) {
      if (b == stage.bulletTail) stage.bulletTail = prev;
      prev->next = b->next;
      free(b);
      b = prev;
    }
    prev = b;
  }
}
