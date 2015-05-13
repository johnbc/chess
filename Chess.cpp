//
// Created by jbc on 13/05/15.
//

#include <ostream>
#include <iostream>
#include "Chess.h"


Chess::Chess() {
    m_ChessLogic = new ChessLogic();
}


void Chess::GenerateMoves() {
    std::vector<ChessLogic::Move> moves;
    for (Piece &p : m_Board.GetPieces()) {
        m_ChessLogic->GenerateMoves(p, m_Board, moves);
    }

    std::vector<Board> boardMoves;
    for (ChessLogic::Move &m : moves) {
        boardMoves.push_back(m_Board);
        m_ChessLogic->ApplyMove(m, boardMoves.back());
    }

    for (Board &b : boardMoves) {
        std::cout << std::endl;
        b.Print();
    }
}


Chess::~Chess() {
    delete m_ChessLogic;
    m_ChessLogic = nullptr;
}
