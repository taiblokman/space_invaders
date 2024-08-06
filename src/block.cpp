#include "block.hpp"

int block_height = 3;
int block_width = 3;

Block::Block(Vector2 position)
{
    this -> position = position;
}

void Block::Draw()
{
    DrawRectangle(position.x, position.y, block_width, block_height, {243, 216, 63, 255});
}

Rectangle Block::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = block_width;
    rect.height = block_height;
    return rect;
}
