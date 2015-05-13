//
// Created by jbc on 13/05/15.
//

#ifndef CHESS_CHESSLOGIC_H
#define CHESS_CHESSLOGIC_H

#include<vector>

#include "pieces.h"
#include "board.h"

class ChessLogic {
public:

    ChessLogic();

    struct Move {
        int m_ply;
        Piece m_Piece;
        char m_From;
        char m_To;
    };

    void GenerateMoves(Piece &piece, Board &board, std::vector<Move> &out_moves);

    void GenerateMovesPawn(Piece &piece, Board &board, std::vector<Move> &out_moves);

    void ApplyMove(Move &move, Board &board);

    void GenerateMoveRook(Piece &piece, Board &board, std::vector<Move> &out_moves);

    void GenerateMoveBishop(Piece &piece, Board &board, std::vector<Move> &out_moves);

    void GenerateMoveKnight(Piece &piece, Board &board, std::vector<Move> &out_moves);

    void GenerateMoveKing(Piece &piece, Board &board, std::vector<Move> &out_moves);
};


#endif //CHESS_CHESSLOGIC_H