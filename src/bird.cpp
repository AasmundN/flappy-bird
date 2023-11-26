#include "bird.h"

#include <SDL_image.h>

#include <iostream>

#define GRAVITY -2

Bird::Bird() : velocity(10), acceleration(GRAVITY) {
   SDL_Rect *rect = getRect();

   rect->h = 70;
   rect->w = 70;

   rect->x = 100;
   rect->y = 200;
}

void Bird::render(SDL_Renderer &renderer) {
   SDL_Texture *img_texture = IMG_LoadTexture(&renderer, img);

   double angle;

   if (velocity >= 20)
      angle = 0;
   else if (velocity <= -20)
      angle = 120;
   else
      angle = 120 - (velocity + 20) * (120 / 40);

   SDL_RenderCopyEx(&renderer, img_texture, NULL, getRect(), angle, NULL, SDL_FLIP_NONE);
}

void Bird::update() {
   SDL_Rect *rect = getRect();

   velocity += acceleration;

   if (rect->y - velocity > 750)
      return;

   rect->y -= velocity;
}

void Bird::jump() {
   velocity = 20;
}