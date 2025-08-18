#ifndef PADDLE_H
#define PADDLE_H

#include "entity.h"

class Paddle : public Entity {
public:
	int points = 0;
	bool aiControlled = false;

	Paddle(bool aiControlled, SDL_Rect rect);

	void draw(SDL_Renderer *renderer) override;
	void update(int maxHeight, Vector2 dir, int speed);
};

#endif // PADDLE_h