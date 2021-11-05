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
  SDL_Texture *texture;
  struct Entity *next;
};

typedef struct Entity Entity;

typedef struct {
  Entity fighterHead, *fighterTail;
  Entity bulletHead, *bulletTail;
} Stage;

#endif
