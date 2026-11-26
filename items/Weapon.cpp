#include "Weapon.h"

using namespace std;

Weapon::Weapon(
    const std::string& name,
    float damage,
    const char* singleTextureFilepath,
    const char* combinedTextureFilepath,
    float attackRange
) :
    Item(name, singleTextureFilepath),
    mAttackDamage{damage},
    mSingleTexture{LoadTexture(singleTextureFilepath)},
    mCombinedTextureFilepath{combinedTextureFilepath},
    mAttackRange(attackRange)
{}

float Weapon::getDamage() const {
    return mAttackDamage;
}
float Weapon::getAttackRange() const {
    return mAttackRange;
}


Weapon::~Weapon() {UnloadTexture(mSingleTexture);}
const char* Weapon::getCombinedTextureFilepath() const {return mCombinedTextureFilepath;}