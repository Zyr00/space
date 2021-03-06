/**
 * @file logic.c
 * @author João Cunha
 * @brief Controls the logic of the game
 *
 * This file is responsible for controlling the game
 * what appends to the enemies and others.
 */
#include "../includes/logic.h"
#include "../includes/common.h"
#include "../includes/draw.h"
#include "../includes/sound.h"
#include "../includes/util.h"

/**
 * Main logic loop calls all other functions
 */
static void logic(void);

/**
 * Initialize the player.
*/
static void initPlayer(void);

/**
 * Restart game.
 */
static void resetStage(void);

/**
 * Player logic.
 */
static void doPlayer(void);

/**
 * Bullet logic
 */
static void doBullets(void);

/**
 * Fighters logic.
 */
static void doFighters(void);

/**
 * Fire bullet from player.
 */
static void fireBullet(void);

/**
 * Bullet collision logic.
 *
 * @param e entity to check if hit.
 *
 * @return 1 if hit 0 if not
 */
static int bulletHitFighter(Entity *);

/**
 * Spawn enemies.
 */
static void spawnEnemies(void);

/**
 * Clip the player inside the border of the screen
 */
static void clipPlayer(void);

/**
 * Enemy fire bullet
 */
static void fireEnemyBullet(Entity *);

/**
 * Enemies logic
 */
static void doEnemies(void);

/**
 * Initialize the stars in the background
 */
void initStarfield(void);

/**
 * Explosion logic.
 */
static void doExplosions(void);

/**
 * Debris logic.
 */
static void doDebris(void);

/**
 * Trail logic.
 */
static void doTrail(void);

/**
 * Logic for the pods
 */
static void doPod(void);

/**
 * Add explosion in a position
 *
 * @param x the x position of the explosion
 * @param y the y position of the explosion
 * @param num the number of explosions.
 */
static void addExplosion(int x, int y, int num);

/**
 * Add debris in a position.
 *
 * @param e the entity that the debris is part of
 */
static void addDebris(Entity *);

/**
 * Add trail in a position.
 *
 * @param e the entity that the trail is part of
 */
static void addTrail(Entity *);

/**
 * Add new pod.
 *
 * @param e the entity that the pod will spawn from
 */
static void addPod(int x, int y);


static SDL_Texture *playerTexture,
  *playerBulletTexture, *enemyBulletTexture,
  *enemyTexture, *enemyTexture1, *enemyTexture2,
  *playerTrail, *enemyTrail, *podTexture;

SDL_Texture *explosionTexture;

static int enemySpawnTimer, stageResetTimer;

void initStage(void) {
 app.delegate.logic = logic;
 app.delegate.draw = draw;

 memset(&stage, 0, sizeof(Stage));
 stage.fighterTail = &stage.fighterHead;
 stage.bulletTail = &stage.bulletHead;
 stage.explosionTail = &stage.explosionHead;
 stage.debrisTail = &stage.debrisHead;

 playerTexture = loadTexture("./assets/player.png");
 playerTrail = loadTexture("./assets/ptrail.png");
 playerBulletTexture = loadTexture("./assets/bullet.png");

 enemyTexture = loadTexture("./assets/enemy.png");
 enemyTexture1 = loadTexture("./assets/enemy1.png");
 enemyTexture2 = loadTexture("./assets/enemy2.png");
 enemyTrail = loadTexture("./assets/etrail.png");
 enemyBulletTexture = loadTexture("./assets/bullet.png");

 explosionTexture = loadTexture("./assets/explosion.png");
 podTexture = loadTexture("./assets/pod.png");

 resetStage();
}

static void logic(void) {
  doStarfield();
  doPlayer();
  doFighters();
  doBullets();
  spawnEnemies();
  doEnemies();
  clipPlayer();

  doExplosions();
  doDebris();
  doTrail();
  doPod();

  if (player == NULL && --stageResetTimer <= 0) {
    resetStage();
  }
}

