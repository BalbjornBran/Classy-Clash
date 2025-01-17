#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(/* args */)
{
}

//Function to undo the movement. Just set the new world position calculated with the position of the last frame.
void BaseCharacter::unDoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
        };
}

void BaseCharacter::tick(float deltaTime)
{
     worldPosLastFrame = worldPos;

    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    //Movement of the character and updating the sprite of the character while moving or idleing
    if (Vector2Length(velocity) != 0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        texture = run;
        //  there is a shortcut to do this if/else statement:
        //          
        //  if (velocity.x < 0.f)
        //  {
        //      rightleft=-1.f;
        //  }
        //  else
        //  {
        //      rightleft = 1.f;
        //  }
        //  Its called the Ternary Operator and its written as follows        
        velocity.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
    }
    else
    {
        texture = idle;
    }

    //After executing the movement of the character, reset velocity for the next frame.
    velocity = {};

    // Draw the texture of the character on screen.
    Rectangle source{frame * width, 0.f, rightleft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}