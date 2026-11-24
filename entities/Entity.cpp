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
    const std::map<Direction, std::vector<int>>& walkAnimationAtlas,
    const std::map<Direction, std::vector<int>>& attackAnimationAtlas
) :
    mPosition{ position },
    mVelocity{ 0.0f, 0.0f },
    mScale{ scale },
    mTexture{ LoadTexture(textureFilepath) },
    mSpriteSheetDimensions{ spriteSheetDimensions },
    mDirection{ RIGHT },
    mFrameSpeed{ DEFAULT_FRAME_SPEED },
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