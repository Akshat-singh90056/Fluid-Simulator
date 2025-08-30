#include "game.h"

Game game;

int main(int argc, char *argv[]) {
  game.init("hello", 1280, 720);
  while (game.running()) {
    game.handleEvent();
    game.update();
    game.render();
  }

  game.clear();
  return 0;
}
