#include "../includes/logic.h"
#include "../includes/common.h"
#include "../includes/draw.h"

static void logic(void);
static void initPlayer(void);
static void resetStage(void);
static void doPlayer(void);
static void doBullets(void);
static void doFighters(void);
static void fireBullet(void);
static int bulletHitFighter(Entity *);
static void spawnEnemies(void);
static void clipPlayer(void);
static void fireEnemyBullet(Entity *);
static void doEnemies(void);

static SDL_Texture *playerTexture, *playerBulletTexture, *enemyTexture1, *enemyTexture2, *enemyBulletTexture;

void initStage(void) {
 app.delegate.logic = logic;
 app.delegate.draw = draw;

 memset(&stage, 0, sizeof(Stage));
 stage.fighterTail = &stage.fighterHead;
 stage.bulletTail = &stage.bulletHead;

 playerBulletTexture = loadTexture("./assets/bullet.png");
 enemyTexture1 = loadTexture("./assets/enemy1.png");
 enemyTexture2 = loadTexture("./assets/enemy2.png");
 enemyBulletTexture = loadTexture("./assets/bullet.png");
 playerTexture = loadTexture("./assets/player.png");

 resetStage();
}

static void logic(void) {
  doPlayer();
  doFighters();
  doBullets();
  spawnEnemies();
  doEnemies();
  clipPlayer();

  if (player == NULL && --stageResetTimer <= 0) {
    resetStage();
  }
}

static void resetStage(void) {
  Entity *e;

  while (stage.fighterHead.next) {
    e = stage.fighterHead.next;
    stage.fighterHead.next = e->next;
    free(e);
  }

  while (stage.bulletHead.next) {
    e = stage.bulletHead.next;
    stage.bulletHead.next = e->next;
    free(e);
  }

  memset(&stage, 0, sizeof(Stage));
  stage.fighterTail = &stage.fighterHead;
  stage.bulletTail = &stage.bulletHead;

  initPlayer();
  enemySpawnTimer = 0;
  stageResetTimer = FPS * 2;
}

static void initPlayer(void) {
  player = (Entity *) malloc(sizeof(Entity));
  memset(player, 0, sizeof(Entity));
  stage.fighterTail->next = player;
  stage.fighterTail = player;

  player->side = SIDE_PLAYER;
  player->x = 100;
  player->y = 100;
  player->health = 10;
  player->texture = playerTexture;
  SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void doPlayer(void) {
  if (player != NULL) {
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
  b->texture = playerBulletTexture;
  SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);

  b->y += (player->h / 2) - (b->h / 2);
  player->reload = 8;
}

static void fireEnemyBullet(Entity *e) {
  Entity *b;

  b = (Entity *) malloc(sizeof(Entity));
  memset(b, 0, sizeof(Entity));

  stage.bulletTail->next = b;
  stage.bulletTail = b;

  b->x = e->x + 18;
  b->y = e->y;
  b->health = 1;
  b->side = e->side;
  b->texture = enemyBulletTexture;
  SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);

  b->x += (e->w / 2) - (b->w / 2);
  b->y += (e->h / 2) - (b->h / 2);

  calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &b->dx, &b->dy);

  b->dx *= ALIEN_BULLET_SPEED;
  b->dy *= ALIEN_BULLET_SPEED;
  e->reload = (rand() % FPS * 2);
}

static void doBullets(void) {
  Entity *b, *prev;

  prev = &stage.bulletHead;

  for (b = stage.bulletHead.next; b != NULL; b = b->next) {
    b->x += b->dx;
    b->y += b->dy;

    if (bulletHitFighter(b) ||
        b->x < -b->w || b->y < -b->h ||
        b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT) {

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
    if (randomNumber(0, 1) <= 0.02) e->health += rand() % 5;
    e->x = SCREEN_WIDTH;
    e->y = rand() % SCREEN_HEIGHT;
    e->texture = e->health <= 1 ? enemyTexture1 : enemyTexture2;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

    e->reload = FPS * (1 + (rand() % 3));
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

    if (e != player && e->x < -e->w) e->health = 0;

    if (e->health == 0) {
      if (e == player) player = NULL;
      if (e == stage.fighterTail) stage.fighterTail = prev;

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
      e->health--;
      return 1;
    }
  }
  return 0;
}

static void clipPlayer(void) {
  if (player != NULL) {
    if (player->x < 0) player->x = 0;
    if (player->y < 0) player->y = 0;
    if (player->x > SCREEN_WIDTH / 2) player->x = SCREEN_WIDTH / 2;
    if (player->y > SCREEN_HEIGHT - player->h) player->y = SCREEN_HEIGHT - player->h;
  }
}

static void doEnemies(void) {
  Entity *e;

  for (e = stage.fighterHead.next; e != NULL; e = e->next) {
    if (e != player && player != NULL && --e->reload <= 0) {
      fireEnemyBullet(e);
    }
  }
}
