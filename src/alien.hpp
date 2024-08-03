#pragma once
#include <raylib.h>

class Alien {
    public:
        Alien(int type, Vector2 position);
        void Update(int direction);
        void Draw();
        int GetType();
        //Texture2D image;
        static void UnloadImages();
        static Texture2D alienImages[3];
        int type; // different aliens
        Vector2 position;
    private:

};