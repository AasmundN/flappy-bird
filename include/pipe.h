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
   int getShift() { return shift; }

   bool isPassed() { return passed; }
   void setPassed() { passed = true; }

 private:
   int interval, width, height, shift;
   int speed;
   bool passed;
};

#endif