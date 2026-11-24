#include "Player.h"

Player::Player(
    Vector2 position,
    Vector2 scale,
    const char* textureFilepath = "../assets/player.png",
    Vector2 spriteSheetDimensions = {8, 8}
): Entity(position, scale, textureFilepath, spriteSheetDimensions,
          {
              {DOWN, {0, 1, 2, 3, 4, 5, 6, 7}},
              {UP, {16, 17, 18, 19, 20, 21, 22, 23}},
              {LEFT, {32, 33, 34, 35, 36, 37, 38, 39}},
              {RIGHT, {48, 49, 50, 51, 52, 53, 54, 55}}
          },
          {
              {DOWN, {8, 9, 10, 11, 12, 13, 14, 15}},
              {UP, {24, 25, 26, 27, 28, 29, 30, 31}},
              {LEFT, {40, 41, 42, 43, 44, 45, 46, 47}},
              {RIGHT, {56, 57, 58, 59, 60, 61, 62, 63}}
          }
    ) {}

Player::~Player() {
    delete mWeapon;
}
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

void Player::equipWeapon(Weapon* weapon) {
    if (weapon) {
        setTexture(weapon->getCombinedTextureFilepath());
        mWeapon = weapon;
    }
}

void Player::basicAttack() {
    if (!mWeapon || getAnimation() == ATTACK) return;

    setAnimation(ATTACK);
}

void Player::handleAttack() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        basicAttack();
    }
}