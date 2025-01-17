#include "Character.h"
#include "raymath.h"

//Construct function
Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

//Getting the position of the player on screen
Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
        };
}

//Tick function: 
void Character::tick(float deltaTime)
{     
    //If player is NOT alive, finish the call of tick.
    if (!GetisAlive()) return;

    //Input tracking of the player for movement.
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    //Parent function of tick.
    BaseCharacter::tick(deltaTime);

    // Adding a sword to the player
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightleft > 0.f) //Facing right
    {
        origin = {0.f, weapon.width * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f; //Rotating the sword when pressing mouse button
    }
    else //Facing left
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f; //Rotating the sword when pressing mouse button
    }

    //Draw the sword
    Rectangle source{0.f,0.f, static_cast<float>(weapon.width) * rightleft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width*scale, weapon.height*scale};
    DrawTexturePro(weapon,source,dest,origin,rotation,WHITE);      
}

//Function to take damage and kill the player if less than 0
void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        SetAlive(false);
    }
}


