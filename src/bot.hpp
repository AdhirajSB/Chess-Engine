#pragma once
#include "piece.hpp"
#include "raylib.h"
#include <utility>
#include <random>

int evaluateBoard(piece* board[8][8]);
int minimax(int depth, int alpha, int beta, bool isMaximizingPlayer, piece* board[8][8], const std::vector<piece>& pieces);
std::pair<std::pair<int, int>, std::pair<int, int>> getRandomMove(int type, piece* board[8][8], const std::vector<piece>& pieces);
std::pair<std::pair<int, int>, std::pair<int, int>> getSmartMove(int depth, int type, piece* board[8][8], const std::vector<piece>& pieces);

void drawEvalBar(int currScore, int barWidth, int totalHeight, int padding);