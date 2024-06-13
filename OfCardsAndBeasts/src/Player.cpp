#include "Player.h"

Player::Player(Vector2 startPosition)
{
	position = startPosition;
	speed = 200.0f;
}

void Player::Update(float deltaTime)
{
	if (IsKeyDown(KEY_W)) position.y -= speed * deltaTime;
	if (IsKeyDown(KEY_S)) position.y += speed * deltaTime;
	if (IsKeyDown(KEY_A)) position.x -= speed * deltaTime;
	if (IsKeyDown(KEY_D)) position.x += speed * deltaTime;
}

void Player::Draw()
{
	DrawCircleV(position, 25, BLUE);
}
