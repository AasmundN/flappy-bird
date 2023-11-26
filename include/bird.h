#ifndef BIRD_H
#define BIRD_H

#include "entity.h"

class Bird : public Entity {

 public:
   Bird(SDL_Renderer &renderer);
   ~Bird();
   void render(SDL_Renderer &renderer);
   void update();
   void jump();

 private:
   int velocity;
   int acceleration;
   const char *img = "graphics/mogus.png";
   SDL_Texture *img_texture;
};

#endif