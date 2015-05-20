//
// Created by jbc on 20/05/15.
//

#include "movelogic.h"

MoveLogic::MoveLogic(const Piece::Colour colourToMove, const Board &board, Evaluation *evaluation,
                     ChessLogic *chessLogic) :
        m_MoveColour(colourToMove),
        m_Board(&board),
        m_Evaluation(evaluation),
        m_ChessLogic(chessLogic) {

}

int NegaMaxLogic::NegaMaxRecursive(Piece::Colour colour, int depth, const Board &board) {

    if (depth == 0) {
        return m_Evaluation->Evaluate(board, m_MoveColour);
    }

    int max = -100000;
    std::vector<ChessLogic::Move> moves;
    m_ChessLogic->GenerateMovesForBoard(colour, board, moves);
    for (ChessLogic::Move &m: moves) {
        int score = -NegaMaxRecursive(colour == Piece::White ? Piece::Black : Piece::White, depth - 1, board);
        if (score > max) {
            max = score;
        }
    }
    return max;
}

ChessLogic::Move NegaMaxLogic::GetAMove(const int searchDepth) {

    int max = -100000;
    ChessLogic::Move returnMove;
    std::vector<ChessLogic::Move> moves;
    m_ChessLogic->GenerateMovesForBoard(m_MoveColour, *m_Board, moves);
    for (ChessLogic::Move &m: moves) {
        int score = -NegaMaxRecursive(m_MoveColour, searchDepth, *m_Board);
        if (score > max) {
            max = score;
            returnMove = m;
        }
    }
    return returnMove;
}

NegaMaxLogic::NegaMaxLogic(const Piece::Colour colourToMove, const Board &board, Evaluation *evaluation,
                           ChessLogic *chessLogic) :
        MoveLogic(colourToMove, board, evaluation, chessLogic) {

}