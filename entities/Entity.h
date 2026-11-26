#ifndef ENTITY_H
#define ENTITY_H

#include "../game/Map.h"
#include "../game/Game.h"



enum AnimationType {WALK, ATTACK};

class Entity {
public:
     static constexpr int DEFAULT_SIZE = 250;

    static constexpr float Y_COLLISION_THRESHOLD = 0.5f;

    Entity();
    Entity(
        Vector2 position,
        Vector2 scale,
        float maxHealth,
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
    void setDirection(Direction dir);
    void setDirection(Vector2 dir);

    void move(float deltaTime);
  //  void normalizeMovement() { Normalize(&mMovement); }
     void setVelocityDirection(Vector2 direction);
    Vector2 getColliderDimensions() const;
    bool isActive() const;
    //
    // void determineAnimationDirection(Vector2 direction);
    void moveUp();
    void moveLeft();
    void moveRight();
    void moveDown();

    void displayCollider();
    void decreaseHealth(float damage);

    bool isMouseClickedOnEntity(Vector2 mousePosition, Entity* entity);

    // void resetMovement() { mMovement = { 0.0f, 0.0f }; }
protected:
    void animate(float deltaTime);
    void resetVelocity();
    void normalizeVelocity();
    void setAnimation(AnimationType animation);
    void setTexture(const char* textureFilepath);
    AnimationType getAnimation() const;
    void setPosition(Vector2 newPosition);
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
    Vector2 mColliderDimensions;

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
    bool mIsCollidingTop    = false;
    bool mIsCollidingBottom = false;
    bool mIsCollidingRight  = false;
    bool mIsCollidingLeft   = false;



    bool mTakingDamage = false;
    bool isColliding(Entity* other) const;

    void checkCollisionY(const std::vector<Entity*>& collidableEntities);
    void checkCollisionY(Map* map);

    void checkCollisionX(const std::vector<Entity*>& collidableEntities);
    void checkCollisionX(Map* map);

    void resetColliderFlags();


};



#endif //ENTITY_H