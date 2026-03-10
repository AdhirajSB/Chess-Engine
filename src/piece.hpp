#pragma once
#include "raylib.h"
#include "constants.hpp"
#include <cassert>
#include <cstdlib>
#include <vector>

enum PieceID { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN };
enum PieceType { _WHITE, _BLACK };

struct Move {
    int toRank;
    int toFile;

    Move(int r, int c) : toRank(r), toFile(c) {}
};

class piece {
public:
    int id, type;
    int rank, file;
    Texture2D texture;
    bool alive, selected;
    bool firstMove, doubleStepped;

    piece(int id, int type, int rank, int file, Texture2D& texture);
    std::vector<Move> getAllMoves(int rank, int file, piece* board[8][8]) const;
    bool move(int newRank, int newFile, piece* board[8][8]);
    bool underThreat(int type, piece* board[8][8]) const;
    bool checkMate(int type, piece* board[8][8]) const;
    bool staleMate(int type, piece* board[8][8]) const;
    bool isDraw(piece* board[8][8]) const;
    void draw(int offsetX) const;
};