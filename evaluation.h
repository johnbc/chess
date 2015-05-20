//
// Created by jbc on 20/05/15.
//

#ifndef CHESS_EVALUATION_H
#define CHESS_EVALUATION_H


#include "pieces.h"
#include "board.h"

class Evaluation {
public:
    virtual int Evaluate(const Board &board, const Piece::Colour forColour) = 0;

    static int GetMaterialScore(const Piece::Colour, const Board &board);

    static int GetPieceCount(const Piece::Colour colour, const Board &board);

    static int GetPieceCount(const Piece::Colour colour, const Piece::Type type, const Board &board);
};

class BasicEvaluation : public Evaluation {

public:
    virtual int Evaluate(const Board &board, const Piece::Colour forColour) override;
};


#endif //CHESS_EVALUATION_H
