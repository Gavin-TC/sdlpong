#include <iostream>
#include <thread>
#include <chrono>
#include "SDL2/SDL.h"
#include "paddle.h"
#include "ball.h"

void drawMiddleLine(int screenWidth, int screenHeight, int segments, SDL_Renderer* renderer);

// TODO:
//		- Render score with text
//		- Play sounds when ball hits something or a paddle scores
int main(int argc, char* argv[]) {
	const int screenWidth = 1280;
	const int screenHeight = 720;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}

	SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		return 3;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		return 3;
	}

	int ticks = 0;
	bool running{ true };
	bool justReset{ true };

	Vector2 paddleSize{ 10, 100 };
	Vector2 paddleDir{ 0, 0 };
	int startingY = (screenHeight / 2) - (paddleSize.y / 2);

	Paddle leftPaddle = Paddle(false, SDL_Rect{				50, startingY, paddleSize.x, paddleSize.y });
	Paddle rightPaddle = Paddle(true, SDL_Rect{ screenWidth - 50, startingY, paddleSize.x, paddleSize.y });

	Ball ball = Ball(SDL_Rect{ 0, 0, 10, 10 });
	Vector2 ballStart = Vector2(screenWidth / 2 - (ball.rect.w / 2), screenHeight / 2 - (ball.rect.h / 2));
	ball.rect.x = ballStart.x;
	ball.rect.y = ballStart.y;
	ball.freezeTicks = 60;

	while (running) {
		SDL_Event event;
		const Uint8* keystate = SDL_GetKeyboardState(NULL);

		paddleDir = Vector2(0);
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) running = false;
		}

		if (keystate[SDL_SCANCODE_W])	   paddleDir.y = -1;
		else if (keystate[SDL_SCANCODE_S]) paddleDir.y = 1;

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		leftPaddle.update(screenHeight, paddleDir, 10);
		rightPaddle.aiUpdate(ball, screenHeight);

		ball.update(screenWidth,
					screenHeight,
					ball.velocity.x < 0 ? leftPaddle : rightPaddle);

		if (ball.needsReset) {
			ball.rect.x = ballStart.x;
			ball.rect.y = ballStart.y;
			ball.needsReset = false;
			
			if (ball.velocity.x < 0) {
				rightPaddle.points++;
				ball.velocity = Vector2(rand() % 5 + 6, ball.velocity.y);
				std::cout << "right paddle has scored. new score: " << rightPaddle.points << std::endl;
			}
			else if (ball.velocity.x > 0) {
				leftPaddle.points++;
				ball.velocity = Vector2(-(rand() % 5 + 6), ball.velocity.y / 2);
				std::cout << "left paddle has scored. new score: " << leftPaddle.points << std::endl;
			}

			justReset = true;
			ball.freezeTicks = 60;
		}

		drawMiddleLine(screenWidth, screenHeight, 5, renderer);

		leftPaddle.draw(renderer);
		rightPaddle.draw(renderer);
		ball.draw(renderer);

		SDL_RenderPresent(renderer);
		std::this_thread::sleep_for(std::chrono::milliseconds((long) 16.67 / 2));

		ticks++;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void drawMiddleLine(int screenWidth, int screenHeight, int segmentHeight, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);

	int middle = screenWidth / 2;

	for (int y = 0; y < screenHeight; y += segmentHeight * 2) {
		SDL_RenderDrawLine(renderer, middle, y, middle, std::min(y + segmentHeight, screenHeight));
	}
}