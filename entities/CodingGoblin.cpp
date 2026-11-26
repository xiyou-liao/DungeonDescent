#include "CodingGoblin.h"

CodingGoblin::CodingGoblin(
    Vector2 position,
    Vector2 scale,
    float maxHealth = 400.0f,
    const char* textureFilepath = "../assets/codingGoblin.png",
    Vector2 spriteSheetDimensions = {8, 8}
): Enemy(position, scale, maxHealth, textureFilepath, spriteSheetDimensions,
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
    ) {

}



// void CodingGoblin::update(float deltaTime) {
//     if (getTarget()) AIActivate(getTarget(), deltaTime);
//     move(deltaTime);
//     animate(deltaTime);
//
// }

CodingGoblin::~CodingGoblin() {}

void CodingGoblin::attack(Entity* target) {
    if (!isAlive() || !target || !target->isAlive() || getAnimation() == ATTACK) return;
    setDirection(target->getPosition() - getPosition());

    resetVelocity();
    setAnimation(ATTACK);
    target->decreaseHealth(getDamage());
}

void CodingGoblin::AIActivate(Entity* target, float deltaTime) {
    // if (target->getPosition().x < getPosition().x) setDirection(LEFT);
    // else setDirection(RIGHT);
    if (!target || !target->isAlive() || getAnimation() == ATTACK) return;

    float attackRange = 50.0f;
    float distance = Vector2Distance(getPosition(), target->getPosition());
    Vector2 positionDifference = target->getPosition() - getPosition();
    switch (getAIState()) {
        case IDLE:
            if (distance < 350.0f)
                 setAIState(FOLLOWING);
            break;
        case FOLLOWING:
            setDirection(positionDifference);
            if (distance > 450.0f) {
                setAIState(IDLE);
                break;
            }
            if (distance > attackRange) {
                Normalize(&positionDifference);
                setVelocityDirection(positionDifference);
            }else {
                attack(target);
            }
            break;
        default:
            break;
    }
}