
#ifndef BASE_CHARACTER_H //This type of definition is used in case the compiler tries to include definitions more than once.
#define BASE_CHARACTER_H
#include "raylib.h"

//This is the class used for the characters of the game, using inheritance to share code between the player or the enemy.

class BaseCharacter
{
private:
    bool bisAlive {true};

protected:
    Texture2D texture{LoadTexture("characters/knight_idle.png")};
    Texture2D idle{LoadTexture("characters/knight_idle.png")};
    Texture2D run{LoadTexture("characters/knight_run.png")};    
    Vector2 worldPos{};
    // 1: Facing right, -1, facing left
    float rightleft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    Vector2 worldPosLastFrame{};
    float scale{4.0f};
    Vector2 velocity{};

public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void unDoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool GetisAlive () {return bisAlive; }
    void SetAlive (bool isAlive) { bisAlive = isAlive; }
    
};

#endif


