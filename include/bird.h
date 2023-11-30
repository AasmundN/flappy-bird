#ifndef BIRD_H
#define BIRD_H

#include "entity.h"

class Bird : public Entity {
 public:
   Bird(SDL_Renderer &renderer, SDL_Texture &texture, int size, int x, int y);
   virtual ~Bird() = default;

   void render();
   void update();
   void jump();

   int getY() { return rect.y; }

 private:
   int velocity;
   int acceleration;
   double angle;
};

#endif