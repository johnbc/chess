//
// Created by jbc on 13/05/15.
//

#include <iostream>
#include "Chess.h"


Chess::Chess() {
    m_ChessLogic = new ChessLogic();
}


void Chess::GenerateMove(Piece::Colour colour) {

    ChessLogic::Move aMove = m_ChessLogic->GetBestMove(colour, m_Board);
    m_ChessLogic->ApplyMove(aMove, m_Board);
    m_LastMove = aMove;

}


Chess::~Chess() {
    delete m_ChessLogic;
    m_ChessLogic = nullptr;
}

void Chess::DumpBoard() {
    std::cout << std::endl;
    std::cout << (m_LastMove.m_Piece.GetColour() == Piece::White ? "White " : "Black ") <<
    m_LastMove.m_Piece.GetText() << " From " << m_LastMove.m_From << " To " << m_LastMove.m_To << std::endl;
    m_Board.Print();


}
