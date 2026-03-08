#include "piece.hpp"

bool piece::underThreat(int type, piece* board[8][8]) const{
    piece* king = nullptr;
    for (int rank = 0; rank < 8; rank++){
        for (int file = 0; file < 8; file++){
            if (board[rank][file] != nullptr && board[rank][file]->type == type && board[rank][file]->id == KING){
                king = board[rank][file];
                break;
            }
        }
    }
    assert(king != nullptr);
    
    // I need to scan the board if this move puts the king under threat or not
    for (int rank = 0; rank < 8; rank++){
        for (int file = 0; file < 8; file++){
            if (board[rank][file] == nullptr) continue;
            if (board[rank][file]->type == type) continue;

            piece* attacker = board[rank][file];

            // Look for a threat
            if (attacker->id == KING){
                int dirX[3] = {-1, 0, 1};
                int dirY[3] = {-1, 0, 1};

                for (int i = 0; i < 3; i++){
                    for (int j = 0; j < 3; j++){
                        if (king->rank == attacker->rank + dirX[i] && king->file == attacker->file + dirY[j]){
                            return true;
                        }
                    }
                }
            }
            else if (attacker->id == QUEEN){
                for (int i = rank - 1; i >= 0; i--){
                    if (board[i][file] != nullptr){
                        if (board[i][file] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }
                for (int i = rank + 1; i < 8; i++){
                    if (board[i][file] != nullptr){
                        if (board[i][file] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }

                for (int i = file - 1; i >= 0; i--){
                    if (board[rank][i] != nullptr){
                        if (board[rank][i] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }
                for (int i = file + 1; i < 8; i++){
                    if (board[rank][i] != nullptr){
                        if (board[rank][i] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }

                int i = rank, j = file;
                while (i + 1 < 8 && j + 1 < 8){
                    i++, j++;
                    if (board[i][j] != nullptr){
                        if (board[i][j] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }

                i = rank, j = file;
                while (i - 1 >= 0 && j - 1 >= 0){
                    i--, j--;
                    if (board[i][j] != nullptr){
                        if (board[i][j] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }

                i = rank, j = file;
                while (i - 1 >= 0 && j + 1 < 8){
                    i--, j++;
                    if (board[i][j] != nullptr){
                        if (board[i][j] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }

                i = rank, j = file;
                while (i + 1 < 8 && j - 1 >= 0){
                    i++, j--;
                    if (board[i][j] != nullptr){
                        if (board[i][j] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }
            }
            else if (attacker->id == BISHOP){
                int i = rank, j = file;
                while (i + 1 < 8 && j + 1 < 8){
                    i++, j++;
                    if (board[i][j] != nullptr){
                        if (board[i][j] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }

                i = rank, j = file;
                while (i - 1 >= 0 && j - 1 >= 0){
                    i--, j--;
                    if (board[i][j] != nullptr){
                        if (board[i][j] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }

                i = rank, j = file;
                while (i - 1 >= 0 && j + 1 < 8){
                    i--, j++;
                    if (board[i][j] != nullptr){
                        if (board[i][j] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }

                i = rank, j = file;
                while (i + 1 < 8 && j - 1 >= 0){
                    i++, j--;
                    if (board[i][j] != nullptr){
                        if (board[i][j] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }
            }
            else if (attacker->id == KNIGHT){
                if (abs(rank - king->rank) == 2 && abs(file - king->file) == 1) return true;
                if (abs(rank - king->rank) == 1 && abs(file - king->file) == 2) return true;
            }
            else if (attacker->id == ROOK){
                for (int i = rank - 1; i >= 0; i--){
                    if (board[i][file] != nullptr){
                        if (board[i][file] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }
                for (int i = rank + 1; i < 8; i++){
                    if (board[i][file] != nullptr){
                        if (board[i][file] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }

                for (int i = file - 1; i >= 0; i--){
                    if (board[rank][i] != nullptr){
                        if (board[rank][i] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }
                for (int i = file + 1; i < 8; i++){
                    if (board[rank][i] != nullptr){
                        if (board[rank][i] == king){
                            return true;
                        }
                        else{
                            break;
                        }
                    }
                }
            }
            else if (attacker->id == PAWN){
                int dir = (attacker->type == _WHITE ? -1 : 1);
                if (king->rank == attacker->rank + dir && abs(king->file - attacker->file) == 1){
                    return true;
                }
            }
            else {
                assert(false);
            }
        }
    }
    return false;
}

std::vector<Move> piece::getAllMoves(int rank, int file, piece *board[8][8]) const{
    std::vector<Move> moves;
    piece* guard = board[rank][file];

    if (guard->id == QUEEN || guard->id == BISHOP || guard->id == ROOK){
        std::vector<std::pair<int, int>> dir;

        if (guard->id == ROOK || guard->id == QUEEN){
            dir.emplace_back(-1, 0);
            dir.emplace_back(1, 0);
            dir.emplace_back(0, -1);
            dir.emplace_back(0, 1);
        }

        if (guard->id == BISHOP || guard->id == QUEEN){
            dir.emplace_back(1, 1);
            dir.emplace_back(-1, -1);
            dir.emplace_back(1, -1);
            dir.emplace_back(-1, 1);
        }

        for (auto [x, y]: dir){
            int r = rank + x;
            int c = file + y;

            while (r >= 0 && r < 8 && c >= 0 && c < 8){
                if (board[r][c] != nullptr){
                    if (board[r][c]->type != guard->type){
                        moves.emplace_back(r, c);
                    }
                    break;
                }

                moves.emplace_back(r, c);
                r += x;
                c += y;
            }
        }
    }
    else if (guard->id == KNIGHT){
        int dr[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
        int dc[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
        
        for (int i = 0; i < 8; i++) {
            int r = rank + dr[i];
            int c = file + dc[i];
            
            if (r >= 0 && r < 8 && c >= 0 && c < 8) {
                if (board[r][c] == nullptr || board[r][c]->type != guard->type) {
                    moves.emplace_back(r, c);
                }
            }
        }
    }
    else if (guard->id == KING){
        int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        
        for (int i = 0; i < 8; i++) {
            int r = rank + dr[i];
            int c = file + dc[i];
            
            if (r >= 0 && r < 8 && c >= 0 && c < 8) {
                if (board[r][c] == nullptr || board[r][c]->type != guard->type) {
                    moves.emplace_back(r, c);
                }
            }
        }
    }
    else if (guard->id == PAWN) {
        int dir = (guard->type == _WHITE) ? -1 : 1;

        int forwardRank = rank + dir;
        if (forwardRank >= 0 && forwardRank < 8) {
            if (board[forwardRank][file] == nullptr) {
                moves.emplace_back(forwardRank, file);

                int doubleRank = rank + 2 * dir;
                if (guard->firstMove && doubleRank >= 0 && doubleRank < 8) {
                    if (board[doubleRank][file] == nullptr) {
                        moves.emplace_back(doubleRank, file);
                    }
                }
            }

            for (int dFile : {-1, 1}) {
                int diagFile = file + dFile;
                if (diagFile >= 0 && diagFile < 8) {
                    if (board[forwardRank][diagFile] != nullptr) {
                        if (board[forwardRank][diagFile]->type != guard->type) {
                            moves.emplace_back(forwardRank, diagFile);
                        }
                    } 
                    else {
                        piece* adjacent = board[rank][diagFile];
                        if (adjacent != nullptr && 
                            adjacent->id == PAWN && 
                            adjacent->type != guard->type && 
                            adjacent->doubleStepped) {
                            moves.emplace_back(forwardRank, diagFile);
                        }
                    }
                }
            }
        }
    }

    return moves;
}

bool piece::checkMate(int type, piece *board[8][8]) const{
    if (!underThreat(type, board)) return false;

    // now i have to simulate all possible moves and see if check can be blocked
    for (int rank = 0; rank < 8; rank++){
        for (int file = 0; file < 8; file++){
            if (board[rank][file] == nullptr || board[rank][file]->type != type) continue;

            piece* guard = board[rank][file];
            std::vector<Move> moves = getAllMoves(rank, file, board);

            for (Move m: moves){
                piece* captured = board[m.toRank][m.toFile];
                int origRank = guard->rank;
                int origFile = guard->file;

                board[rank][file] = nullptr;
                board[m.toRank][m.toFile] = guard;
                guard->rank = m.toRank;
                guard->file = m.toFile;

                bool mate = underThreat(type, board);

                guard->rank = origRank;
                guard->file = origFile;
                board[m.toRank][m.toFile] = captured;
                board[rank][file] = guard;

                if (!mate) return false;
            }
        }
    }
    return true;
}

bool piece::staleMate(int type, piece *board[8][8]) const{
    if (underThreat(type, board)) return false;

    for (int rank = 0; rank < 8; rank++){
        for (int file = 0; file < 8; file++){
            if (board[rank][file] == nullptr || board[rank][file]->type != type) continue;

            piece* guard = board[rank][file];
            std::vector<Move> moves = getAllMoves(rank, file, board);

            for (Move m : moves) {
                piece* captured = board[m.toRank][m.toFile];

                int origRank = guard->rank;
                int origFile = guard->file;

                board[rank][file] = nullptr;
                board[m.toRank][m.toFile] = guard;
                guard->rank = m.toRank;
                guard->file = m.toFile;

                bool isSafe = !underThreat(type, board);

                guard->rank = origRank;
                guard->file = origFile;
                board[m.toRank][m.toFile] = captured;
                board[rank][file] = guard;

                if (isSafe) return false; 
            }
        }
    }
    return true;
}

piece::piece(int id, int type, int rank, int file, Texture2D &texture)
{
    this->id = id;
    this->type = type;
    this->rank = rank;
    this->file = file;
    this->texture = texture;
    alive = true;
    selected = false;
    firstMove = true;
    doubleStepped = false;
}

bool piece::move(int newRank, int newFile, piece *board[8][8]){
    if (board[newRank][newFile] != nullptr && board[newRank][newFile]->type == type) return false;
    if (rank == newRank && file == newFile) return false;

    if (id == KING){
        if (abs(file - newFile) == 1 && abs(rank - newRank) == 1){
            // Valid
        }
        else if (abs(file - newFile) == 1 && rank == newRank){
            // Valid
        }
        else if (abs(rank - newRank) == 1 && file == newFile){
            // Valid
        }
        else if (abs(file - newFile) == 2 && rank == newRank){
            if (!firstMove) return false; // Cannot castle if king has moved
            if (underThreat(type, board)) return false; // Cannot castle under check

            int rookFile = (newFile > file ? 7 : 0);
            piece* rook = board[rank][rookFile];

            // Check if that piece is a same colored rook that has not moved
            if (rook == nullptr || rook->id != ROOK || rook->type != type || !rook->firstMove){
                return false;
            }

            int dir = (newFile > file ? 1 : -1);
            for (int f = file + dir; f != rookFile; f+= dir){
                if (board[rank][f] != nullptr) return false;
            }

            int origFile = file;
            board[rank][file] = nullptr;

            file += dir;
            board[rank][file] = this;

            bool threat = underThreat(type, board);

            board[rank][file] = nullptr;
            file = origFile;
            board[rank][file] = this;

            // King cannot land under check after the castle
            if (threat) return false;

        }
        else return false;
    }
    else if (id == QUEEN){
        if (rank == newRank){
            int dir = (newFile > file ? 1 : -1);
            for (int f = file + dir; f != newFile; f+= dir){
                if (board[rank][f] != nullptr) return false;
            }
            // Valid
        }
        else if (file == newFile){
            int dir = (newRank > rank ? 1 : -1);
            for (int r = rank + dir; r != newRank; r+= dir){
                if (board[r][file] != nullptr) return false;
            }
            // Valid
        }
        else if (abs(rank - newRank) == abs(file - newFile)){
            int dirX = (newRank > rank ? 1 : -1);
            int dirY = (newFile > file ? 1 : -1);

            int currRank = rank + dirX;
            int currFile = file + dirY;
            while (currRank != newRank && currFile != newFile){
                if (board[currRank][currFile] != nullptr) return false;
                currRank += dirX;
                currFile += dirY;
            }
            // Valid
        }
        else return false;
    }
    else if (id == BISHOP){
        if (abs(rank - newRank) != abs(file - newFile)) return false;

        int dirX = (newRank > rank ? 1 : -1);
        int dirY = (newFile > file ? 1 : -1);

        int currRank = rank + dirX;
        int currFile = file + dirY;
        while (currRank != newRank && currFile != newFile){
            if (board[currRank][currFile] != nullptr) return false;
            currRank += dirX;
            currFile += dirY;
        }
        // Valid
    }
    else if (id == KNIGHT){
        if (abs(rank - newRank) == 2 && abs(file - newFile) == 1){
            // Valid
        }
        else if (abs(rank - newRank) == 1 && abs(file - newFile) == 2){
            // Valid
        }
        else return false;
    }
    else if (id == ROOK){
        if (rank == newRank){
            int dir = (newFile > file ? 1 : -1);
            for (int f = file + dir; f != newFile; f+= dir){
                if (board[rank][f] != nullptr) return false;
            }
            // Valid
        }
        else if (file == newFile){
            int dir = (newRank > rank ? 1 : -1);
            for (int r = rank + dir; r != newRank; r+= dir){
                if (board[r][file] != nullptr) return false;
            }
            // Valid
        }
        else return false;
    }
    else if (id == PAWN){
        int dir = (type == _WHITE ? -1 : 1);

        if (newFile == file){
            if (board[newRank][newFile] != nullptr) return false;
            if (firstMove){
                if (rank + dir == newRank){
                    // Valid
                }
                else if (rank + 2*dir == newRank){
                    if (board[rank + dir][file] != nullptr) return false;
                    if (board[newRank][newFile] != nullptr) return false;
                    // Valid
                    doubleStepped = true;
                }
                else return false;
            }
            else{
                if (rank + dir != newRank) return false;
                // Valid
            }
        }
        else if (rank + dir == newRank && abs(file - newFile) == 1){
            if (board[newRank][newFile] != nullptr){
                // Valid
            } 
            else{
                piece* adjacent = board[rank][newFile];
                if (adjacent != nullptr &&
                    adjacent->id == PAWN &&
                    adjacent->type != type &&
                    adjacent->doubleStepped == true){
                    // Valid En-Passant
                }
                else return false;
            }
            // Valid
        }
        else{
            return false;
        }
    }
    else{
        assert(false);
        return false;
    }

    piece* taken = board[newRank][newFile];
    piece* orig = board[rank][file];
    int origRank = rank;
    int origFile = file;

    bool isEnPassant = (id == PAWN && newFile != origFile && board[newRank][newFile] == nullptr);
    piece* epPawn = nullptr;
    if (isEnPassant){
        epPawn = board[origRank][newFile];
    }

    bool isCastling = (id == KING && abs(file - newFile) == 2 && rank == newRank);
    piece* rookToMove = nullptr;
    int oldRookFile = -1;
    int newRookFile = -1;

    if (isCastling){
        oldRookFile = (newFile > file ? 7 : 0);
        newRookFile = (newFile > file ? newFile - 1 : newFile + 1);
        rookToMove = board[origRank][oldRookFile];

        board[origRank][oldRookFile] = nullptr;
        board[origRank][newRookFile] = rookToMove;
        rookToMove->file = newRookFile;
    }

    if (board[newRank][newFile] != nullptr){
        board[newRank][newFile]->alive = false;
    }
    else if (isEnPassant){
        epPawn->alive = false;
        board[origRank][newFile] = nullptr;
    }

    board[rank][file] = nullptr;

    rank = newRank;
    file = newFile;
    board[rank][file] = this;

    if (underThreat(type, board)){
        rank = origRank;
        file = origFile;
        board[rank][file] = orig;
        board[newRank][newFile] = taken;

        if (taken != nullptr){
            taken->alive = true;
        }

        if (isCastling){
            board[origRank][newRookFile] = nullptr;
            board[origRank][oldRookFile] = rookToMove;
            rookToMove->file = oldRookFile;
        }

        if (isEnPassant){
            board[origRank][newFile] = epPawn;
            epPawn->alive = true;
        }
        return false;
    }

    firstMove = false;
    doubleStepped = (id == PAWN && abs(origRank - newRank) == 2);
    if (isCastling) rookToMove->firstMove = false;

    return true;
}

void piece::draw(int offsetX) const{
    if (!alive) return;

    int X = file * squareSize + offsetX;
    int Y = rank * squareSize;

    if (selected){
        DrawRectangle(X, Y, squareSize, squareSize, ColorAlpha(YELLOW, 0.5f));
    }
    
    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Rectangle dest = {(float)X, (float)Y, (float)squareSize, (float)squareSize};
    Vector2 origin = {0.0f, 0.0f};

    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}