#include <raylib.h>

int main(void){

    int windowWidth = 750;
    int windowHeight = 700;
    Color grey = {29, 29, 27, 255};

    InitWindow(windowWidth, windowHeight, "Space Invaders");
    // Set game at constant speed (ie. loop 60 per sec)
    SetTargetFPS(60);

    // 1. Event Handling
    // 2. Update Positions
    // - Detect collisions
    // 3. Drawing Objects
     while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(grey);
        EndDrawing(); 
    }
   
    CloseWindow();
    return 0;
}