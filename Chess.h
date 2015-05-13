//
// Created by jbc on 13/05/15.
//

#ifndef CHESS_CHESS_H
#define CHESS_CHESS_H


#include "pieces.h"
#include "board.h"
#include "chesslogic.h"

class Chess {
private:
    Board m_Board;
    Piece::Colour m_TurnToPlay;
    int m_Ply;
    int m_Turn;

    ChessLogic *m_ChessLogic;
public:
    Chess();

    ~Chess();

    void GenerateMoves();
};


#endif //CHESS_CHESS_H
