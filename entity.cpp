#include <iostream>
#include "entity.h"


Entity::Entity(SDL_Rect rect) {
	this->rect = rect;
}

void Entity::draw(SDL_Renderer *renderer) {
	std::cout << "entity rendering..." << std::endl;
}

void Entity::update() {
	std::cout << "entity updating..." << std::endl;
}
