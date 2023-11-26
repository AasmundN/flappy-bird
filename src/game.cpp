#include "game.h"

#include <SDL.h>
#include <SDL_image.h>

#include <chrono>
#include <iostream>

using namespace flappy_bird;

// get milliseconds
inline unsigned long getCurrentMillis() {
   using namespace std::chrono;
   return (unsigned long)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Game::Game(int width, int height)
    : window(nullptr),
      renderer(nullptr),
      state(State::RUNNING),
      bird(nullptr),
      currentMillis(0),
      previousMillis(0) {
   if (SDL_Init(SDL_INIT_VIDEO) == -1) {
      std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
   }

   SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}

Game::~Game() {
   std::cout << "Closing window..." << std::endl;

   if (renderer != nullptr) {
      SDL_DestroyRenderer(renderer);
   }
   if (window != nullptr) {
      SDL_DestroyWindow(window);
   }

   SDL_Quit();
}

int Game::run() {
   SDL_Event event;

   // temporary background image
   const char *img = "graphics/mogus.jpeg";
   SDL_Rect texture_rect({0, 0, 500, 800});

   if (!bird)
      bird = std::make_unique<Bird>();

   while (state == State::RUNNING) {
      while (SDL_PollEvent(&event) != 0) {
         switch (event.type) {
         case SDL_QUIT:
            state = State::STOPPED;
            break;

         case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_SPACE:
               bird->jump();
               break;
            }
            break;
         }
      }

      currentMillis = getCurrentMillis();
      if ((currentMillis - previousMillis) > 1000 / FPS) {
         bird->update();
         previousMillis = currentMillis;
      }

      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
      SDL_RenderClear(renderer);

      SDL_Texture *img_texture = IMG_LoadTexture(renderer, img);
      SDL_RenderCopy(renderer, img_texture, NULL, &texture_rect);

      bird->render(*renderer);

      SDL_RenderPresent(renderer);
   }

   return 0;
}
