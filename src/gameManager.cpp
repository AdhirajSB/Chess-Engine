#include "gameManager.hpp"

GameManager::GameManager(){
    m_pieces.reserve(32);
    
    m_wKing = LoadTexture("assets/pieces/WhiteKing.png");
    m_wQueen = LoadTexture("assets/pieces/WhiteQueen.png");
    m_wBishop = LoadTexture("assets/pieces/WhiteBishop.png");
    m_wKnight = LoadTexture("assets/pieces/WhiteKnight.png");
    m_wRook = LoadTexture("assets/pieces/WhiteRook.png");
    m_wPawn = LoadTexture("assets/pieces/WhitePawn.png");

    m_bKing = LoadTexture("assets/pieces/BlackKing.png");
    m_bQueen = LoadTexture("assets/pieces/BlackQueen.png");
    m_bBishop = LoadTexture("assets/pieces/BlackBishop.png");
    m_bKnight = LoadTexture("assets/pieces/BlackKnight.png");
    m_bRook = LoadTexture("assets/pieces/BlackRook.png");
    m_bPawn = LoadTexture("assets/pieces/BlackPawn.png");

    m_Move = LoadSound("assets/sounds/move.wav");
    m_InvalidMove = LoadSound("assets/sounds/invalid.mp3");

    initBoard();

    whiteTurn = true;
    gameOver = false;
    isDraw = false;
    isCheck = false;
    winningColor = -1;
}

GameManager::~GameManager(){
    UnloadTexture(m_wKing);
    UnloadTexture(m_wQueen);
    UnloadTexture(m_wBishop);
    UnloadTexture(m_wKnight);
    UnloadTexture(m_wRook);
    UnloadTexture(m_wPawn);

    UnloadTexture(m_bKing);
    UnloadTexture(m_bQueen);
    UnloadTexture(m_bBishop);
    UnloadTexture(m_bKnight);
    UnloadTexture(m_bRook);
    UnloadTexture(m_bPawn);

    UnloadSound(m_Move);
    UnloadSound(m_InvalidMove);
}

void GameManager::initBoard(){
    m_pieces.clear();

    for (int rank = 0; rank < 8; rank++){
        for (int file = 0; file < 8; file++){
            board[rank][file] = nullptr;
        }
    }

    m_pieces.push_back(piece(KING, 0, 7, 4, m_wKing));
    m_pieces.push_back(piece(QUEEN, 0, 7, 3, m_wQueen));
    m_pieces.push_back(piece(BISHOP, 0, 7, 5, m_wBishop));
    m_pieces.push_back(piece(BISHOP, 0, 7, 2, m_wBishop));
    m_pieces.push_back(piece(KNIGHT, 0, 7, 1, m_wKnight));
    m_pieces.push_back(piece(KNIGHT, 0, 7, 6, m_wKnight));
    m_pieces.push_back(piece(ROOK, 0, 7, 0, m_wRook));
    m_pieces.push_back(piece(ROOK, 0, 7, 7, m_wRook));
    for (int i = 0; i < 8; i++){
        m_pieces.push_back(piece(PAWN, 0, 6, i, m_wPawn));
    }
    
    m_pieces.push_back(piece(KING, 1, 0, 4, m_bKing));
    m_pieces.push_back(piece(QUEEN, 1, 0, 3, m_bQueen));
    m_pieces.push_back(piece(BISHOP, 1, 0, 5, m_bBishop));
    m_pieces.push_back(piece(BISHOP, 1, 0, 2, m_bBishop));
    m_pieces.push_back(piece(KNIGHT, 1, 0, 1, m_bKnight));
    m_pieces.push_back(piece(KNIGHT, 1, 0, 6, m_bKnight));
    m_pieces.push_back(piece(ROOK, 1, 0, 0, m_bRook));
    m_pieces.push_back(piece(ROOK, 1, 0, 7, m_bRook));
    for (int i = 0; i < 8; i++){
        m_pieces.push_back(piece(PAWN, 1, 1, i, m_bPawn));
    }

    for (auto& p: m_pieces){
        board[p.rank][p.file] = &p;
    }
}

