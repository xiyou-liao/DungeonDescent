

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../items/Weapon.h"
#include "Enemy.h"

class Player : public Entity {
public:
    //Player(Vector2 position, Vector2 scale, const char* textureFilePath);
    Player(
        Vector2 position,
        Vector2 scale,
        float maxHealth,
        const char* textureFilePath,
        Vector2 spriteSheetDimensions
    );
    void update(float deltaTime) override;
    void handleMovement();
    void handleAttack(const std::vector<Enemy*>& enemies);
   // void render() override;
    void basicAttack(Enemy* enemy);
    // void useAbilityQ();
    // void useAbilityE();
    //
     void equipWeapon(Weapon* weapon);
    float getAttackDamage() const;
    float getAttackRange() const;

    // void unequipWeapon();
    ~Player();
    //void useConsumable(int itemID);

  //  Inventory& getInventory();
private:
    Weapon* mWeapon = nullptr;

};


#endif //PLAYER_H