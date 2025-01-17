#include "game.hpp"
#include <iostream>
#include <fstream>

int gameWindowOffsetAlien = 25;
int gameWindowOffsetObstacles = 100;
int lastAlienSoundTime = 0.0;

Game::Game(){
    music = LoadMusicStream("Sounds/lights-out.ogg");
    explosionSound = LoadSound("Sounds/explosion.ogg");
    alienMoveSound = LoadSound("Sounds/fastinvader1.wav");
    gameOverSound = LoadSound("Sounds/JingleLose003.wav");
    InitGame();
};

Game::~Game(){
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
    UnloadSound(alienMoveSound);
    UnloadSound(gameOverSound);
}

void Game::Update()
{
    if (run){
        // Spawn the mysteryship randomly
        double currentTime = GetTime();
        if (currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
            mysteryship.Spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);        
        }
        
        for (auto& laser: spaceship.lasers){
            laser.Update();
        }   

        MoveAliens(); 
        AlienShootLaser();
        // PlaySound(alienMoveSound);
        if (GetTime() - lastAlienSoundTime >= 1.0){        
            PlaySound(alienMoveSound);
            lastAlienSoundTime = GetTime();
            //std::cout << "play alien sound" << std::endl;
        }        

        for(auto& laser: alienLasers ){
            laser.Update(); 
        }

        DeleteInactiveLasers();
        // std::cout << "Vector size: " << spaceship.lasers.size() << std::endl;

        mysteryship.Update();

        CheckForCollisions();
    } else if(IsKeyDown(KEY_ENTER)){
        ResetGame();
        InitGame();
    }

}

void Game::Draw(){

    // Draw the spaceship and lasers
    spaceship.Draw();
    for (auto& laser: spaceship.lasers){
        laser.Draw();
    }
    // Draw the obstacles
    for (auto& obstacle: obstacles) {
        obstacle.Draw();
    }
    // Draw the Aliens
    for (auto& alien: aliens) {
        alien.Draw();
    }
    // Draw the alien lasers
    for(auto& laser: alienLasers ){
        laser.Draw(); 
    }    
    // Draw the Mystery Ship
    mysteryship.Draw();
}

void Game::HandleInput(){
    if (run) {
        if(IsKeyDown(KEY_LEFT)) {
            spaceship.MoveLeft();
        } else if(IsKeyDown(KEY_RIGHT)) {
            spaceship.MoveRight();
        } else if(IsKeyDown(KEY_SPACE)){
            spaceship.FireLaser();
        }
    }

}

void Game::DeleteInactiveLasers()
{
    for(auto iter = spaceship.lasers.begin(); iter !=spaceship.lasers.end();){
        if (!iter -> active) {
            iter = spaceship.lasers.erase(iter);
        }
        else {
            ++ iter;
        }
    }
    for(auto iter = alienLasers.begin(); iter !=alienLasers.end();){
        if (!iter -> active) {
            iter = alienLasers.erase(iter);
        }
        else {
            ++ iter;
        }
    }    
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth))/5;

    for(int i = 0; i < 4; i++) {
        float offsetX = ((i + 1) * gap) + (i * obstacleWidth);
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100 - gameWindowOffsetObstacles)}));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    for(int row = 0; row < 5; row++) {
        for(int column = 0; column < 11; column++) {

            int alienType;
            if(row == 0) {
                alienType = 3;
            } else if (row == 1 || row == 2) {
                alienType = 2;
            } else {
                alienType = 1;
            }

            float x = 75 + column * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens()
{
    for(auto& alien: aliens){
        //check if any aliens touched the left or right screen boundaries
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - gameWindowOffsetAlien) {
            aliensDirection = -1;
            MoveDownAliens(4);
        } if(alien.position.x < 0 + gameWindowOffsetAlien) {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
    for(auto& alien: aliens){
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();

    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()){

        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type -1].width/2,
                                    alien.position.y + alien.alienImages[alien.type -1].height},6));
        timeLastAlienFired = GetTime();
    }                                 
}

void Game::CheckForCollisions()
{
    // Spaceship lasers
    for(auto& laser: spaceship.lasers) {
        // first check if we hit any aliens
        auto iter = aliens.begin();
        while (iter != aliens.end()) {
            if(CheckCollisionRecs(iter -> getRect(), laser.getRect())){
                PlaySound(explosionSound);                
                if(iter -> type == 1) score +=100;
                if(iter -> type == 2) score +=200;
                if(iter -> type == 3) score +=300;
                checkForHighScore();
                iter = aliens.erase(iter);
                laser.active = false;
            } else {
                ++iter;
            }            
        }
        // next check if we hit any blocks/obstacles
        for(auto& obstacle: obstacles) {
            auto iter = obstacle.blocks.begin();
            while (iter != obstacle.blocks.end()){
                if(CheckCollisionRecs(iter -> getRect(), laser.getRect())){
                    iter = obstacle.blocks.erase(iter);
                    laser.active = false;
                }
                else {
                    ++iter;
                }
            }
        }
        // check if we hit the mysteryship
        if(CheckCollisionRecs(mysteryship.getRect(), laser.getRect())){
            PlaySound(explosionSound);
            mysteryship.alive = false;
            laser.active = false;
            score += 500;
            checkForHighScore();
        }
    }    

    //Alien Lasers
    for(auto& laser: alienLasers) {
        if(CheckCollisionRecs(laser.getRect(), spaceship.getRect())){
            laser.active = false;
            std::cout << "Spaceship Hit" << std::endl;
            lives--;
            if(lives == 0) {
                StopMusicStream(music);
                GameOver();
                PlaySound(gameOverSound);
            }
        }
        // next check if we hit any blocks/obstacles
        for(auto& obstacle: obstacles) {
            auto iter = obstacle.blocks.begin();
            while (iter != obstacle.blocks.end()){
                if(CheckCollisionRecs(iter -> getRect(), laser.getRect())){
                    iter = obstacle.blocks.erase(iter);
                    laser.active = false;
                }
                else {
                    ++iter;
                }
            }
        }        
    }
    
    // Alien collision with obstacle

    for(auto& alien: aliens) {
        for(auto& obstacle: obstacles) {
            auto iter = obstacle.blocks.begin();
            while (iter != obstacle.blocks.end()) {
                if(CheckCollisionRecs(iter -> getRect(), alien.getRect())){
                    iter = obstacle.blocks.erase(iter);                                    
                }
                else {
                    ++iter;
                }
            }
        }
        // check if alien hit the spaceship
        if(CheckCollisionRecs(alien.getRect(), spaceship.getRect())){
            std::cout << "Spaceship hit by Alien" << std::endl;
            StopMusicStream(music);
            GameOver();
            PlaySound(gameOverSound);
        }
    }

}

void Game::GameOver()
{
    std::cout << "Game over" << std::endl;
    run = false;
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens(); 
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = GetTime();
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    lives = 3;
    score = 0;
    //highscore = 0;
    //if (highscore<=0) highscore = 0;
    highscore = loadHighscoreFromFile();
    run = true;
    PlayMusicStream(music);
}

void Game::checkForHighScore()
{
    if(score>highscore) highscore = score;
    saveHighScoreToFile(highscore);
}

void Game::saveHighScoreToFile(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()){
        highscoreFile << highscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}

int Game::loadHighscoreFromFile(){
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()){
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to load highscore from file" << std::endl;
    }
    return loadedHighscore;
}

void Game::ResetGame(){
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
    mysteryship.Reset();
}
