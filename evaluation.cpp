//
// Created by jbc on 20/05/15.
//

#include "evaluation.h"


/*static*/ int Evaluation::GetPieceCount(const Piece::Colour colour, const Piece::Type type, const Board &board) {
    int count = 0;
    for (const Piece &p : board.GetPieces(colour)) {
        if (p.GetType() == type && p.IsOnBoard() == true) {
            count++;
        }
    }

    return count;
}


/*static*/ int Evaluation::GetPieceCount(const Piece::Colour colour, const Board &board) {
    int count = 0;
    for (const Piece &p : board.GetPieces(colour)) {
        if (p.IsOnBoard() == true) {
            count++;
        }
    }

    return count;
}


int BasicEvaluation::Evaluate(const Board &board, const Piece::Colour forColour) {

    int materialWeight = 1;
    int numWhitePieces = GetPieceCount(Piece::White, board);
    int numBlackPieces = GetPieceCount(Piece::Black, board);
    int score = materialWeight * (numWhitePieces - numBlackPieces) * (forColour == Piece::White ? 1 : -1);

    return score;
}
