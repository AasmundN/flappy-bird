#ifndef PIPE_H
#define PIPE_H

#include "entity.h"

class Pipe : public Entity {
 public:
   Pipe(SDL_Renderer &renderer, SDL_Texture &texture, int width, int height, int interval, int speed);
   virtual ~Pipe() = default;
   void render();
   void update();
   int getX() { return rect.x; }

 private:
   SDL_Renderer &renderer;
   SDL_Texture &texture;
   int interval;
   int width;
   int height;
   int speed;
};

#endif