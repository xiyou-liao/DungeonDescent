#include "Entity.h"

void Entity::move(float deltaTime) {
    // std::cout << mVelocity.x << ", "
    //         << mVelocity.y << std::endl;

    mPosition.x += mVelocity.x * deltaTime;
    mPosition.y += mVelocity.y * deltaTime;
}

bool Entity::isAlive() const {return mHealth > 0;}
Vector2 Entity::getPosition() const {return mPosition;}
float Entity::getHealth() const {return mHealth;}
float Entity::getMaxHealth() const {return mMaxHealth;}

void Entity::setVelocityDirection(Vector2 direction) {
    mVelocity.x = direction.x * mSpeed;
    mVelocity.y = direction.y * mSpeed;
}

Entity::Entity() :
    mPosition{ 0.0f, 0.0f },
    mVelocity{ 0.0f, 0.0f },
    mScale{ DEFAULT_SIZE, DEFAULT_SIZE },
    mColliderDimensions{ DEFAULT_SIZE, DEFAULT_SIZE },
    mTexture{}, mSpriteSheetDimensions{},
    mWalkAnimationAtlas{}, mAttackAnimationAtlas{}, mAnimationIndices{}, mDirection{ RIGHT },
    mFrameSpeed{ 0 }, mSpeed{ DEFAULT_SPEED }{}

Entity::Entity(
    Vector2 position,
    Vector2 scale,
    float maxHealth,
    const char* textureFilepath,
    Vector2 spriteSheetDimensions,
    const std::map<Direction, std::vector<int>>& walkAnimationAtlas,
    const std::map<Direction, std::vector<int>>& attackAnimationAtlas
) :
    mPosition{ position },
    mVelocity{ 0.0f, 0.0f },
    mScale{ scale },
    mMaxHealth(maxHealth),
    mTexture{ LoadTexture(textureFilepath) },
    mSpriteSheetDimensions{ spriteSheetDimensions },
    mDirection{ RIGHT },
    mFrameSpeed{ DEFAULT_FRAME_SPEED },
    mColliderDimensions{scale.x * 0.5f, scale.y * 0.5f},
    mSpeed{ DEFAULT_SPEED },
    mWalkAnimationAtlas{walkAnimationAtlas},
    mAttackAnimationAtlas{attackAnimationAtlas},
    mAnimationIndices{walkAnimationAtlas.at(RIGHT)}
{}

Entity::~Entity() { UnloadTexture(mTexture); }


void Entity::animate(float deltaTime) {

    if (mAnimation == WALK) {
        mAnimationIndices = mWalkAnimationAtlas.at(mDirection);
    }else if (mAnimation == ATTACK) {
        mAnimationIndices = mAttackAnimationAtlas.at(mDirection);
    }
    if (mAnimationIndices.empty()) return;
    mAnimationTime += deltaTime;
    float secondsPerFrame = 1.0f / mFrameSpeed;

    if (mAnimationTime >= secondsPerFrame)
    {
        mAnimationTime = 0.0f;

        mCurrentFrameIndex++;
        if (mCurrentFrameIndex >= mAnimationIndices.size()) {
            if (mAnimation == ATTACK) {
                setAnimation(WALK);
                return;
            }
            else {
                mCurrentFrameIndex = 0;
            }
        }
    }
}

void Entity::render() {
    if (mEntityStatus == INACTIVE) return;

    Rectangle textureArea;

    textureArea = getUVRectangle(
        &mTexture,
        mAnimationIndices[mCurrentFrameIndex],
        mSpriteSheetDimensions.x,
        mSpriteSheetDimensions.y
    );

    Rectangle destinationArea = {
        mPosition.x, mPosition.y, mScale.x, mScale.y
    };

    Vector2 originOffset = { mScale.x / 2.0f, mScale.y / 2.0f };

    DrawTexturePro(
        mTexture,
        textureArea, destinationArea, originOffset,
        0.0f, WHITE
    );
    DrawText(TextFormat("%.0f", mHealth), mPosition.x,
        mPosition.y - mScale.y /2.0f, 15, RED);
    //uncomment to see collision boxes for entities
    displayCollider();
}

