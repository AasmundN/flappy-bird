#ifndef FLAPPY_BIRD_GAME_H
#define FLAPPY_BIRD_GAME_H

#include "bird.h"
#include "pipe.h"

#include <memory>
#include <vector>

// global namespace forward declarations
struct SDL_Window;
struct SDL_Renderer;

namespace flappy_bird {
class Game final {
 public:
   Game(int width, int height);
   ~Game();

   int run();

 private:
   enum class State {
      RUNNING,
      STOPPED
   };

   SDL_Window *window;
   SDL_Renderer *renderer;

   SDL_Texture *pipeTexture;
   SDL_Texture *birdTexture;

   State state;

   std::shared_ptr<Bird> bird;
   std::vector<std::shared_ptr<Pipe>> pipes;

   unsigned long frameStart;
   unsigned long frameTime;
   static const int FPS = 40;

   void updateFrame();
   void drawFrame();
};
} // namespace flappy_bird

#endif
