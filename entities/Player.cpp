#include "Player.h"

using namespace std;

Player::Player(
    Vector2 position,
    Vector2 scale,
    float maxHealth = 1000.0f,
    const char* textureFilepath = "../assets/player.png",
    Vector2 spriteSheetDimensions = {8, 8}
): Entity(position, scale, maxHealth, textureFilepath, spriteSheetDimensions,
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
    if (!isAlive()) return;
    if (getAnimation() == ATTACK) resetVelocity();
    else handleMovement();

    move(deltaTime);
    animate(deltaTime);
}

void Player::equipWeapon(Weapon* weapon) {
    if (weapon) {
        setTexture(weapon->getCombinedTextureFilepath());
        mWeapon = weapon;
    }
}

void Player::basicAttack(Enemy* enemy) {
    if (!mWeapon || !isAlive() || !enemy || !enemy->isAlive() || getAnimation() == ATTACK) return;
    float distance = GetLength(getPosition() - enemy->getPosition());

    //if (isMouseClickedOnEntity(mousePosition, enemy)) {

        cout << "enemy clicked on" << endl;

        if (distance <= getAttackRange()) {
            setDirection(enemy->getPosition() - getPosition());
            resetVelocity(); //stops moving to attack
            setAnimation(ATTACK);

            enemy->decreaseHealth(getAttackDamage());
            cout <<"attack registered and enemy health = " << enemy->getHealth() << endl;
        }
    //}

}

void Player::handleAttack(const vector<Enemy*>& enemies) {

    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) || !isAlive() || !mWeapon || getAnimation() == ATTACK) return;


    Vector2 mousePosition = GetMousePosition();

    for (Enemy* enemy : enemies) {
      //  cout << "checking enemy" << endl;
        if (!enemy || !enemy->isAlive()) continue;
        if (isMouseClickedOnEntity(mousePosition, enemy)) {
          //  cout << "mouse clicked on entity" << endl;
            basicAttack(enemy);
            break;
        }
    }

}

float Player::getAttackDamage() const {
    if (mWeapon) return mWeapon->getDamage();
    return 5.0f;
}
float Player::getAttackRange() const {
    if (mWeapon) return mWeapon->getAttackRange();
    return 30.0f;
}