void Entity::resetVelocity() {
    mVelocity = {0.0f, 0.0f};
}
void Entity::normalizeVelocity() {
    Normalize(&mVelocity);
    mVelocity.x *= mSpeed;
    mVelocity.y *= mSpeed;
}

void Entity::moveRight() {
    mVelocity.x += 1.0f;
    mDirection = RIGHT;
}

void Entity::moveLeft() {
    mVelocity.x -= 1.0f;
    mDirection = LEFT;
}

void Entity::moveUp() {
    mVelocity.y -= 1.0f;
    mDirection = UP;
}

void Entity::moveDown() {
    mVelocity.y += 1.0f;
    mDirection = DOWN;
}

Direction Entity::getDirection() const {
    return mDirection;
}

void Entity::setTexture(const char* textureFilepath) {
    Texture2D newTexture = LoadTexture(textureFilepath);

    UnloadTexture(mTexture);
    mTexture = newTexture;
    mCurrentFrameIndex = 0;
    mAnimationTime = 0.0f;

}

void Entity::setAnimation(AnimationType animation) {
    if (mAnimation == animation) return;

    mAnimation = animation;
    mCurrentFrameIndex = 0;
    mAnimationTime = 0.0f;

    if (mAnimation == WALK) {
        mAnimationIndices = mWalkAnimationAtlas.at(mDirection);
    }
    else if (mAnimation == ATTACK) {
        mAnimationIndices = mAttackAnimationAtlas.at(mDirection);
    }
}

AnimationType Entity::getAnimation() const {
    return mAnimation;
}

void Entity::checkCollisionY(const std::vector<Entity*>& collidableEntities){
    for (size_t i = 0; i<collidableEntities.size(); i++) {
        Entity* collidableEntity = collidableEntities[i];
        if (collidableEntity == nullptr) continue;
        if (!collidableEntity->isActive()) continue;
        if (isColliding(collidableEntity)){

            float yDistance = fabs(mPosition.y - collidableEntity->mPosition.y);
            float yOverlap  = fabs(
                yDistance - (mColliderDimensions.y / 2.0f) -
                (collidableEntity->mColliderDimensions.y / 2.0f)
            );

            if (mVelocity.y > 0){
                mPosition.y -= yOverlap;
                mVelocity.y = 0;
                mIsCollidingBottom = true;

            }
            else if (mVelocity.y < 0) {
                mPosition.y += yOverlap;
                mVelocity.y = 0;
                mIsCollidingTop = true;

            }
        }
    }
}