static void resetStage(void) {
  Entity *e;
  Explosion *ex;
  Debris *d;
  Trail *t;

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

  while (stage.explosionHead.next) {
    ex = stage.explosionHead.next;
    stage.explosionHead.next = ex->next;
    free(ex);
  }

  while (stage.debrisHead.next) {
    d = stage.debrisHead.next;
    stage.debrisHead.next = d->next;
    free(d);
  }

  while (stage.trailHead.next) {
    t = stage.trailHead.next;
    stage.trailHead.next = t->next;
    free(t);
  }

  while (stage.podsHead.next) {
    e = stage.podsHead.next;
    stage.podsHead.next = e->next;
    free(e);
  }

  memset(&stage, 0, sizeof(Stage));
  stage.fighterTail = &stage.fighterHead;
  stage.bulletTail = &stage.bulletHead;
  stage.explosionTail = &stage.explosionHead;
  stage.debrisTail = &stage.debrisHead;
  stage.trailTail = &stage.trailHead;
  stage.podsTail = &stage.podsHead;

  initPlayer();
  initStarfield();

  enemySpawnTimer = 0;
  stageResetTimer = FPS * 2;
  stage.score = 0;

  SDL_Delay(16);
  playMusic(1);
}

static void initPlayer(void) {
  player = (Entity *) malloc(sizeof(Entity));
  memset(player, 0, sizeof(Entity));
  stage.fighterTail->next = player;
  stage.fighterTail = player;

  player->side = SIDE_PLAYER;
  player->x = 100;
  player->y = rand() % SCREEN_HEIGHT;
  player->health = 10;
  player->texture = playerTexture;
  SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
  addTrail(player);
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
      playSound(SND_PLAYER_FIRE, CH_PLAYER);
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

  b->dx = -1;
  b->x += (e->w / 2) - (b->w / 2);

  if (e->type != 1) {
    calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &b->dx, &b->dy);
    b->y += (e->h / 2) - (b->h / 2);
    b->dy *= ALIEN_BULLET_SPEED;
  }

  b->dx *= ALIEN_BULLET_SPEED;

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
    e->reload = FPS * (1 + (rand() % 3));

    e->type = (int) randomNumber(1, 2);
    e->health = 1;

    if (e->type == 1) {
      e->texture = enemyTexture;
    } else {
      e->texture = enemyTexture1;
    }

    if (randomNumber(0, 1) <= 0.01)  {
      e->type = 3;
      e->health += rand() % 5;
      e->texture = enemyTexture2;
    }

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

    e->x = SCREEN_WIDTH;
    e->y = (int) randomNumber(e->h, SCREEN_HEIGHT);

    e->dx = -(2 + (rand() % 4));
    e->dy = -100 + (rand() % 200);
    e->dy /= 100;

    enemySpawnTimer = 30 + (rand() % 60);
    addTrail(e);
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
      if (e->health == 0) {
        addExplosion(e->x, e->y, e->type);
        addDebris(e);
        if (e == player) {
          stopMusic();
          playSound(SND_PLAYER_DIE, CH_PLAYER);
          playSound(SND_GAMEOVER, CH_GAMEOVER);
        } else {
          playSound(SND_ALIEN_DIE, CH_ANY);
          addPod(e->x + e->w / 2, e->y + e->h / 2);
        }
      }
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
    e->y = MIN(MAX(e->y, 0), SCREEN_HEIGHT - e->h);
    if (e != player && player != NULL && --e->reload <= 0) {
      if (e->x > e->h + 100) {
        playSound(SND_ALIEN_FIRE, CH_ALIEN_FIRE);
        fireEnemyBullet(e);
      }
    }
  }
}

void initStarfield(void) {
  int i;

  for (i = 0; i < MAX_STARS; i++) {
    stars[i].x = rand() % SCREEN_WIDTH;
    stars[i].y = rand() % SCREEN_HEIGHT;
    stars[i].speed = 1 + rand() % 8;
  }
}

void doStarfield(void) {
  int i;
  for (i = 0; i < MAX_STARS; i++) {
    stars[i].x -= stars[i].speed;

    if (stars[i].x < 0)
      stars[i].x = SCREEN_WIDTH + stars[i].x;
  }
}

static void doExplosions(void) {
  Explosion *e, *prev;

  prev = &stage.explosionHead;

  for (e = stage.explosionHead.next; e != NULL; e = e->next) {
    e->x += e->dx;
    e->y += e->dy;

    if (--e->a <= 0) {
      if (e == stage.explosionTail)
        stage.explosionTail = prev;

      prev->next = e->next;
      free(e);
      e = prev;
    }
    prev = e;
  }
}

static void doDebris(void) {
  Debris *d, *prev;

  prev = &stage.debrisHead;

  for (d = stage.debrisHead.next; d != NULL; d = d->next) {
    d->x += d->dx;
    d->y += d->dy;

    d->dy += 0.5;

    if (--d->life <= 0) {
      if (d == stage.debrisTail)
        stage.debrisTail = prev;

      prev->next = d->next;
      free(d);
      d = prev;
    }
    prev = d;
  }
}

