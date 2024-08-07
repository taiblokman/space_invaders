#include <raylib.h>
#include "game.hpp"
#include "laser.hpp"

int main(void){

    int windowOffset = 50;
    int windowWidth = 750;
    int windowHeight = 700;
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
 
    InitWindow(windowWidth + windowOffset, windowHeight + windowOffset * 2, "Space Invaders");

    Font font = LoadFontEx("font/monofram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    // Set game at constant speed (ie. loop 60 per sec)
    SetTargetFPS(60);
    Game game;
    while (!WindowShouldClose()){
    // 1. Event Handling
        game.HandleInput();        
        game.Update();
    // 2. Update Positions
    // - Detect collisions
    // 3. Drawing Objects

        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775,730}, 3, yellow);
        if(game.run){
            DrawTextEx(font, "Level 01", {570, 740}, 34, 2, yellow);
        } else {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }

        float x = 50.0;
        for (int i= 0; i< game.lives; i++) {
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50;
        }
        
        game.Draw();
        EndDrawing(); 
    }
   
    CloseWindow();
    return 0;
}