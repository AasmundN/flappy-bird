#include "game.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <time.h>

#define PIPE_WIDTH 120
#define PIPE_HEIGHT 1200
#define PIPE_INTERVAL 150
#define PIPE_SPEED 2

#define BIRD_SIZE 60
#define BIRD_X 100
#define BIRD_Y 200

// get random integer between two limits
int randInt(int lower, int upper) {
   return rand() % (upper - lower + 1) + lower;
}

using namespace flappy_bird;

Game::Game(int width, int height)
    : window(nullptr),
      renderer(nullptr),
      birdTexture(nullptr),
      state(State::RUNNING),
      scoreDst({235, 50, 30, 56}),
      bird(nullptr),
      width(width),
      height(height),
      score(0),
      frameStart(0l),
      frameTime(0l) {

   // init video and timer
   if (SDL_Init(SDL_INIT_VIDEO) == -1) {
      std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
   }

   // initialize TTF system for text rendering.
   if (TTF_Init() == -1) {
      std::cerr << "Unable to initialize TTF: " << TTF_GetError() << std::endl;
      return;
   }

   // load font
   font = TTF_OpenFont("./graphics/bold.ttf", 70);

   // create window and renderer
   SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

   // initialize random
   srand((unsigned)time(NULL));
}

Game::~Game() {
   std::cout << "Closing window..." << std::endl;

   if (font != nullptr) {
      TTF_CloseFont(font);
   }
   if (renderer != nullptr) {
      SDL_DestroyRenderer(renderer);
   }
   if (window != nullptr) {
      SDL_DestroyWindow(window);
   }
   if (pipeTextures.size()) {
      for (auto pipeTexture : pipeTextures) {
         SDL_DestroyTexture(pipeTexture);
      }
   }
   if (birdTexture != nullptr) {
      SDL_DestroyTexture(birdTexture);
   }

   TTF_Quit();
   SDL_Quit();
}

int Game::run() {
   SDL_Event event;

   // load images and create textures for pipes and bird
   birdTexture = IMG_LoadTexture(renderer, "./graphics/mogus.png");

   for (int i = 1; i < 4; i++) {
      std::string img = "./graphics/pipe-" + std::to_string(i) + ".png";
      pipeTextures.insert(pipeTextures.end(), IMG_LoadTexture(renderer, img.c_str()));
   }

   // create bird
   if (!bird) {
      bird = std::make_unique<Bird>(*renderer, *birdTexture, BIRD_SIZE, BIRD_X, BIRD_Y);
   }

   // create first pipe
   if (pipes.empty()) {
      pipes.insert(pipes.end(), std::make_unique<Pipe>(*renderer, *pipeTextures[randInt(0, 2)], PIPE_WIDTH, PIPE_HEIGHT, PIPE_INTERVAL, PIPE_SPEED));
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

      // update frame and check for collitions
      updateFrame();
      collide();

      // clear renderer
      SDL_SetRenderDrawColor(renderer, 0x8a, 0xef, 0xff, 0xff);
      SDL_RenderClear(renderer);

      // draw new frame to renderer
      drawFrame();

      // update score text
      drawScore();

      // present renderer
      SDL_RenderPresent(renderer);

      // wait for next frame
      frameTime = SDL_GetTicks() - frameStart;
      if (1000 / FPS > frameTime) {
         SDL_Delay(1000 / FPS - frameTime);
      }
   }

   SDL_Delay(1000);

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
      pipes.insert(pipes.end(), std::make_unique<Pipe>(*renderer, *pipeTextures[randInt(0, 2)], PIPE_WIDTH, PIPE_HEIGHT, PIPE_INTERVAL, PIPE_SPEED));
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

void Game::collide() {
   // get position and shift of current pipe
   const int pipeX = pipes[0]->getX();

   // pipe is already passed
   if (pipes[0]->isPassed()) {
      return;
   }

   // pipe passed or check collision between pipe and bird
   if (pipeX + PIPE_WIDTH - 25 < BIRD_X) {
      score++;
      pipes[0]->setPassed();
   } else {
      const int pipeShift = pipes[0]->getShift();
      const int birdY = bird->getY();

      const int gapY = height / 2 + pipeShift;

      const int gapTop = gapY - 75;
      const int gapBottom = gapY + 80;

      const bool validY = (birdY > gapTop) && (birdY + BIRD_SIZE < gapBottom);

      // bird is within the gap
      if (validY) {
         return;
      }

      const bool validX = pipeX > BIRD_X + BIRD_SIZE - 20;

      // bird has not yet collided with the pipe
      if (validX) {
         return;
      }

      // game lost
      state = State::LOST;
   }
}

void Game::drawScore() {
   SDL_Color color{0xff, 0xff, 0xff, 0xff};
   std::string scoreStr = std::to_string(score);

   auto surface = TTF_RenderText_Solid(font, scoreStr.c_str(), color);
   if (surface == nullptr) {
      std::cerr << "Unable to create a surface with a text: " << TTF_GetError() << std::endl;
      return;
   }

   auto texture = SDL_CreateTextureFromSurface(renderer, surface);
   if (texture == nullptr) {
      std::cerr << "Unable to create texture from a text surface: " << SDL_GetError() << std::endl;
      return;
   }

   SDL_RenderCopy(renderer, texture, NULL, &scoreDst);
   SDL_DestroyTexture(texture);
}