#include "game.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <iostream>
#include<vector>
#include <time.h>

const int numPartcles = 10000;
float particlePos[numPartcles * 2]; // example pixel coords

GLuint shaderProgram;
GLuint VBO, VAO;

std::vector<float> positions;
std::vector<float> velocities;

float r = 10.0f;

GLuint compileShader(GLenum type, const char *source)
{
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  return shader;
}

bool Game::init(const char *title, int WINDOW_W, int WINDOW_H)
{
  this->WINDOW_W = WINDOW_W;
  this->WINDOW_H = WINDOW_H;

  if (SDL_Init(SDL_INIT_VIDEO) == 0)
  {
    std::cerr << "Failes to initialize sdl" << std::endl;
    return false;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  window = SDL_CreateWindow(title, WINDOW_W, WINDOW_H, SDL_WINDOW_OPENGL);

  context = SDL_GL_CreateContext(window);


  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
  {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return false;
  }

  SDL_GL_SetSwapInterval(0);

  glEnable(GL_PROGRAM_POINT_SIZE); // Enable gl_PointSize in shader
  glEnable(GL_POINT_SPRITE);       // Enable point sprites

  int i = 0;
  srand(time(NULL));

  for (int j = 0; j < numPartcles; j++)
  {
    int x = rand() % WINDOW_W;
    int y = rand() % WINDOW_H;

    particlePos[i] = x;
    particlePos[i + 1] = y;
    i += 2;
  }

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(particlePos), particlePos, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  shader = new Shader("shaders/vertex.vert", "shaders/fragment.frag");

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  frameTimePrev = SDL_GetTicks();
  frameCount = 0;
  fps = 0.0f;

  isRunning = true;
  return true;
}

void Game::update()
{

  // this is a comment and i am chekcing id this saves on formaing or not
}

void Game::handleEvent()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_EVENT_QUIT)
    {
      isRunning = false;
    }
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
      if (event.key.key == SDLK_UP)
      {
        r += 1.0f;
      }
    }
  }

}

void Game::render()
{
  frameCount++;
  Uint64 currentTime = SDL_GetTicks();
  Uint64 deltaTime = currentTime - frameTimePrev;

  // Update FPS every second
  if (deltaTime >= 1000)
  {
    fps = frameCount * 1000.0f / deltaTime;
    std::cout << "FPS: " << fps << std::endl; // Display in terminal
    frameCount = 0;
    frameTimePrev = currentTime;
  }

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  shader->use();
  shader->setFloat("pointSize", r);
  shader->setVec2("screenSize", glm::vec2(WINDOW_W, WINDOW_H));

  glBindVertexArray(VAO);

  int numVertices = sizeof(particlePos) / (sizeof(float));
  glDrawArrays(GL_POINTS, 0, (int)(numVertices / 2));

  SDL_GL_SwapWindow(window);
}

void Game::clear()
{
  shader->destroy();

  delete shader;
  SDL_GL_DestroyContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
