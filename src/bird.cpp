#include "bird.h"

#include <SDL_image.h>

#define GRAVITY -1

Bird::Bird(SDL_Renderer &renderer, SDL_Texture &texture) : renderer(renderer), texture(texture), velocity(10), acceleration(GRAVITY), angle(0) {
   rect.h = 70;
   rect.w = 70;

   rect.x = 100;
   rect.y = 200;
}

void Bird::render() {
   if (velocity >= 12) {
      angle = 0;
   } else if (velocity <= -12) {
      angle = 140;
   } else {
      angle = 140 - (velocity + 12) * (140 / 24);
   }

   SDL_RenderCopyEx(&renderer, &texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Bird::update() {
   velocity += acceleration;

   if (rect.y - velocity > 750) {
      rect.y = 750;
      return;
   }

   rect.y -= velocity;
}

void Bird::jump() {
   velocity = 12;
}