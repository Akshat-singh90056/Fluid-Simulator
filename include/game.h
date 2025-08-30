#ifndef GAME_H
#define GAME_H

#include "glad/glad.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include "shader.h"

class Game
{
public:
  bool init(const char *title, int WINDOW_W, int WINDOW_H);
  void handleEvent();
  void update();
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
};

#endif // !GAME_H
