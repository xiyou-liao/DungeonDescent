#ifndef ENTITY_H
#define ENTITY_H

#include "../game/Map.h"
#include "../game/Game.h"


enum EntityType {PLAYER};
enum AnimationType {WALK, ATTACK};

class Entity {
public:
    // static constexpr int DEFAULT_SIZE = 250;

   // static constexpr float Y_COLLISION_THRESHOLD = 0.5f;

    Entity();
    Entity(
        Vector2 position,
        Vector2 scale,
        const char* textureFilepath,
        Vector2 spriteSheetDimensions,
        const std::map<Direction, std::vector<int>>& walkAnimationAtlas,
        const std::map<Direction, std::vector<int>>& attackAnimationAtlas
    );
    virtual ~Entity();

    virtual void update(float deltaTime) = 0;
    virtual void render();
    bool isAlive() const;
    Vector2 getPosition() const;
    float getHealth() const;
    float getMaxHealth() const;
    Direction getDirection() const;

    void move(float deltaTime);
  //  void normalizeMovement() { Normalize(&mMovement); }
     void setVelocityDirection(Vector2 direction);

    //
    // void determineAnimationDirection(Vector2 direction);
    void moveUp();
    void moveLeft();
    void moveRight();
    void moveDown();
    // void resetMovement() { mMovement = { 0.0f, 0.0f }; }
protected:
    void animate(float deltaTime);
    void resetVelocity();
    void normalizeVelocity();
    void setAnimation(AnimationType animation);
    void setTexture(const char* textureFilepath);
    AnimationType getAnimation() const;

private:
    Vector2 mPosition;
    Vector2 mVelocity;
    Direction mDirection;
    float mSpeed;
    float mMaxHealth = 100.0f;
    float mHealth = mMaxHealth;

    Vector2 mScale;
    const char* mTextureFilePath;

    Status mEntityStatus = ACTIVE;
    // Vector2 mScale;
    // Vector2 mColliderDimensions;
    //
    Texture2D mTexture;
    Vector2 mSpriteSheetDimensions;


    AnimationType mAnimation = WALK;


    int mFrameSpeed;

    int   mCurrentFrameIndex = 0;
    float mAnimationTime     = 0.0f;

    std::map<Direction, std::vector<int>> mWalkAnimationAtlas;
    std::map<Direction, std::vector<int>> mAttackAnimationAtlas;
    std::vector<int> mAnimationIndices;
    // float mDamageCooldown = 0.0f;
    //
    // float mAngle;
    //
    // bool mIsCollidingTop    = false;
    // bool mIsCollidingBottom = false;
    // bool mIsCollidingRight  = false;
    // bool mIsCollidingLeft   = false;
    //
    // EntityType mEntityType;
    //
    // bool mTakingDamage = false;
    // bool isColliding(Entity* other) const;
    //
    // void checkCollisionY(const std::vector<Entity*>& collidableEntities);
    // void checkCollisionY(Map* map);
    //
    // void checkCollisionX(const std::vector<Entity*>& collidableEntities);
    // void checkCollisionX(Map* map);
    //
    // void resetColliderFlags() {
    //     mIsCollidingTop    = false;
    //     mIsCollidingBottom = false;
    //     mIsCollidingRight  = false;
    //     mIsCollidingLeft   = false;
    // }
    //

};



#endif //ENTITY_H