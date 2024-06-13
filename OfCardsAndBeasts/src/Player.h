#pragma once
#include "raylib.h"

class Player
{
public:
	Vector2 position;
	float speed;

	Player(Vector2 startPosition);

	void Update(float deltaTime);
	void Draw();
};

