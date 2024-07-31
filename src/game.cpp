#include "game.hpp"
#include <iostream>

Game::Game(){
    obstacles = CreateObstacles();
};

Game::~Game(){
}

void Game::Update()
{
    for (auto& laser: spaceship.lasers){
        laser.Update();
    }    

    DeleteInactiveLasers();
    // std::cout << "Vector size: " << spaceship.lasers.size() << std::endl;
}

void Game::Draw(){
    spaceship.Draw();
    for (auto& laser: spaceship.lasers){
        laser.Draw();
    }

    for (auto& obstacle: obstacles) {
        obstacle.Draw();
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
