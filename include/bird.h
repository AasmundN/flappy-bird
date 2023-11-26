#ifndef BIRD_H
#define BIRD_H

#include "entity.h"

class Bird : public Entity {
 public:
   Bird(SDL_Renderer &renderer, SDL_Texture &texture);
   virtual ~Bird() = default;
   
   void render();
   void update();
   void jump();

 private:
   SDL_Renderer &renderer;
   SDL_Texture &texture;
   int velocity;
   int acceleration;
   double angle;
};

#endif