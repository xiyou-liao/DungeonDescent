#ifndef SCENE_H
#define SCENE_H

#include "../entities/Entity.h"

struct GameState {
    Entity* protag = nullptr;
    Map* map = nullptr;
    std::vector<Entity*> entities;

    SceneID nextSceneID = NO_SCENE;
};

class Scene {
protected:
    GameState mGameState;
    Vector2 mOrigin;
    const char* mBGColourHexCode = "#000000";

public:
    Scene();
    Scene(Vector2 origin, const char* bgHexCode);
    virtual ~Scene() {}

    virtual void initialize() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
    virtual void shutdown() = 0;
    virtual void respawn() = 0;
    virtual void restart() = 0;

    GameState& getState() { return mGameState; }
    Vector2 getOrigin() const { return mOrigin; }

    const char* getBGColourHexCode() const { return mBGColourHexCode; }
};

#endif //SCENE_H