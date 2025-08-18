#include <iostream>
#include "ball.h"

Ball::Ball(SDL_Rect rect) : Entity(rect) {
	velocity.x = rand() % 5 + 6;
	velocity.y = 0;
}

void Ball::draw(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
	SDL_RenderFillRect(renderer, &rect);
}

// `paddle` is the paddle that the ball is concerned with.
// Basically, if the balls x is to the left of the middle, the context is the left paddle.
// If the balls x is to the right of the middle, the context is the right paddle.
void Ball::update(int width, int height, Paddle paddle) {
	if (freezeTicks > 0) {
		freezeTicks--;
		return;
	}

	rect.x += velocity.x;
	rect.y += velocity.y;

	if (collidingWithPaddle(paddle)) {
		velocity.x *= -1;
		velocity.y += paddle.velocity.y + rand() % 5;
	}

	if (collidingWithRoof(height)) {
		velocity.y *= -1;
	}

	if (collidingWithWalls(width)) {
		needsReset = true;
	}
}

bool Ball::collidingWithPaddle(Paddle paddle) {
	if (rect.x < paddle.rect.x + paddle.rect.w &&
		rect.x + rect.w > paddle.rect.x &&
		rect.y < paddle.rect.y + paddle.rect.h &&
		rect.y + rect.h > paddle.rect.y)
		return true;
	return false;
}

bool Ball::collidingWithWalls(int width) {
	if (rect.x < 0 || rect.x + rect.w > width)
		return true;
	return false;
}

bool Ball::collidingWithRoof(int height) {
	if (rect.y < 0 || rect.y + rect.h > height)
		return true;
	return false;
}
