#include "vector2.h"

Vector2::Vector2(int x, int y) {
	this->x = x;
	this->y = y;
}
Vector2::Vector2(int xy) {
	this->x = xy;
	this->y = xy;
}
Vector2::Vector2() {
	this->x = 0;
	this->y = 0;
}

bool Vector2::operator==(const Vector2& other) const {
	return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const {
	return x != other.x || y != other.y;
}

Vector2 Vector2::operator+(const Vector2& other) const {
	return Vector2{ x + other.x, y + other.y };
}

Vector2 Vector2::operator*(const Vector2& other) const {
	return Vector2{ x * other.x, y * other.y };
}

Vector2& Vector2::operator+=(const Vector2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}