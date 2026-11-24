#include "Player.h"

Player::Player(
    Vector2 position,
    Vector2 scale,
    const char* textureFilepath,
    Vector2 spriteSheetDimensions
): Entity(position, scale, textureFilepath, spriteSheetDimensions,
{
                {DOWN,  { 0,  1,  2,  3,  4,  5,  6,  7}},
                {UP,    { 8,  9, 10, 11, 12, 13, 14, 15}},
                {LEFT,  {16, 17, 18, 19, 20, 21, 22, 23}},
                {RIGHT, {24, 25, 26, 27, 28, 29, 30, 31}}
                }
    ) {}


void Player::handleMovement() {
    resetVelocity();
    if (IsKeyDown(KEY_W)) moveUp();
    if (IsKeyDown(KEY_S)) moveDown();
    if (IsKeyDown(KEY_A)) moveLeft();
    if (IsKeyDown(KEY_D)) moveRight();
    normalizeVelocity();
}
void Player::update(float deltaTime) {
    handleMovement();
    move(deltaTime);
    animate(deltaTime);
}
