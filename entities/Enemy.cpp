#include "Enemy.h"

Enemy::Enemy(
        Vector2 position,
        Vector2 scale,
        float maxHealth,
        const char* textureFilepath,
        Vector2 spriteSheetDimensions,
        const std::map<Direction, std::vector<int>>& walkAnimationAtlas,
        const std::map<Direction, std::vector<int>>& attackAnimationAtlas
    ): Entity(position, scale, maxHealth, textureFilepath, spriteSheetDimensions,
              walkAnimationAtlas,
                attackAnimationAtlas
          ) {}

Enemy::~Enemy() {}

void Enemy::update(float deltaTime) {
    if (!isAlive()) return;

    resetVelocity();

    if (getTarget() && getTarget()->isAlive()) {
        AIActivate(getTarget(), deltaTime);
    }

    move(deltaTime);
    animate(deltaTime);
}

AIState Enemy::getAIState() const {return mAIState;}

void Enemy::setAIState(AIState state) {mAIState = state;}

void Enemy::setTarget(Entity* tar) {target = tar;}

Entity* Enemy::getTarget() const {return target;}

float Enemy::getDamage() const {return mDamage;}


