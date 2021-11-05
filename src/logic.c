#include "../includes/logic.h"
#include "../includes/common.h"

static void doPlayer(void);
static void fireBullet(void);
static void doBullets(void);
static void spawnEnemies(void);
static void doFighters(void);
static int bulletHitFighter(Entity *);

void logic(void) {
  doPlayer();
  doFighters();
  doBullets();
  spawnEnemies();
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

  b->side = SIDE_PLAYER;
  b->x = player->x + 18;
  b->y = player->y;
  b->dx = BULLET_SPEED;
  b->health = 1;
  b->texture = bulletTexture;
  SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);

  b->y += (player->h / 2) - (b->h / 2);
  player->reload = 8;
}

static void doBullets(void) {
  Entity *b, *prev;

  prev = &stage.bulletHead;

  for (b = stage.bulletHead.next; b != NULL; b = b->next) {
    b->x += b->dx;
    b->y += b->dy;

    if (bulletHitFighter(b) || b->x > SCREEN_WIDTH) {
      if (b == stage.bulletTail) stage.bulletTail = prev;
      prev->next = b->next;
      free(b);
      b = prev;
    }
    prev = b;
  }
}

static void spawnEnemies(void) {
  Entity *e;

  if (--enemySpawnTimer <= 0) {
    e = (Entity *) malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.fighterTail->next = e;
    stage.fighterTail = e;

    e->side = SIDE_ALIEN;
    e->health = 1;
    e->x = SCREEN_WIDTH;
    e->y = rand() % SCREEN_HEIGHT;
    e->texture = enemyTexture;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

    e->dx = -(2 + (rand() % 4));
    enemySpawnTimer = 30 + (rand() % 60);
  }
}

static void doFighters(void) {
  Entity *e, *prev;

  prev = &stage.fighterHead;

  for (e = stage.fighterHead.next; e != NULL; e = e->next) {
    e->x += e->dx;
    e->y += e->dy;

    if (e != player && (e->x < -e->w || e->health == 0)) {
      if (e == stage.fighterTail) {
        stage.fighterTail = prev;
      }

      prev->next = e->next;
      free(e);
      e = prev;
    }
    prev = e;
  }
}

static int bulletHitFighter(Entity *b) {
  Entity *e;

  for (e = stage.fighterHead.next; e != NULL; e = e->next) {
    if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h)) {
      b->health = 0;
      e->health = 0;
      return 1;
    }
  }
  return 0;
}
