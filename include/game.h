#ifndef FLAPPY_BIRD_GAME_H
#define FLAPPY_BIRD_GAME_H

#include "bird.h"
#include "pipe.h"

#include <memory>
#include <vector>

struct _TTF_Font;

namespace flappy_bird {
class Game final {
 public:
   Game(int width, int height);
   ~Game();

   int run();

 private:
   enum class State {
      RUNNING,
      STOPPED,
      LOST
   };

   int width, height;

   SDL_Window *window;
   SDL_Renderer *renderer;

   std::vector<SDL_Texture *> pipeTextures;
   SDL_Texture *birdTexture;
   _TTF_Font *font;

   State state;

   SDL_Rect scoreDst;
   int score;

   std::shared_ptr<Bird> bird;
   std::vector<std::shared_ptr<Pipe>> pipes;

   unsigned long frameStart;
   unsigned long frameTime;
   static const int FPS = 40;

   void updateFrame();
   void drawFrame();
   void collide();
   void drawScore();
};
} // namespace flappy_bird

#endif
