#include "../includes/sound.h"
#include "../includes/common.h"

static void loadSounds(void);

Mix_Chunk *sounds[SND_MAX];
Mix_Music *music;

void initSounds(void) {
  memset(sounds, 0, sizeof(Mix_Chunk *) * SND_MAX);
  music = NULL;

  loadSounds();

  Mix_Volume(SND_PLAYER_FIRE, MIX_MAX_VOLUME/4);
  Mix_Volume(SND_ALIEN_FIRE, MIX_MAX_VOLUME/4);
  Mix_Volume(SND_PLAYER_DIE, MIX_MAX_VOLUME/4);
  Mix_Volume(SND_ALIEN_DIE, MIX_MAX_VOLUME/4);
  Mix_Volume(SND_GAMEOVER, MIX_MAX_VOLUME);

  loadMusic("sounds/The Novis Base.wav");
  playMusic(1);

  Mix_VolumeMusic(MIX_MAX_VOLUME/2);
}

static void loadSounds(void) {
  sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("sounds/laser.ogg");
  if (!sounds[SND_PLAYER_FIRE])
    err("No sound loaded", Mix_GetError());

  sounds[SND_ALIEN_FIRE] = Mix_LoadWAV("sounds/laser.ogg");
  if (!sounds[SND_ALIEN_FIRE])
    err("No sound loaded", Mix_GetError());

  sounds[SND_PLAYER_DIE] = Mix_LoadWAV("sounds/explosion.ogg");
  if (!sounds[SND_PLAYER_DIE])
    err("No sound loaded", Mix_GetError());

  sounds[SND_ALIEN_DIE] = Mix_LoadWAV("sounds/explosion.ogg");
  if (!sounds[SND_ALIEN_DIE])
    err("No sound loaded", Mix_GetError());

  sounds[SND_GAMEOVER] = Mix_LoadWAV("sounds/gameover.mp3");
  if (!sounds[SND_GAMEOVER])
    err("No sound loaded", Mix_GetError());
}

void loadMusic(char *filename) {
  if (music != NULL) {
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = NULL;
  }

  music = Mix_LoadMUS(filename);

  if (!music) {
    err("Error loading", Mix_GetError());
  }
}

void playMusic(int loop) {
  Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void stopMusic(void) {
  Mix_HaltMusic();
}

void playSound(int id, int channel) {
  Mix_PlayChannel(channel, sounds[id], 0);
}
