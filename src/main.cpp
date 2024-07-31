#include <raylib.h>
#include "game.hpp"
#include "laser.hpp"

int main(void){

    int windowWidth = 750;
    int windowHeight = 700;
    Color grey = {29, 29, 27, 255};
 
    InitWindow(windowWidth, windowHeight, "Space Invaders");
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
        game.Draw();
        EndDrawing(); 
    }
   
    CloseWindow();
    return 0;
}