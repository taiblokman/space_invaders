#include "mysteryship.hpp"

float lastMysteryShipSoundTime = 0.0;

MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
    mysteryshipMoveSound = LoadSound("Sounds/ufo_lowpitch.wav");
}

MysteryShip::~MysteryShip(){
    UnloadTexture(image);
    StopSound(mysteryshipMoveSound);
    UnloadSound(mysteryshipMoveSound);
}

void MysteryShip::Spawn(){
    position.y = 90;
    // spawn either left or right
    int side = GetRandomValue(0,1);

    if(side == 0) {
        position.x = 0 - image.width;
        speed = 3;
    } else {
        position.x = GetScreenWidth();
        speed = -3;
    }
    alive = true;
}

Rectangle MysteryShip::getRect()
{
    if(alive) {
        return {position.x, position.y, float(image.width), float(image.height)};
    } else {
        return {position.x, position.y, 0, 0};
    }
}

void MysteryShip::Reset()
{
    alive = false;
}

void MysteryShip::Update(){
    if(alive){
        if (GetTime() - lastMysteryShipSoundTime >= 0.8){        
            PlaySound(mysteryshipMoveSound);
            lastMysteryShipSoundTime = GetTime();
            //std::cout << "play alien sound" << std::endl;
        }           
        position.x += speed;
        if (position.x > GetScreenWidth()|| position.x + image.width < 0) {
            alive = false;
            StopSound(mysteryshipMoveSound);
        }
    }
}

void MysteryShip::Draw(){
    if(alive){
        DrawTextureV(image, position, WHITE);
    }
}