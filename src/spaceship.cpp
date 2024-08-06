#include "spaceship.hpp"

#define MOVE_DELTA 7

Spaceship::Spaceship(){
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 7;
    lastFireTime = 0.0;
}

Spaceship::~Spaceship(){
    UnloadTexture(image);
}

void Spaceship::Draw(){
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft(){
    position.x -= 7;
    if (position.x < 0) {
        position.x = 0;
    }
}

void Spaceship::MoveRight(){
    position.x += 7;
    if (position.x > GetScreenWidth() - image.width) {
        position.x = GetScreenWidth() - image.width;
    }
}

void Spaceship::FireLaser()
{
    if (GetTime() - lastFireTime >= 0.35){
        lasers.push_back(Laser({position.x + image.width/2 -2, position.y},-6));
        lastFireTime = GetTime();
    }
}

Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}
