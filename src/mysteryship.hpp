#pragma once
#include <raylib.h>

class MysteryShip{
    public:
        MysteryShip();
        ~MysteryShip();
        void Update();
        void Draw();
        void Spawn();
        Rectangle getRect();
        void Reset();
        bool alive;
        Sound mysteryshipMoveSound;
    private:
        Vector2 position;
        Texture2D image;
        int speed;
};