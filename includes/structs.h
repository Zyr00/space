#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "common.h"

typedef struct {
  void (*logic)(void);
  void (*draw)(void);
} Delegate;

typedef struct {
  int running;
  SDL_Renderer *renderer;
  SDL_Window *window;
  Delegate delegate;
  int keyboard[MAX_KEYBOARD_KEYS];
} App;

struct Entity {
  float x;
  float y;
  int w;
  int h;
  float dx;
  float dy;
  int health;
  int reload;
  int side;
  int type;
  SDL_Texture *texture;
  struct Entity *next;
};

typedef struct Entity Entity;

struct Explosion {
  float x, y, dx, dy;
  int r, g, b, a;
  struct Explosion *next;
};

typedef struct Explosion Explosion;

struct Debris {
  float x, y, dx, dy;
  SDL_Rect rect;
  SDL_Texture *texture;
  int life;
  struct Debris *next;
};

typedef struct Debris Debris;

struct Trail {
  float x, y;
  SDL_Texture *texture;
  Entity *e;
  int a;
  struct Trail *next;
};

typedef struct Trail Trail;

typedef struct {
  Entity fighterHead, *fighterTail;
  Entity bulletHead, *bulletTail;
  Explosion explosionHead, *explosionTail;
  Debris debrisHead, *debrisTail;
  Trail trailHead, *trailTail;
  Entity podsHead, *podsTail;
  int score;
} Stage;

typedef struct {
  int x, y, speed;
} Star;

#endif