void Entity::checkCollisionX(const std::vector<Entity*>& collidableEntities){
    for (size_t i = 0; i<collidableEntities.size(); i++) {
        Entity* collidableEntity = collidableEntities[i];
        if (collidableEntity == nullptr) continue;
        if (!collidableEntity->isActive()) continue;
        if (isColliding(collidableEntity)){

            float yDistance = fabs(mPosition.y - collidableEntity->mPosition.y);
            float yOverlap  = fabs(
                yDistance - (mColliderDimensions.y / 2.0f) -
                (collidableEntity->mColliderDimensions.y / 2.0f)
            );
            if (yOverlap < Y_COLLISION_THRESHOLD) continue;

            float xDistance = fabs(mPosition.x - collidableEntity->mPosition.x);
            float xOverlap  = fabs(
                xDistance - (mColliderDimensions.x / 2.0f) -
                (collidableEntity->mColliderDimensions.x / 2.0f)
            );

            if (mVelocity.x > 0) {
                mPosition.x -= xOverlap;
                mVelocity.x = 0;

                mIsCollidingRight = true;

            }else if (mVelocity.x < 0) {
                mPosition.x += xOverlap;
                mVelocity.x  = 0;

                mIsCollidingLeft = true;

            }
        }
    }
}
//
// void Entity::checkCollisionY(Map *map) {
//     if (map == nullptr) return;
//
//     Vector2 topCentreProbe = {
//         mPosition.x, mPosition.y - (mColliderDimensions.y / 2.0f)
//     };
//     Vector2 topLeftProbe = {
//         mPosition.x - (mColliderDimensions.x / 2.0f),
//         mPosition.y - (mColliderDimensions.y / 2.0f)
//     };
//     Vector2 topRightProbe = {
//         mPosition.x + (mColliderDimensions.x / 2.0f),
//         mPosition.y - (mColliderDimensions.y / 2.0f)
//     };
//
//     Vector2 bottomCentreProbe = {
//         mPosition.x, mPosition.y + (mColliderDimensions.y / 2.0f)
//     };
//     Vector2 bottomLeftProbe = {
//         mPosition.x - (mColliderDimensions.x / 2.0f),
//         mPosition.y + (mColliderDimensions.y / 2.0f)
//     };
//     Vector2 bottomRightProbe = {
//         mPosition.x + (mColliderDimensions.x / 2.0f),
//         mPosition.y + (mColliderDimensions.y / 2.0f)
//     };
//
//     float xOverlap = 0.0f;
//     float yOverlap = 0.0f;
//
//     if ((map->isSolidTileAt(topCentreProbe, &xOverlap, &yOverlap) ||
//          map->isSolidTileAt(topLeftProbe, &xOverlap, &yOverlap) ||
//          map->isSolidTileAt(topRightProbe, &xOverlap, &yOverlap)) &&
//         mVelocity.y < 0.0f && xOverlap < map->getTileSize() * 0.4f) {
//         mPosition.y     += yOverlap * 1.01f; // push down
//         mVelocity.y      = 0.0f;
//         mIsCollidingTop  = true;
//         if (mEntityType == PLATFORM) {
//             setAcceleration({0.0f, 0.0f});
//             setVelocity({0.0f, 0.0f});
//         }
//     }
//
//     if ((map->isSolidTileAt(bottomCentreProbe, &xOverlap, &yOverlap) ||
//          map->isSolidTileAt(bottomLeftProbe, &xOverlap, &yOverlap) ||
//          map->isSolidTileAt(bottomRightProbe, &xOverlap, &yOverlap)) &&
//         mVelocity.y > 0.0f) {
//         mPosition.y -= yOverlap; // push up
//         mVelocity.y = 0.0f;
//         mIsCollidingBottom = true;
//         if (mEntityType == PLATFORM) {
//             setAcceleration({0.0f, 0.0f});
//             setVelocity({0.0f, 0.0f});
//         }
//         if (mEntityType == NPC && mAIType == JUMPER) {
//             setVelocity({0.0f, -mJumpingPower});
//         }
//     }
// }
//
// void Entity::checkCollisionX(Map *map) {
//     if (map == nullptr) return;
//
//     Vector2 leftCentreProbe = {
//         mPosition.x - (mColliderDimensions.x / 2.0f), mPosition.y
//     };
//     Vector2 rightCentreProbe = {
//         mPosition.x + (mColliderDimensions.x / 2.0f), mPosition.y
//     };
//     Vector2 topLeftProbe = {
//         mPosition.x - (mColliderDimensions.x / 2.0f),
//         mPosition.y - (mColliderDimensions.y / 2.0f)
//     };
//     Vector2 topRightProbe = {
//         mPosition.x + (mColliderDimensions.x / 2.0f),
//         mPosition.y - (mColliderDimensions.y / 2.0f)
//     };
//
//     Vector2 bottomLeftProbe = {
//         mPosition.x - (mColliderDimensions.x / 2.0f),
//         mPosition.y + (mColliderDimensions.y / 2.0f)
//     };
//     Vector2 bottomRightProbe = {
//         mPosition.x + (mColliderDimensions.x / 2.0f),
//         mPosition.y + (mColliderDimensions.y / 2.0f)
//     };
//
//     float xOverlap = 0.0f;
//     float yOverlap = 0.0f;
//
//     if ((map->isSolidTileAt(rightCentreProbe, &xOverlap, &yOverlap) ||
//         map->isSolidTileAt(topRightProbe, &xOverlap, &yOverlap) ||
//         map->isSolidTileAt(bottomRightProbe, &xOverlap, &yOverlap))    &&
//              mVelocity.x > 0.0f && yOverlap >= 0.5f) {
//         mPosition.x -= xOverlap * 1.01f; // push left
//         mVelocity.x = 0.0f;
//         mIsCollidingRight = true;
//         if (mEntityType == PLATFORM) {
//             setAcceleration({0.0f, 0.0f});
//             setVelocity({0.0f, 0.0f});
//         }
//     }
//
//     if ((map->isSolidTileAt(leftCentreProbe, &xOverlap, &yOverlap) ||
//         map->isSolidTileAt(topLeftProbe, &xOverlap, &yOverlap) ||
//         map->isSolidTileAt(bottomLeftProbe, &xOverlap, &yOverlap)) &&
//         mVelocity.x < 0.0f && yOverlap >= 0.5f) {
//         mPosition.x      += xOverlap * 1.01f;
//         mVelocity.x       = 0.0f;
//         mIsCollidingLeft  = true;
//         if (mEntityType == PLATFORM) {
//             setAcceleration({0.0f, 0.0f});
//             setVelocity({0.0f, 0.0f});
//         }
//     }
// }

