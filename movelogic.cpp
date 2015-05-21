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


NegaMaxLogic::NegaMaxLogic(const Piece::Colour colourToMove, const Board &board, Evaluation *evaluation,
                           ChessLogic *chessLogic) :
        MoveLogic(colourToMove, board, evaluation, chessLogic) {

}

int NegaMaxLogic::NegaMaxRecursive(Piece::Colour colour, int depth, const Board &board) {

    if (depth == 0) {
        // board.Print();
        return m_Evaluation->Evaluate(board, /*m_MoveColour*/ colour);

    }

    int max = -100000;
    std::vector<ChessLogic::Move> moves;
    m_ChessLogic->GenerateMovesForBoard(colour, board, moves);
    for (ChessLogic::Move &m: moves) {
        int score = -NegaMaxRecursive(colour == Piece::White ? Piece::Black : Piece::White, depth - 1, m.m_Board);
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
        int score = NegaMaxRecursive(m_MoveColour, searchDepth, m.m_Board);
        if (score > max) {
            max = score;
            returnMove = m;
        }
    }
    return returnMove;
}


NegaMaxAlphaBetaLogic::NegaMaxAlphaBetaLogic(const Piece::Colour colourToMove, const Board &board,
                                             Evaluation *evaluation, ChessLogic *chessLogic) :
        MoveLogic(colourToMove, board, evaluation, chessLogic) {

}

ChessLogic::Move NegaMaxAlphaBetaLogic::GetAMove(const int searchDepth) {
    int max = -100000;
    ChessLogic::Move returnMove;
    std::vector<ChessLogic::Move> moves;
    m_ChessLogic->GenerateMovesForBoard(m_MoveColour, *m_Board, moves);
    for (ChessLogic::Move &m: moves) {
        int score = NegaMaxAlphaBetaLogicRecursive(m_MoveColour, searchDepth, m.m_Board, -1000000, 100000);
        if (score > max) {
            max = score;
            returnMove = m;
        }
    }

    return returnMove;
}

int NegaMaxAlphaBetaLogic::NegaMaxAlphaBetaLogicRecursive(Piece::Colour colour, int depth, const Board &board,
                                                          int alpha, int beta) {
    if (depth == 0) {
        // board.Print();
        return m_Evaluation->Evaluate(board, /*m_MoveColour*/ colour);

    }

    int max = -100000;
    std::vector<ChessLogic::Move> moves;
    m_ChessLogic->GenerateMovesForBoard(colour, board, moves);
    for (ChessLogic::Move &m: moves) {
        int score = -NegaMaxAlphaBetaLogicRecursive(colour == Piece::White ? Piece::Black : Piece::White, depth - 1,
                                                    m.m_Board, -beta, -alpha);
        if (score > max) {
            max = score;
        }
        if (alpha > score) {
            alpha = score;
        }
        if (alpha >= beta) {
            break;
        }
    }
    return max;
}
