#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>

class Entity {
 public:
   Entity(SDL_Renderer &renderer, SDL_Texture &texture) : renderer(renderer), texture(texture), rect({0, 0, 0, 0}) {}
   virtual ~Entity() = default;

   virtual void render() = 0;
   virtual void update() = 0;

 protected:
   SDL_Rect rect;
   SDL_Renderer &renderer;
   SDL_Texture &texture;
};

#endif