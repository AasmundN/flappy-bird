#include "pipe.h"

#include <SDL_image.h>

Pipe::Pipe(SDL_Renderer &renderer, SDL_Texture &texture, int width, int height, int interval, int speed)
    : renderer(renderer),
      texture(texture),
      interval(interval),
      width(width),
      height(height),
      speed(speed) {

   // set dimensions of pipe
   rect.h = height;
   rect.w = width;
   rect.x = 500;
}

void Pipe::render() {
   SDL_RenderCopy(&renderer, &texture, NULL, &rect);
}

void Pipe::update() {
   rect.x -= speed;
}
