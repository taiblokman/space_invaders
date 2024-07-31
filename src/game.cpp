#include "game.hpp"
#include <iostream>

Game::Game(){
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
