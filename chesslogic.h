//
// Created by jbc on 13/05/15.
//

#ifndef CHESS_CHESSLOGIC_H
#define CHESS_CHESSLOGIC_H

#include<vector>

#include "pieces.h"
#include "board.h"
#include "evaluation.h"

class ChessLogic {
public:

    ChessLogic();

    struct Move {
        int m_ply;
        Piece m_Piece;
        char m_From;
        char m_To;
        Board m_Board;
        int m_Score;
    };

    void GenerateMoves(const Piece &piece, const Board &board, std::vector<Move> &out_moves);

    void GenerateMovesPawn(const Piece &piece, const Board &board, std::vector<Move> &out_moves);

    void GenerateMoveRook(const Piece &piece, const Board &board, std::vector<Move> &out_moves);

    void GenerateMoveBishop(const Piece &piece, const Board &board, std::vector<Move> &out_moves);

    void GenerateMoveKnight(const Piece &piece, const Board &board, std::vector<Move> &out_moves);

    void GenerateMoveKing(const Piece &piece, const Board &board, std::vector<Move> &out_moves);

    void ApplyMove(Move &move, Board &board);


    Move GetBestMove(Piece::Colour colour, const Board &board, Evaluation *eval);

    void GenerateMovesForBoard(Piece::Colour colour, const Board &board, std::vector<Move> &out_moves);


};


#endif //CHESS_CHESSLOGIC_H
