#include "gameManager.hpp"
#include "menu.hpp"

int main(){
    InitWindow(screenWidth + offsetX, screenWidth, "Chess Engine");
    InitAudioDevice();
    SetTargetFPS(60);

    ChangeDirectory(TextFormat("%s../Resources", GetApplicationDirectory()));

    Menu menu; menu.run();

    GameManager gameManager;
    if (menu.pVb()){
        gameManager.pvb(menu.getPlayerColor(), menu.getDepth1());
    }
    else{
        gameManager.bVb(menu.getDepth1(), menu.getDepth2(), 10);
    }
    
    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}