void GameManager::bVb(int depthWhite, int depthBlack, int playSpeed){
    int frameCounter = 0;
    while (!WindowShouldClose()){
        if (!gameOver && ++ frameCounter >= playSpeed){
            frameCounter = 0;

            std::pair<std::pair<int, int>, std::pair<int, int>> moveset;
            if (whiteTurn) moveset = getSmartMove(depthWhite, _WHITE, board, m_pieces);
            else moveset = getSmartMove(depthBlack, _BLACK, board, m_pieces);

            auto [start, end] = moveset;

            piece* currPiece = board[start.first][start.second];
            if (currPiece != nullptr && currPiece->move(end.first, end.second, board)){ // Valid Move

                // Auto-Promote to Queen for now
                if (currPiece->id == PAWN && currPiece->type == _WHITE && currPiece->rank == 0){
                    currPiece->id = QUEEN;
                    currPiece->texture = m_wQueen;
                }
                if (currPiece->id == PAWN && currPiece->type == _BLACK && currPiece->rank == 7){
                    currPiece->id = QUEEN;
                    currPiece->texture = m_bQueen;
                }

                // Flip the turns
                whiteTurn = !whiteTurn;
                PlaySound(m_Move);

                // Clear the doubleStepped stat
                for (auto& p: m_pieces){
                    if (whiteTurn && p.type == _WHITE) p.doubleStepped = false;
                    if (!whiteTurn && p.type == _BLACK) p.doubleStepped = false;
                }

                if (whiteTurn && m_pieces[0].checkMate(_WHITE, board)){
                    gameOver = true;
                    winningColor = _BLACK;
                }
                else if (!whiteTurn && m_pieces[0].checkMate(_BLACK, board)){
                    gameOver = true;
                    winningColor = _WHITE;
                }
            }
        }

        draw();

        if (gameOver && IsKeyPressed(KEY_R)){
            initBoard();
            whiteTurn = true;
            gameOver = false;
            isDraw = false;
            isCheck = false;
            winningColor = -1;
        }
    }
}

void GameManager::pvb(int playerColor, int botDepth){
    while (!WindowShouldClose()){
        if (!gameOver){
            bool playerTurn = (playerColor == _WHITE ? whiteTurn : !whiteTurn);

            if (playerTurn){
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    Vector2 mousePos = GetMousePosition();
                    int clickedFile = (int)(mousePos.x - offsetX) / squareSize;
                    int clickedRank = (int)(mousePos.y - offsetY) / squareSize;

                    if (clickedFile < 0 || clickedFile > 7 || clickedRank < 0 || clickedRank > 7) continue;

                    piece* currPiece = nullptr;
                    for (auto& p: m_pieces){
                        if (p.selected){
                            currPiece = &p;
                        }
                    }

                    piece* clickedPiece = board[clickedRank][clickedFile];

                    // We had something already selected
                    if (currPiece != nullptr){
                        if (clickedPiece != nullptr && clickedPiece->type == currPiece->type){
                            // Clicked on same color piece, so just switch the selected piece
                            currPiece->selected = false;
                            clickedPiece->selected = true;
                        }
                        else{
                            // Lets try to move the piece to the desired position
                            if (currPiece->move(clickedRank, clickedFile, board)){
                                // Valid Move

                                // Auto-Promote to Queen for now
                                if (currPiece->id == PAWN && currPiece->rank == (playerColor == _WHITE ? 0 : 7)){
                                    currPiece->id = QUEEN;
                                    currPiece->texture = (playerColor == _WHITE ? m_wQueen : m_bQueen);
                                }

                                // flip the turn
                                whiteTurn = !whiteTurn;
                                PlaySound(m_Move);

                                // Reset the doubleMove status after the opponent made a move
                                for (auto& p: m_pieces){
                                    if (whiteTurn && p.type == _WHITE) p.doubleStepped = false;
                                    if (!whiteTurn && p.type == _BLACK) p.doubleStepped = false;
                                }

                                isCheck = m_pieces[0].underThreat(1 - playerColor, board);
                                isDraw = m_pieces[0].staleMate(1 - playerColor, board);

                                if (m_pieces[0].checkMate(1 - playerColor, board)){
                                    gameOver = true;
                                    winningColor = (whiteTurn ? _BLACK : _WHITE);
                                }
                                else if (isDraw){
                                    gameOver = true;
                                    winningColor = 2;
                                }
                            }
                            else{
                                PlaySound(m_InvalidMove);
                            }

                            currPiece->selected = false;
                        }
                    }
                    else{
                        for (auto& p: m_pieces) p.selected = false;

                        if (clickedPiece != nullptr && clickedPiece->alive && clickedPiece->type == playerColor){
                            clickedPiece->selected = true;
                        }
                    }
                }
            }
            else{
                auto [start, end] = getSmartMove(botDepth, 1 - playerColor, board, m_pieces);

                piece* botPiece = board[start.first][start.second];
                    
                if (botPiece != nullptr && botPiece->move(end.first, end.second, board)) {
                    if (botPiece->id == PAWN && botPiece->rank == (1 - playerColor == _WHITE ? 0 : 7)) {
                        botPiece->id = QUEEN;
                        botPiece->texture = (1 - playerColor == _WHITE ? m_wQueen : m_bQueen);
                    }

                    whiteTurn = !whiteTurn;
                    PlaySound(m_Move);

                    for (auto& p: m_pieces){
                        if (whiteTurn && p.type == _WHITE) p.doubleStepped = false;
                        if (!whiteTurn && p.type == _BLACK) p.doubleStepped = false;
                    }

                    isCheck = m_pieces[0].underThreat(playerColor, board);
                    isDraw = m_pieces[0].staleMate(playerColor, board);

                    if (m_pieces[0].checkMate(playerColor, board)) {
                        gameOver = true;
                        winningColor = (playerColor == _WHITE ? _BLACK : _WHITE);
                    } 
                    else if (isDraw) {
                        gameOver = true;
                        winningColor = 2; // Draw
                    }
                }
            }
        }

        draw();

        if (gameOver && IsKeyPressed(KEY_R)){
            initBoard();
            whiteTurn = true;
            gameOver = false;
            isDraw = false;
            isCheck = false;
            winningColor = -1;
        }
    }
}

