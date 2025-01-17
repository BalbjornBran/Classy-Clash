#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture)
{
    worldPos = pos;
    texture = idle_Texture;
    idle = idle_Texture;
    run = run_Texture;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 2.5f;
}

//This is the tick function. gets and calculate the velocity of the character, we then run the parent tick function.
void Enemy::tick(float deltaTime)
{
    if (!GetisAlive()) return;

    //Get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity)<radius) velocity = {};

    BaseCharacter::tick(deltaTime);

    //If the character gets close to its target, it starts dealing damage per second.
    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

//Function to get the position of the screen of the enemy.
Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
