//
// Created by jbc on 20/05/15.
//

#ifndef CHESS_MOVELOGIC_H
#define CHESS_MOVELOGIC_H


#include "chesslogic.h"
#include "evaluation.h"

class MoveLogic {
public:
    MoveLogic(const Piece::Colour colourToMove, const Board &board, Evaluation *evaluation, ChessLogic *chessLogic);

    virtual ChessLogic::Move GetAMove(const int searchDepth) = 0;

private:

    MoveLogic() { }

protected:
    Evaluation *m_Evaluation;
    const Board *m_Board;
    Piece::Colour m_MoveColour;
    ChessLogic *m_ChessLogic;
};

class NegaMaxLogic : public MoveLogic {
public:
    NegaMaxLogic(const Piece::Colour colourToMove, const Board &board, Evaluation *evaluation, ChessLogic *chessLogic);

    virtual ChessLogic::Move GetAMove(const int searchDepth) override;

private:
    int NegaMaxRecursive(Piece::Colour colour, int depth, const Board &board);
};


#endif //CHESS_MOVELOGIC_H
