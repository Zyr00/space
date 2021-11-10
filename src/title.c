/**
 * @file title.c
 * @author João Cunha
 * @brief Initialize the title for the game
 *
 * Initialize the title for the game, that will start the game.
 */
#include "../includes/title.h"
#include "../includes/common.h"
#include "../includes/logic.h"
#include "../includes/text.h"
#include "../includes/draw.h"

/**
 * Draw the title
 */
static void draw_title(void);

/**
 * Logic of the title
 */
static void logic(void);

void initTitle(void) {
  app.delegate.draw = draw_title;
  app.delegate.logic = logic;

  memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

  initStarfield();
}

static void logic(void) {
  doStarfield();

  if (app.keyboard[SDL_SCANCODE_LCTRL])
    initStage();
}

static void draw_title(void) {
  drawStarfield();
  char *str = "PRESS FIRE (LCTRL) TO START!";
  drawText(strlen(str), SCREEN_HEIGHT / 2, 250, 250, 250, str);
}
