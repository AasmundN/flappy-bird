#include "game.h"

#include <SDL.h>
#include <SDL_image.h>

#include <chrono>
#include <iostream>

#define PIPE_WIDTH 80
#define PIPE_INTERVAL 160
#define PIPE_SPEED 2

#define PIPE_IMG "./graphics/pipe.png"
#define BIRD_IMG "./graphics/mogus.png"

using namespace flappy_bird;

Game::Game(int width, int height)
    : window(nullptr),
      renderer(nullptr),
      pipeTexture(nullptr),
      birdTexture(nullptr),
      state(State::RUNNING),
      bird(nullptr),
      frameStart(0l),
      frameTime(0l) {

   // init video and timer
   if (SDL_Init(SDL_INIT_VIDEO) == -1) {
      std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
   }

   SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
   SDL_SetWindowResizable(window, SDL_TRUE);
}

Game::~Game() {
   std::cout << "Closing window..." << std::endl;

   if (renderer != nullptr) {
      SDL_DestroyRenderer(renderer);
   }
   if (window != nullptr) {
      SDL_DestroyWindow(window);
   }
   if (pipeTexture != nullptr) {
      SDL_DestroyTexture(pipeTexture);
   }
   if (birdTexture != nullptr) {
      SDL_DestroyTexture(birdTexture);
   }

   SDL_Quit();
}

int Game::run() {
   SDL_Event event;

   // load images and create textures for pipes and bird
   pipeTexture = IMG_LoadTexture(renderer, PIPE_IMG);
   birdTexture = IMG_LoadTexture(renderer, BIRD_IMG);

   // create bird
   if (!bird) {
      bird = std::make_unique<Bird>(*renderer, *birdTexture);
   }

   // create first pipe
   if (pipes.empty()) {
      pipes.insert(pipes.end(), std::make_unique<Pipe>(*renderer, *pipeTexture, PIPE_WIDTH, 800, PIPE_INTERVAL, PIPE_SPEED));
   }

   // game loop
   while (state == State::RUNNING) {
      frameStart = SDL_GetTicks();

      // handle events
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

      // update frame
      updateFrame();

      // clear renderer
      SDL_SetRenderDrawColor(renderer, 0x8a, 0xef, 0xff, 0xff);
      SDL_RenderClear(renderer);

      // draw new frame to renderer
      drawFrame();

      // present renderer
      SDL_RenderPresent(renderer);

      // wait for next frame
      frameTime = SDL_GetTicks() - frameStart;
      if (1000 / FPS > frameTime) {
         SDL_Delay(1000 / FPS - frameTime);
      }
   }

   return 0;
}

void Game::updateFrame() {
   // update pipes
   for (auto pipe : pipes) {
      pipe->update();
   }

   // remove pipe when it leaves the window
   if (pipes[0]->getX() <= -PIPE_WIDTH) {
      pipes.erase(pipes.begin());
   }

   // add new pipe
   if (pipes[pipes.size() - 1]->getX() <= 500 - PIPE_WIDTH - PIPE_INTERVAL) {
      pipes.insert(pipes.end(), std::make_unique<Pipe>(*renderer, *pipeTexture, PIPE_WIDTH, 800, PIPE_INTERVAL, PIPE_SPEED));
   }

   // update bird
   bird->update();
}

void Game::drawFrame() {
   // render pipres
   for (auto pipe : pipes) {
      pipe->render();
   }

   // render bird
   bird->render();
}