#include "menu.hpp"

Menu::Menu(){
    inMenu = true;
    isPvB = true; 
    playerColor = _WHITE; 
    botDepth1 = 3; 
    botDepth2 = 3;
}

void Menu::run(){
    while (inMenu && !WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int screenW = screenWidth + offsetX;
        
        // Title
        DrawText("CHESS ENGINE", screenW / 2 - MeasureText("CHESS ENGINE", 40) / 2, 80, 40, BLACK);

        // 1. Mode Selection
        DrawText("Select Mode:", screenW / 2 - 200, 180, 20, DARKGRAY);
        if (draw({ (float)screenW / 2 - 200, 220, 180, 50 }, "Player vs Bot", isPvB)) isPvB = true;
        if (draw({ (float)screenW / 2 + 20, 220, 180, 50 }, "Bot vs Bot", !isPvB)) isPvB = false;

        // 2. Dynamic Settings (Changes based on mode)
        if (isPvB) {
            // Player Color Selection
            DrawText("Play As:", screenW / 2 - 200, 320, 20, DARKGRAY);
            if (draw({ (float)screenW / 2 - 200, 360, 180, 50 }, "White", playerColor == _WHITE)) playerColor = _WHITE;
            if (draw({ (float)screenW / 2 + 20, 360, 180, 50 }, "Black", playerColor == _BLACK)) playerColor = _BLACK;

            // Bot Depth Selector
            DrawText("Bot Depth:", screenW / 2 - 200, 460, 20, DARKGRAY);
            if (draw({ (float)screenW / 2 - 200, 500, 50, 50 }, "-", false) && botDepth1 > 1) botDepth1--;
            DrawText(TextFormat("%d", botDepth1), screenW / 2 - 120, 515, 20, BLACK);
            if (draw({ (float)screenW / 2 - 70, 500, 50, 50 }, "+", false) && botDepth1 < 10) botDepth1++;
        } 
        else {
            // Bot vs Bot Settings
            DrawText("White Bot Depth:", screenW / 2 - 200, 320, 20, DARKGRAY);
            if (draw({ (float)screenW / 2 - 200, 360, 50, 50 }, "-", false) && botDepth1 > 1) botDepth1--;
            DrawText(TextFormat("%d", botDepth1), screenW / 2 - 120, 375, 20, BLACK);
            if (draw({ (float)screenW / 2 - 70, 360, 50, 50 }, "+", false) && botDepth1 < 10) botDepth1++;

            DrawText("Black Bot Depth:", screenW / 2 + 20, 320, 20, DARKGRAY);
            if (draw({ (float)screenW / 2 + 20, 360, 50, 50 }, "-", false) && botDepth2 > 1) botDepth2--;
            DrawText(TextFormat("%d", botDepth2), screenW / 2 + 100, 375, 20, BLACK);
            if (draw({ (float)screenW / 2 + 150, 360, 50, 50 }, "+", false) && botDepth2 < 10) botDepth2++;
        }

        // 3. Start Button
        if (draw({ (float)screenW / 2 - 100, 650, 200, 60 }, "START GAME", false)) {
            inMenu = false; // This breaks the loop!
        }

        EndDrawing();
    }
}

bool Menu::draw(Rectangle rec, const char* text, bool selected){
    Color bgColor = selected ? LIGHTGRAY : DARKGRAY;
    DrawRectangleRec(rec, bgColor);
    DrawRectangleLinesEx(rec, 2, BLACK);
        
    int textWidth = MeasureText(text, 20);
    DrawText(text, rec.x + rec.width / 2 - textWidth / 2, rec.y + 15, 20, selected ? BLACK : WHITE);
        
    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && CheckCollisionPointRec(GetMousePosition(), rec);
}
