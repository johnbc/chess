//
// Created by jbc on 13/05/15.
//

#include <iostream>
#include "chess.h"


Chess::Chess() {
    m_ChessLogic = new ChessLogic();
}


void Chess::GenerateMove(Piece::Colour colour) {

    BasicEvaluation evaluation;
    ChessLogic::Move aMove = m_ChessLogic->GetBestMove(colour, m_Board, &evaluation);
    m_ChessLogic->ApplyMove(aMove, m_Board);
    m_LastMove = aMove;

}


Chess::~Chess() {
    delete m_ChessLogic;
    m_ChessLogic = nullptr;
}

void FileRankFromIndex(BoardIndex index, char *fr) {
    fr[0] = 'A' + index % 8;
    fr[1] = '1' + index / 8;
    fr[2] = '\0';
}

void Chess::DumpBoard() {

    char from[3];
    FileRankFromIndex(m_LastMove.m_From, from);
    char to[3];
    FileRankFromIndex(m_LastMove.m_To, to);

    std::cout << std::endl;
    std::cout << (m_LastMove.m_Piece.GetColour() == Piece::White ? "White " : "Black ") <<
            m_LastMove.m_Piece.GetText() << " From " << from << " To " << to << std::endl;
    m_Board.Print();
}
