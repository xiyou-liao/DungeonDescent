#include "game/Game.h"
#include "entities/Player.h"

constexpr int SCREEN_WIDTH = 1500;
constexpr int SCREEN_HEIGHT = 1000;
constexpr int FPS = 120;

constexpr Vector2 ORIGIN = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

//Global Variables
AppStatus gAppStatus = RUNNING;
float gPreviousTicks = 0.0f;
float gTimeAccumulator = 0.0f;


Player* gPlayer = nullptr;
Weapon* gWeapon = nullptr;
//Camera2D gCamera = {};

void initialize() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dungeon Descent");
    SetTargetFPS(FPS);
    gPlayer = new Player(
           {500.0f, 400.0f},
           {80.0f, 80.0f},
           "assets/player.png",
           {8, 8}
       );
    Weapon* fireSword = new Weapon(
    "Fire Sword",
    25.0f,
    "assets/fireSword.png",
    "assets/fireSword.png"
);
    gPlayer->equipWeapon(fireSword);
}

void processInput() {
    if (IsKeyPressed(KEY_Q)) gAppStatus = TERMINATED;
    gPlayer->handleAttack();
}

void update() {
    // Delta time
    float ticks = static_cast<float>(GetTime());
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    // Fixed timestep
    deltaTime += gTimeAccumulator;

    if (deltaTime < FIXED_TIMESTEP){
        gTimeAccumulator = deltaTime;
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP){
        deltaTime -= FIXED_TIMESTEP;
        gPlayer->update(FIXED_TIMESTEP);
        gTimeAccumulator = deltaTime;

    }
}

void render() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    gPlayer->render();

    EndDrawing();

}


void shutdown() {
    delete gPlayer;
    CloseWindow();
}

int main() {
    initialize();
    while (gAppStatus == RUNNING){
        processInput();
        update();
        render();
    }

    shutdown();
    return 0;
}