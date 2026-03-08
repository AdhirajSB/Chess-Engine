#include "bot.hpp"

int evaluateBoard(piece *board[8][8]){
    int score = 0;

    for (int rank = 0; rank < 8; rank++){
        for (int file = 0; file < 8; file++){
            if (board[rank][file] == nullptr || !board[rank][file]->alive) continue;

            int pValue = 0;
            switch (board[rank][file]->id){
                case PAWN: pValue = 1; break;
                case KNIGHT: pValue = 3; break;
                case BISHOP: pValue = 3; break;
                case ROOK: pValue = 5; break;
                case QUEEN: pValue = 9; break;
            }

            if (board[rank][file]->type == _WHITE){
                score += pValue;
            }
            else{
                score -= pValue;
            }
        }
    }

    return score;
}

int minimax(int depth, int alpha, int beta, bool isMaximizingPlayer, piece *board[8][8], const std::vector<piece> &pieces){
    if (depth == 0){
        return evaluateBoard(board);
    }

    int currType = isMaximizingPlayer ? _WHITE : _BLACK;
    int bestEval = isMaximizingPlayer ? -100000 : 100000;
    bool hasLegalMoves = false;

    for (const auto& p: pieces){
        if (p.type != currType || !p.alive) continue;

        int rank = p.rank;
        int file = p.file;
        piece* curr = board[rank][file];

        std::vector<Move> moves = curr->getAllMoves(rank, file, board);
        for (Move m: moves){
            piece* captured = board[m.toRank][m.toFile];

            board[rank][file] = nullptr;
            board[m.toRank][m.toFile] = curr;
            curr->rank = m.toRank;
            curr->file = m.toFile;

            if (captured != nullptr){
                captured->alive = false;
            }

            if (!pieces[0].underThreat(currType, board)){
                hasLegalMoves = true;

                int eval = minimax(depth - 1, alpha, beta, !isMaximizingPlayer, board, pieces);

                if (isMaximizingPlayer){
                    bestEval = std::max(bestEval, eval);
                    alpha = std::max(alpha, eval);
                }
                else{
                    bestEval = std::min(bestEval, eval);
                    beta = std::min(beta, eval);
                }
            }

            if (captured) captured->alive = true;
            curr->rank = rank;
            curr->file = file;
            board[m.toRank][m.toFile] = captured;
            board[rank][file] = curr;

            if (alpha >= beta) break;
        }

        if (alpha >= beta) break;
    }

    if (!hasLegalMoves){
        if (pieces[0].underThreat(currType, board)){
            return isMaximizingPlayer ? -99999 + depth : 99999 - depth;
        }
        else{
            return 0;
        }
    }

    return bestEval;
}

std::pair<std::pair<int, int>, std::pair<int, int>> getRandomMove(int type, piece *board[8][8], const std::vector<piece> &pieces){
    std::random_device rd;
    std::mt19937 gen(rd());

    int startRank, startFile, endRank, endFile;
    while (true){
        std::vector<std::pair<int, int>> validPieces;
        for (const auto& p: pieces){
            if (p.type == type && p.alive){
                validPieces.emplace_back(p.rank, p.file);
            }
        }

        std::uniform_int_distribution<int> dist1(0, (int)validPieces.size() - 1);
        int random1 = dist1(gen);
            
        startRank = validPieces[random1].first;
        startFile = validPieces[random1].second;

        std::vector<Move> validMoves = pieces[0].getAllMoves(startRank, startFile, board);
        if (validMoves.empty()) continue;

        std::uniform_int_distribution<int> dist2(0, (int)validMoves.size() - 1);
        int random2 = dist2(gen);

        endRank = validMoves[random2].toRank;
        endFile = validMoves[random2].toFile;
        break;
    }

    return std::make_pair(std::make_pair(startRank, startFile), std::make_pair(endRank, endFile));
}

std::pair<std::pair<int, int>, std::pair<int, int>> getSmartMove(int depth, int type, piece *board[8][8], const std::vector<piece> &pieces){
    std::pair<std::pair<int, int>, std::pair<int, int>> bestMove = {{-1, -1}, {-1, -1}};

    std::vector<std::pair<int, int>> validPieces;
    for (const auto& p: pieces){
        if (p.type == type && p.alive){
            validPieces.emplace_back(p.rank, p.file);
        }
    }

    // Lets try do do a move that results in the best evaluation for us
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> tiedBestMoves;

    int currBest = (type == _WHITE ? -1000000 : 100000);
    for (auto [rank, file]: validPieces){
        piece* curr = board[rank][file];
        
        std::vector<Move> moves = pieces[0].getAllMoves(rank, file, board);
        for (Move m: moves){
            piece* captured = board[m.toRank][m.toFile];

            int origRank = rank;
            int origFile = file;

            board[rank][file] = nullptr;
            board[m.toRank][m.toFile] = curr;
            curr->rank = m.toRank;
            curr->file = m.toFile;
            
            if (captured != nullptr) captured->alive = false;

            if (!pieces[0].underThreat(type, board)){
                bool nextTurn = type != _WHITE;
                int newScore = minimax(depth - 1, -100000, 100000, nextTurn, board, pieces);

                if (type == _WHITE){
                    if (newScore > currBest){
                        currBest = newScore;
                        tiedBestMoves.clear();

                        tiedBestMoves.push_back({{origRank, origFile}, {m.toRank, m.toFile}});
                    }
                    else if (newScore == currBest){
                        tiedBestMoves.push_back({{origRank, origFile}, {m.toRank, m.toFile}});
                    }
                }
                else{
                    if (newScore < currBest){
                        currBest = newScore;
                        tiedBestMoves.clear();

                        tiedBestMoves.push_back({{origRank, origFile}, {m.toRank, m.toFile}});
                    }
                    else if (newScore == currBest){
                        tiedBestMoves.push_back({{origRank, origFile}, {m.toRank, m.toFile}});
                    }                    
                }
            }

            if (captured != nullptr) captured->alive = true;
            curr->rank = origRank;
            curr->file = origFile;
            board[m.toRank][m.toFile] = captured;
            board[rank][file] = curr;
        }
    }

    if (!tiedBestMoves.empty()){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, (int)tiedBestMoves.size() - 1);
        bestMove = tiedBestMoves[dist(gen)];
    }

    return bestMove;
}

void drawEvalBar(int currentScore, int barWidth, int totalHeight, int padding) {
    float maxEval = 20.0f;
    float fillPercentage = 0.5f + (currentScore / (2.0f * maxEval));

    if (fillPercentage > 1.0f) fillPercentage = 1.0f;
    if (fillPercentage < 0.0f) fillPercentage = 0.0f;

    int whiteHeight = (int)(totalHeight * fillPercentage);
    int blackHeight = totalHeight - whiteHeight;

    DrawRectangle(padding, 0, barWidth, blackHeight, BLACK);
    DrawRectangle(padding, blackHeight, barWidth, whiteHeight, RAYWHITE);
    DrawRectangleLines(padding, 0, barWidth, totalHeight, BLACK);
}
