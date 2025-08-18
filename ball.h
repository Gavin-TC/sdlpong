#ifndef BALL_H
#define BALL_H

#include "entity.h"
#include "paddle.h"

class Ball : public Entity {
public:
	bool needsReset = false;
	int freezeTicks = 0;

	Ball(SDL_Rect rect);

	void draw(SDL_Renderer* renderer) override;
	//void update(SDL_Rect paddleContext);
	void update(int width, int height, Paddle paddle);
	bool collidingWithPaddle(Paddle paddle);
	bool collidingWithWalls(int width);
	bool collidingWithRoof(int height);
};

#endif // BALL_H
