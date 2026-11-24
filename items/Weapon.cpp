#include "Weapon.h"

using namespace std;

Weapon::Weapon(
    const std::string& name,
    float damage,
    const char* singleTextureFilepath,
    const char* combinedTextureFilepath
) :
    Item(name, singleTextureFilepath),
    mAttackDamage{damage},
    mSingleTexture{LoadTexture(singleTextureFilepath)},
    mCombinedTextureFilepath{combinedTextureFilepath}
{}


Weapon::~Weapon() {UnloadTexture(mSingleTexture);}
const char* Weapon::getCombinedTextureFilepath() const {return mCombinedTextureFilepath;}