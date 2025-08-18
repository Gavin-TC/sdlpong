#ifndef ENTITY_H
#define ENTITY_H

#include "vector2.h"
#include "SDL2/SDL.h"

class Entity {
public:
	SDL_Rect rect;
	Vector2 velocity = Vector2();

	Entity(SDL_Rect rect);

	virtual void draw(SDL_Renderer *renderer);
	virtual void update();
};

#endif // ENTITY_H
