//
// Created by jbc on 13/05/15.
//

#include "Chess.h"


Chess::Chess() {
    m_ChessLogic = new ChessLogic();
}


void Chess::GenerateMove(Piece::Colour colour) {

    ChessLogic::Move aMove = m_ChessLogic->GetBestMove(colour, m_Board);
    m_ChessLogic->ApplyMove(aMove, m_Board);

}


Chess::~Chess() {
    delete m_ChessLogic;
    m_ChessLogic = nullptr;
}

void Chess::DumpBoard() {
    m_Board.Print();
}
