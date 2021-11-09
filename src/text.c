/**
 * @file text.c
 * @author João Cunha
 * @brief Text controller
 *
 * Load and draw text
 */
#include "../includes/text.h"
#include "../includes/common.h"
#include "../includes/draw.h"

TTF_Font *font;
static char drawTextBuffer[MAX_LINE_LENGTH];

void drawText(int x, int y, int r, int g, int b, char *fmt, ...)  {
  SDL_Color color;
  SDL_Surface *textSurface;
  SDL_Texture *textTexture;
  SDL_Rect rect;
  va_list args;

  memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));

  va_start(args, fmt);
  vsprintf(drawTextBuffer, fmt, args);
  va_end(args);

  rect.x = 0;
  rect.y = 0;

  color.a = 255;
  color.r = r;
  color.g = g;
  color.b = b;

  textSurface = TTF_RenderText_Blended(font, drawTextBuffer, color);
  textTexture = SDL_CreateTextureFromSurface(app.renderer, textSurface);
  SDL_QueryTexture(textTexture, NULL, NULL, &rect.w, &rect.h);

  blitRect(textTexture, &rect, x, y);
  SDL_FreeSurface(textSurface);
}
