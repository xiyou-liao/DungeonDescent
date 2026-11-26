#include "game/Game.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/CodingGoblin.h"

using namespace std;

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
CodingGoblin* gCodingGoblin = nullptr;
vector<Enemy*> enemies;

//Camera2D gCamera = {};

void initialize() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dungeon Descent");
    SetTargetFPS(FPS);
    gPlayer = new Player(
           {500.0f, 400.0f},
           {80.0f, 80.0f},
           1000.0f,
           "assets/player.png",
           {8, 8}
       );
    Weapon* fireSword = new Weapon(
    "Fire Sword",
    250.0f,
    "assets/fireSword.png",
    "assets/fireSword.png",
    100.0f
);
    gPlayer->equipWeapon(fireSword);

    gCodingGoblin = new CodingGoblin(
        {700.0f, 400.0f},          // Position
        {80.0f, 80.0f},            // Scale
        400.0f,
        "assets/codingGoblin.png", // Texture filepath
        {8, 8}                    // Sprite sheet dimensions
    );
    gCodingGoblin->setTarget(gPlayer);
    enemies.push_back(gCodingGoblin);
}

void processInput() {
    if (IsKeyPressed(KEY_Q)) gAppStatus = TERMINATED;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        cout << "left nouse button held!" << endl;
    }

    gPlayer->handleAttack(enemies);
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
       // cout <<"Player health" << gPlayer->getHealth() << endl;
        for (Enemy* enemy : enemies) {
            enemy->update(FIXED_TIMESTEP);
        }
        gTimeAccumulator = deltaTime;

    }
}

void render() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    gPlayer->render();
    for (Enemy* enemy : enemies) {
        enemy->render();
    }
    EndDrawing();

}


void shutdown() {
    delete gPlayer;
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

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