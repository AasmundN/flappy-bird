#include "bird.h"

#include <SDL_image.h>

#define GRAVITY -1

#define SPRITE_WIDTH 192
#define SPRITE_HEIGHT 112
#define SPRITE_BORDER_WIDTH 4

Bird::Bird(SDL_Renderer &renderer, SDL_Texture &texture, int width, int height, int x, int y)
    : Entity(renderer, texture),
      jumpState(3),
      velocity(10),
      animationState(0),
      acceleration(GRAVITY),
      srcrect({SPRITE_BORDER_WIDTH, SPRITE_BORDER_WIDTH, SPRITE_WIDTH, SPRITE_HEIGHT}),
      angle(0) {
   rect.h = height;
   rect.w = width;
   rect.x = x;
   rect.y = y;
}

void Bird::render() {
   srcrect.x = SPRITE_BORDER_WIDTH + (2 * SPRITE_BORDER_WIDTH * animationState) + (SPRITE_WIDTH * animationState);
   SDL_RenderCopyEx(&renderer, &texture, &srcrect, &rect, angle, NULL, SDL_FLIP_NONE);

   if (animationState < 7) {
      animationState++;
   }
}

void Bird::update() {
   updateJumpState();

   if (velocity <= 10 || acceleration == GRAVITY) {
      velocity += acceleration;
   }

   if (rect.y - velocity > 750) {
      rect.y = 750;
      velocity = 0;
      return;
   }

   rect.y -= velocity;
}

void Bird::jump() {
   velocity = 0;
   jumpState = 0;
   animationState = 0;
}

void Bird::updateJumpState() {
   switch (jumpState) {
   case 0:
      acceleration = 4;
      break;

   case 1:
      acceleration = 7;
      break;

   case 2:
      acceleration = GRAVITY;
      break;
   }

   if (jumpState < 3) {
      jumpState++;
   }
}