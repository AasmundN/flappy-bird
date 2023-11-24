#ifndef FLAPPY_BIRD_GAME_H
#define FLAPPY_BIRD_GAME_H

// global namespace forward declarations
struct SDL_Window;
struct SDL_Renderer;

namespace flappy_bird {
class Game final {
 public:
   enum class State {
      RUNNING,
      STOPPED
   };

   Game(int width, int height);
   ~Game();
   int run();

 private:
   SDL_Window *window;
   SDL_Renderer *renderer;
   State state;
};
} // namespace flappy_bird

#endif
