#include <raylib.h>
#include "game.hpp"
#include "laser.hpp"

// format strings for the scores
std::string formatWidthLeadingZeros(int score, int width){
    std::string numberText = std::to_string(score);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main(void){

    int windowOffset = 50;
    int windowWidth = 750;
    int windowHeight = 700;
    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
 
    InitWindow(windowWidth + windowOffset, windowHeight + windowOffset * 2, "Space Invaders");
    InitAudioDevice();

    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    // Set game at constant speed (ie. loop 60 per sec)
    SetTargetFPS(60);
    Game game;
    while (!WindowShouldClose()){
        UpdateMusicStream(game.music);
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
        //Show the score
        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = formatWidthLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        //Show the highscore
        DrawTextEx(font, "HIGH SCORE", {570, 15}, 34, 2, yellow);
        std::string highscoreText = formatWidthLeadingZeros(game.highscore, 5);        
        DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, yellow);
        
        game.Draw();
        EndDrawing(); 
    }
   
    UnloadTexture(spaceshipImage);
    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}