bool Entity::isColliding(Entity *other) const {
    if (!other->isActive() || other == this) return false;

    float xDistance = fabs(mPosition.x - other->getPosition().x) -
        ((mColliderDimensions.x + other->getColliderDimensions().x) / 2.0f);
    float yDistance = fabs(mPosition.y - other->getPosition().y) -
        ((mColliderDimensions.y + other->getColliderDimensions().y) / 2.0f);

    return xDistance < 0.0f && yDistance < 0.0f;
}

bool Entity::isActive() const {return mEntityStatus == ACTIVE;}
void Entity::resetColliderFlags() {
    mIsCollidingTop    = false;
    mIsCollidingBottom = false;
    mIsCollidingRight  = false;
    mIsCollidingLeft   = false;
}

Vector2 Entity::getColliderDimensions() const { return mColliderDimensions; }

void Entity::displayCollider() {
    // draw the collision box
    Rectangle colliderBox = {
        mPosition.x - mColliderDimensions.x / 2.0f,
        mPosition.y - mColliderDimensions.y / 2.0f,
        mColliderDimensions.x,
        mColliderDimensions.y
    };

    DrawRectangleLines(
        colliderBox.x,
        colliderBox.y,
        colliderBox.width,
        colliderBox.height,
        GREEN
    );
}

void Entity::setDirection(Direction dir) {mDirection = dir;}
void Entity::setDirection(Vector2 dir) {
    float dirX = fabs(dir.x);
    float dirY = fabs(dir.y);
    if (dirX > dirY) {
        if (dir.x < 0) mDirection = LEFT;
        else mDirection = RIGHT;
    }else {
        if (dir.y < 0) mDirection = UP;
        else mDirection = DOWN;
    }
}

void Entity::setPosition(Vector2 newPosition) {
    mPosition = newPosition;
}

void Entity::decreaseHealth(float damage) {
    if (!isAlive()) return;
    if (mHealth - damage <= 0.0f) mHealth = 0.0f;
    else mHealth -= damage;

    if (mHealth == 0.0f) {
        mEntityStatus = INACTIVE;
        resetVelocity();
    }
}

bool Entity::isMouseClickedOnEntity(Vector2 mousePosition, Entity* entity) {
    if (!entity) return false;

    Vector2 colliderDimensions = entity->getColliderDimensions();
    Vector2 entityPosition = entity->getPosition();

    float topLeftX = entityPosition.x - colliderDimensions.x / 2.0f;
    float topLeftY = entityPosition.y - colliderDimensions.y / 2.0f;
    float bottomRightX = entityPosition.x + colliderDimensions.x / 2.0f;
    float bottomRightY = entityPosition.y + colliderDimensions.y / 2.0f;

    if ((mousePosition.x >= topLeftX && mousePosition.x <= bottomRightX) &&
        (mousePosition.y >= topLeftY && mousePosition.y <= bottomRightY)) {
        return true;
    }
    return false;

}
