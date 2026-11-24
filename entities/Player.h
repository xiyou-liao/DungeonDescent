

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../items/Weapon.h"

class Player : public Entity {
public:
    //Player(Vector2 position, Vector2 scale, const char* textureFilePath);
    Player(
        Vector2 position,
        Vector2 scale,
        const char* textureFilePath,
        Vector2 spriteSheetDimensions
    );
    void update(float deltaTime) override;
    void handleMovement();

    // void basicAttack();
    // void useAbilityQ();
    // void useAbilityE();
    //
    // void equipWeapon(Weapon* weapon);
    // void unequipWeapon();

    //void useConsumable(int itemID);

  //  Inventory& getInventory();
private:
    Weapon* mWeapon = nullptr;

};


#endif //PLAYER_H