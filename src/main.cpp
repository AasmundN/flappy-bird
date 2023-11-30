#include "game.h"

const int width = 500;
const int height = 800;

using namespace flappy_bird;

int main(int argc, char const *argv[]) {
   Game game(width, height);
   return game.run();
}
