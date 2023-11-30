#include "pipe.h"

#include <SDL_image.h>

int randInt(int lower, int upper);

Pipe::Pipe(SDL_Renderer &renderer, SDL_Texture &texture, int width, int height, int interval, int speed)
    : Entity(renderer, texture),
      interval(interval),
      width(width),
      passed(false),
      height(height),
      speed(speed) {

   // set dimensions of pipe
   rect.h = height;
   rect.w = width;
   rect.x = 500;

   // set random shift
   shift = randInt(-125, 125);
   rect.y = -200 + shift;
}

void Pipe::render() {
   SDL_RenderCopy(&renderer, &texture, NULL, &rect);
}

void Pipe::update() {
   rect.x -= speed;
}
