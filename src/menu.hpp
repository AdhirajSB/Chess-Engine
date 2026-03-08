#pragma once
#include "raylib.h"
#include "constants.hpp"
#include "piece.hpp"

class Menu{
private:
    bool inMenu;
    bool isPvB;
    int playerColor;
    int botDepth1, botDepth2;

    bool draw(Rectangle rec, const char* text, bool selected);
public:
    Menu();
    void run();

    inline int getPlayerColor(){
        return playerColor;
    }

    inline int getDepth1(){
        return botDepth1;
    }

    inline int getDepth2(){
        return botDepth2;
    }

    inline bool pVb(){
        return isPvB;
    }
};