void GameManager::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw the Evaluation Bar
    int currScore = evaluateBoard(board);
    drawEvalBar(currScore, barWidth, 8 * squareSize, padding);

    // Draw the Grid
    for (int rank = 0; rank < 8; rank++){
        for (int file = 0; file < 8; file++){
            bool isLightSquare = (rank + file) % 2 == 0;
            Color squareColor = isLightSquare ? Color{238, 238, 210, 255} : Color{118, 150, 86, 255};

            DrawRectangle(file * squareSize + offsetX, rank * squareSize, squareSize, squareSize, squareColor);
        }
    }

    // Draw the Check Indicator
    if (isCheck && !gameOver){
        int currTurnCol = whiteTurn ? 0 : 1;

        for (const auto& p: m_pieces){
            if (p.alive && p.id == KING && p.type == currTurnCol){
                DrawRectangle(p.file * squareSize + offsetX, p.rank * squareSize, squareSize, squareSize, ColorAlpha(RED, 0.6f));
                break;
            }
        }
    }

    // Draw the pieces
    for (const piece& p: m_pieces){
        p.draw(offsetX);
    }

    // Draw the Game-Over Overlay
    if (gameOver){
        DrawRectangle(offsetX, 0, 8 * squareSize, 8 * squareSize, ColorAlpha(BLACK, 0.7f));

        const char* winText = (winningColor == 0 ? "WHITE WINS!" : "BLACK WINS!");
        if (winningColor == _WHITE) winText = "WHITE WINS!";
        else if (winningColor == _BLACK) winText = "BLACK WINS!";
        else if (winningColor == 2) winText = "STALEMATE!";
            
        int fontSize = 40;
        int textWidth = MeasureText(winText, fontSize);

        int textX = (8 * squareSize - textWidth) / 2;
        int textY = (8 * squareSize - textWidth) / 2;

        DrawText(winText, textX + offsetX, textY, fontSize, RED);
        DrawText("Press R to Restart", textX + 30 + offsetX, textY + 50, 20, LIGHTGRAY);
    }

    EndDrawing();
}
