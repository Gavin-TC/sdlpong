#include <iostream>
#include "paddle.h"
#include "ball.h"

Paddle::Paddle(bool aiControlled, SDL_Rect rect) : Entity(rect) {
	this->aiControlled = aiControlled;
}

void Paddle::draw(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
	SDL_RenderFillRect(renderer, &rect);
}

void Paddle::update(int maxHeight, Vector2 dir, int speed) {
	velocity.y += dir.y * speed;

	if (rect.y + velocity.y > 0 && rect.y + rect.h + velocity.y < maxHeight)
		rect.y += velocity.y;

	// Slow down paddles movement
	if (dir == 0 && velocity.y != 0) {
		int zeroDir = -1 ? velocity.y < 0 : 1;
		velocity.y += zeroDir;
	}

	velocity.y = 0;
}

void Paddle::aiUpdate(const Ball& ball, int maxHeight) {
	int paddleCenter = rect.y + rect.h / 2;
	int ballCenter = ball.rect.y + ball.rect.h / 2;
	int distance = std::abs(ballCenter - paddleCenter);

	int maxSpeed = 100;
	int minSpeed = 1;
	int speed = std::min(maxSpeed, std::max(minSpeed, distance / 20));

	int dir = (ballCenter > paddleCenter) ? 1 : -1;
	velocity.y = dir * speed;

	if (rect.y + velocity.y > 0 && rect.y + rect.h + velocity.y < maxHeight)
		rect.y += velocity.y;
}