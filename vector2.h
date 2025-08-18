#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2 {
	int x;
	int y;

	Vector2(int x, int y);
	Vector2(int xy);
	Vector2();

	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator*(const Vector2& other) const;
	Vector2& operator+=(const Vector2& other);
	Vector2& operator*=(const Vector2& other);
};

#endif // VECTOR2_H