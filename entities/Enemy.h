//
// Created by xiyou on 11/24/2026.
//

#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

enum AIState {IDLE, FOLLOWING};
class Enemy : public Entity {
public:
    Enemy(
        Vector2 position,
        Vector2 scale,
        float maxHealth,
        const char* textureFilepath,
        Vector2 spriteSheetDimensions,
        const std::map<Direction, std::vector<int>>& walkAnimationAtlas,
        const std::map<Direction, std::vector<int>>& attackAnimationAtlas
    );
   void update(float deltaTime) override;

    virtual void AIActivate(Entity* target, float deltaTime) = 0;

    ~Enemy() override;

    void setTarget(Entity* tar);
    virtual void attack(Entity* target) = 0;
    void takeDamage(float damage);
protected:
    AIState getAIState() const;
    void setAIState(AIState state);
    Entity* getTarget() const;
    float getDamage() const;

private:
    Entity* target = nullptr;
    AIState mAIState = IDLE;
    float mDamage = 10.0f;

};

#endif //ENEMY_H