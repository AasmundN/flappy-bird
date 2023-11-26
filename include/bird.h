#ifndef BIRD_H
#define BIRD_H

#include "entity.h"

class Bird : public Entity {

 public:
   Bird();
   virtual ~Bird() = default;
   void render(SDL_Renderer &renderer);
   void update();
   void jump();

 private:
   int velocity;
   int acceleration;
   const char *img = "graphics/mogus.png";
};

#endif