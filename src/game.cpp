#include "game.h"

#include <SDL.h>
#include <iostream>

using namespace flappy_bird;

Game::Game(int width, int height) : window(nullptr), renderer(nullptr), state(State::RUNNING) {
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

   while (state == State::RUNNING) {
      while (SDL_PollEvent(&event) != 0) {
         switch (event.type) {
         case SDL_QUIT:
            state = State::STOPPED;
            break;

         default:
            break;
         }
      }
   }

   return 0;
}
