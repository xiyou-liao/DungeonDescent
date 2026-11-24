#include "Entity.h"

void Entity::move(float deltaTime) {
    std::cout << mVelocity.x << ", "
            << mVelocity.y << std::endl;

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


Entity::Entity(
    Vector2 position,
    Vector2 scale,
    const char* textureFilepath,
    Vector2 spriteSheetDimensions,
    const std::map<Direction, std::vector<int>>& animationAtlas
) :
    mPosition{ position },
    mVelocity{ 0.0f, 0.0f },
    mScale{ scale },
    mTexture{ LoadTexture(textureFilepath) },
    mSpriteSheetDimensions{ spriteSheetDimensions },
    mDirection{ RIGHT },
    mFrameSpeed{ DEFAULT_FRAME_SPEED },
    mSpeed{ DEFAULT_SPEED },
    mAnimationAtlas{animationAtlas},
    mAnimationIndices{animationAtlas.at(RIGHT)}
{}

Entity::~Entity() { UnloadTexture(mTexture); }


void Entity::animate(float deltaTime) {
    if (mAnimationIndices.empty()) return;
    mAnimationIndices = mAnimationAtlas.at(mDirection);

    mAnimationTime += deltaTime;
    float secondsPerFrame = 1.0f / mFrameSpeed;

    if (mAnimationTime >= secondsPerFrame)
    {
        mAnimationTime = 0.0f;

        mCurrentFrameIndex++;
        mCurrentFrameIndex %= mAnimationIndices.size();
    }
}

void Entity::render() {
    if (mEntityStatus == INACTIVE) return;
    if (mAnimationIndices.empty()) return;

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

    //uncomment to see collision boxes for entities
    //displayCollider();
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