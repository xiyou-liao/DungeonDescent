
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
     const char* combinedTextureFilepath
 ) ;
    void animate(float deltaTime);
    void update(float deltaTime, Direction playerDirection);
    void render(Vector2 playerPosition);

    void attack(Direction direction);

    bool isAttacking() const;
    ~Weapon() override;
    const char* getCombinedTextureFilepath() const;
private:
    float mAttackDamage;

    Vector2 mScale;

    Texture2D mSingleTexture;
    Vector2 mSpriteSheetDimensions;
    bool mIsAttacking = false;
    float mCooldown = 0.0f;
    Direction mDirection;
    const char* mCombinedTextureFilepath;
};
#endif //WEAPON_H