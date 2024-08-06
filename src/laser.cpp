#include "laser.hpp"
#include <iostream>

int laser_height = 15;
int laser_width = 4;

Laser::Laser(Vector2 position, int speed)
{
    this -> position = position;
    this -> speed = speed;
    active = true;
}

void Laser::Draw()
{
    if (active) {
        DrawRectangle(position.x, position.y, laser_width, laser_height, {243, 216, 63, 255 });
    }
    
}
Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = laser_width;
    rect.height = laser_height;
    return rect;
}
void Laser::Update()
{
    position.y += speed;
    if (active) {
        if (position.y > GetScreenHeight() || position.y <0) {
            active = false;
            // std::cout << "Laser Inactive" << std::endl;
        }
    }
}