static void doTrail(void) {
  Trail *t, *prev;

  prev = &stage.trailHead;

  for (t = stage.trailHead.next; t != NULL; t = t->next) {
    t->x = t->e->x + t->e->w;
    if (t->e == player)
      t->x = t->e->x + -t->e->w;
    t->y = t->e->y;

    if (t->e->health == 0) {
      if (t == stage.trailTail)
        stage.trailTail = prev;

      prev->next = t->next;
      free(t);
      t = prev;
    }
    prev = t;
  }
}

static void doPod(void) {
  Entity *e, *prev;

  prev = &stage.podsHead;

  for (e = stage.podsHead.next; e != NULL; e = e->next) {
    if (e->x < 0) {
      e->x = 0;
      e->dx = -e->dx;
    }

    if (e->y < 0) {
      e->y = 0;
      e->dy = -e->dy;
    }

    if (e->x + e->w > SCREEN_WIDTH) {
      e->x = SCREEN_WIDTH - e->w;
      e->dx = -e->dx;
    }

    if (e->y + e->y > SCREEN_HEIGHT) {
      e->y = SCREEN_HEIGHT - e->y;
      e->dy = -e->dy;
    }

    e->x += e->dx;
    e->y += e->dy;

    if (player != NULL && collision(e->x, e->y, e->w, e->h, player->x, player->y, player->w, player->h)) {
      if (randomNumber(0, 1) < 0.5)
        player->health++;
      e->health = 0;
      stage.score++;
      highscore = MAX(stage.score, highscore);
    }

    if (--e->health <= 0) {
      if (e == stage.podsTail)
        stage.podsTail = prev;

      prev->next = e->next;
      free(e);
      e = prev;
    }
    prev = e;
  }
}

static void addExplosion(int x, int y, int num) {
  Explosion *e;
  int i;

  for (i = 0; i < num; i++) {
    e = (Explosion *) malloc(sizeof(Explosion));
    memset(e, 0, sizeof(Explosion));
    stage.explosionTail->next = e;
    stage.explosionTail = e;

    e->x = x + (rand() % 32) - (rand() % 32);
    e->y = y + (rand() % 32) - (rand() % 32);
    e->dx = (rand() % 10) - (rand() % 10);
    e->dy = (rand() % 10) - (rand() % 10);

    e->dx /= 10;
    e->dy /= 10;

    switch (rand() % 4) {
      case 0:
        e->r = 255;
        break;
      case 1:
        e->r = 255;
        e->g = 128;
        break;
      case 2:
        e->r = 255;
        e->g = 255;
        break;
      default:
        e->r = 255;
        e->g = 255;
        e->b = 255;
        break;
    }

    e->a = rand() % FPS * 3;
  }
}

static void addDebris(Entity *e) {
  Debris *d;

  int x, y, w, h;

  w = e->w / 2;
  h = e->h / 2;

  for (y = 0; y <= h; y += h) {
    for (x = 0; x <= w; x += w) {
      d = (Debris *) malloc(sizeof(Debris));
      memset(d, 0, sizeof(Debris));
      stage.debrisTail->next = d;
      stage.debrisTail = d;

      d->x = e->x + e->w / 2;
      d->y = e->y + e->h / 2;
      d->dx = (rand() % 5) - (rand() % 5);
      d->dy = -(5 + (rand() % 12));
      d->life = FPS * 2;
      d->texture = e->texture;

      d->rect.x = x;
      d->rect.y = y;
      d->rect.w = w;
      d->rect.h = h;
    }
  }
}

static void addTrail(Entity *e) {
  Trail *t;

  t = (Trail *) malloc(sizeof(Trail));
  memset(t, 0, sizeof(Trail));
  stage.trailTail->next = t;
  stage.trailTail= t;

  t->x = e->x + e->w;
  if (e == player)
    t->x = e->x + -e->w;
  t->y = e->y;
  t->texture = e == player ? playerTrail : enemyTrail;
  t->e = e;
  t->a = rand() % FPS * 3;
}

static void addPod(int x, int y) {
  Entity *e;

  e = (Entity *) malloc(sizeof(Entity));
  memset(e, 0, sizeof(Entity));
  stage.podsTail->next = e;
  stage.podsTail = e;

  e->x = x;
  e->y = y;
  e->dx = -(rand() % 5);
  e->dy = (rand() % 5) - (rand() % 5);
  e->health = FPS * 10;
  e->texture = podTexture;

  SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);

  e->x -= e->w / 2;
  e->y -= e->h / 2;
}
