#pragma once
#include "constants.hpp"
#include "piece.hpp"
#include "bot.hpp"
#include "raylib.h"
#include <vector>

class GameManager{
private:
    std::vector<piece> m_pieces;
    piece* board[8][8];

    Texture2D m_wKing, m_wQueen, m_wBishop, m_wKnight, m_wRook, m_wPawn;
    Texture2D m_bKing, m_bQueen, m_bBishop, m_bKnight, m_bRook, m_bPawn;

    Sound m_Move, m_InvalidMove;

    bool whiteTurn, gameOver, isDraw, isCheck;
    int winningColor;

public:
    GameManager();
    ~GameManager();
    
    void initBoard();
    void bVb(int depthWhite, int depthBlack, int playSpeed);
    void pvp();
    void pvb(int playerColor, int botDepth);
    void draw();
};