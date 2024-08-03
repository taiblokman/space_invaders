#include "game.hpp"
#include <iostream>

Game::Game(){
    obstacles = CreateObstacles();
    aliens = CreateAliens(); 
    aliensDirection = 1;
};

Game::~Game(){
    Alien::UnloadImages();
}

void Game::Update()
{
    for (auto& laser: spaceship.lasers){
        laser.Update();
    }   

    MoveAliens(); 
    AlienShootLaser();

    for(auto& laser: alienLasers ){
        laser.Update(); 
    }

    DeleteInactiveLasers();
    // std::cout << "Vector size: " << spaceship.lasers.size() << std::endl;
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
}

void Game::HandleInput(){
    if(IsKeyDown(KEY_LEFT)) {
        spaceship.MoveLeft();
    } else if(IsKeyDown(KEY_RIGHT)) {
        spaceship.MoveRight();
    } else if(IsKeyDown(KEY_SPACE)){
        spaceship.FireLaser();
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
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
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
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth()) {
            aliensDirection = -1;
            MoveDownAliens(4);
        } if(alien.position.x < 0) {
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
