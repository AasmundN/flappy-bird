#ifndef ENTITYH
#define ENTITYH

#include <SDL.h>

class Entity {
 public:
   Entity() : rect({0, 0, 0, 0}) {}
   virtual ~Entity() = default;

   virtual void render(SDL_Renderer &renderer) = 0;
   virtual void update() = 0;

 protected:
   SDL_Rect rect;
};

#endif