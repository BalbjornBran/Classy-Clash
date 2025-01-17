//Balbjorn Bran Copyright

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

// This is the main function of the game, taking care of all the drawing of the game.
int main()
{
    // The size of the window
    const int window[2] = {384, 384}; // width, height

    //Initialization of the window
    InitWindow(window[0], window[1], "Classy Clash by Balbjorn Bran");

    //Local variables needed for the game
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap.png"); //Loading a png as the map of the game.
    Vector2 mapPos{{0}, {0}}; //The position of the map
    const float mapScale{4.0}; //the scale of the map

    //Spawning the player character
    Character knight{window[0], window[1]}; 
    
    //Spawning the enemies, there are 2 types of enemies, so we create the 2 instances. In future updates if we want to increase the number of enemies, we can create a class that handles the enemy spawns and give them random variables or positions
    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle.png"),
        LoadTexture("characters/goblin_run.png")};
    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle.png"),
        LoadTexture("characters/slime_run.png")};
    
    // We then store the enemies in an Array just to set the variables and run the functionalities
    Enemy *Enemies[]{
        &goblin,
        &slime};

    //Set the reference to the player's character in the enemies for the enemy to follow the player and attack him.
    for (auto Enemy : Enemies)
    {
        Enemy->setTarget(&knight);
    }

    //Set the textures that the enemies are going to use.
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};


    // At this point we will start the while function to draw all the frames on the window.
    SetTargetFPS(60);
    while (!WindowShouldClose()) //if the player doesn't close the window, we will keep drawing the game.
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        // In this case, we are not moving the player, we are moving the map, so, we move the map at the inverse were the player wants to move.
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw Map
        DrawTextureEx(map, mapPos, 0, mapScale, WHITE);

        // Now, we are manually drawing the props, just because we want to add collision to them. Just creating 2 of them in this project because its too time consuming for learning, but its enough to get the idea.
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        // this is were our win or lose statement will be applied.
        if (!knight.GetisAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue; // as soon as we get to the "dead" state, we just finish the while here.
        }
        else
        {
            // Just show the health on the screen.
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        // Calling the tick funcion on the player character
        knight.tick(GetFrameTime());
        // If the player is getting out of bound of the world, in this case we will undo the movement.
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + window[0] > map.width * mapScale ||
            knight.getWorldPos().y + window[1] > map.height * mapScale)
        {
            knight.unDoMovement();
        }

        // check prop collision (This is crazy to do on tick, but its just for learning.)
        for (auto prop : props)
        {
            //if collisioning with a prop...
            if (CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos())))
            {
                knight.unDoMovement(); //Undo movement.
            }
        }

        //For every enemy, lets call the tick function as well.
        for (auto enemy : Enemies)
        {
            enemy->tick(GetFrameTime());
        }

        //If the player is attacking, we are checking if we're dealing damage. The enemy is killed with just one attack.
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : Enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getCollisionRec()))
                {
                    enemy->SetAlive(false);
                }
            }
        }

        // Stop drawing
        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(map);
    return 0;
}