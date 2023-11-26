#include "bird.h"

#include <SDL_image.h>

#define GRAVITY -2

Bird::Bird(SDL_Renderer &renderer) : velocity(10), acceleration(GRAVITY) {
   rect.h = 70;
   rect.w = 70;

   rect.x = 100;
   rect.y = 200;

   img_texture = IMG_LoadTexture(&renderer, img);
}

Bird::~Bird() {
   SDL_DestroyTexture(img_texture);
}

void Bird::render(SDL_Renderer &renderer) {
   double angle;

   if (velocity >= 20)
      angle = 0;
   else if (velocity <= -20)
      angle = 120;
   else
      angle = 120 - (velocity + 20) * (120 / 40);

   SDL_RenderCopyEx(&renderer, img_texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
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
   velocity = 20;
}