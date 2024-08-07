#include "spaceship.hpp"

int speed = 7;
int gameWindowOffset = 25;
int gameWindowOffsetBottom = 100;

Spaceship::Spaceship(){
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 7 - gameWindowOffsetBottom;
    lastFireTime = 0.0;
}

Spaceship::~Spaceship(){
    UnloadTexture(image);
}

void Spaceship::Draw(){
    DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft(){
    position.x -= speed;
    if (position.x < gameWindowOffset) {
        position.x = gameWindowOffset;
    }
}

void Spaceship::MoveRight(){
    position.x += speed;
    if (position.x > GetScreenWidth() - image.width - gameWindowOffset) {
        position.x = GetScreenWidth() - image.width - gameWindowOffset;
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

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width)/2.0f;
    position.y = (GetScreenHeight() - image.height - gameWindowOffsetBottom);
    lasers.clear();
}
