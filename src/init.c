/**
 * @file init.c
 * @author João Cunha
 * @brief Initializer for SDL
 *
 * Initializes SDL, SDL_Image and SDL_Mixer
 */
#include "../includes/init.h"
#include "../includes/common.h"
#include "../includes/sound.h"

void initSDL(void) {
  int rendererFlags, windowsFlags;
  rendererFlags = SDL_RENDERER_ACCELERATED;
  windowsFlags = 0;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    err("Error initializing SDL: %s\n", SDL_GetError());

  app.window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowsFlags);

  if (!app.window)
    err("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

  if (!app.renderer)
    err("Failed to create renderer", SDL_GetError());

  if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0)
    err("Failed to load support of images: %s\n", IMG_GetError());

  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) == -1)
    err("Failed to inicialize SDL Mixer", SDL_GetError());

  Mix_AllocateChannels(MAX_SND_CHANNELS);

  app.running = 1;
}

void finishSDL(void) {
  int i;

  IMG_Quit();
  Mix_Quit();

  for (i = 0; i < SND_MAX; i++)
    Mix_FreeChunk(sounds[i]);

  if (music != NULL) {
    Mix_HaltMusic();
    Mix_FreeMusic(music);
  }

  Mix_CloseAudio();

  SDL_DestroyRenderer(app.renderer);
  SDL_DestroyWindow(app.window);
  SDL_Quit();
}
