
#ifndef CODINGGOBLIN_H
#define CODINGGOBLIN_H

#include "Enemy.h"

class CodingGoblin : public Enemy {
public:
    //CodingGoblin(Vector2 position, Vector2 scale, const char* textureFilePath);
    CodingGoblin(
        Vector2 position,
        Vector2 scale,
        float maxHealth,
        const char* textureFilePath,
        Vector2 spriteSheetDimensions
    );
    // void update(float deltaTime) override;

    void attack(Entity* target) override;
    ~CodingGoblin();
    //void useConsumable(int itemID);
    void AIActivate(Entity* target, float deltaTime) override;
    //  Inventory& getInventory();
private:
    float mLerpFactor = 2.0f;

};


#endif //CODINGGOBLIN_H