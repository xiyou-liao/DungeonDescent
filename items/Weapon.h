
#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include <string>

class Weapon : public Item {
public:
    Weapon(
     const std::string& name,
     float damage,
     const char* singleTextureFilepath,
     const char* combinedTextureFilepath,
     float attackRange
 ) ;
    void animate(float deltaTime);
    void update(float deltaTime, Direction playerDirection);
    void render(Vector2 playerPosition);

    void attack(Direction direction);

    bool isAttacking() const;
    ~Weapon() override;
    const char* getCombinedTextureFilepath() const;

    float getDamage() const;
    float getAttackRange() const;

private:
    float mAttackDamage;
    float mAttackRange = 100.0f;
    Vector2 mScale;

    Texture2D mSingleTexture;
    Vector2 mSpriteSheetDimensions;
    bool mIsAttacking = false;
    float mCooldown = 0.0f;
    Direction mDirection;
    const char* mCombinedTextureFilepath;
};
#endif //WEAPON_H