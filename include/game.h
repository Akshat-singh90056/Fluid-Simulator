#ifndef GAME_H
#define GAME_H

#include "glad/glad.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include "shader.h"
#include "Particle.h"

class Game
{
public:

  Game();

  bool init(const char *title, int WINDOW_W, int WINDOW_H);
  void handleEvent();
  void update(float dt);
  void render();
  bool running() { return isRunning; }
  void clear();

private:
  int WINDOW_W, WINDOW_H;
  SDL_Window *window;
  SDL_GLContext context;
  bool isRunning;
  Shader *shader;

  Uint64 frameTimePrev;
  int frameCount;
  float fps;

  Particle * p;
};

#endif // !GAME_H
