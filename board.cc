/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * board.cc
 * Copyright (C) 2015 jbc <john.bc@gmail.com>
 *
 */

#include "board.h"

#include <iostream>

Board::Board() {
    Reset();
}

void Board::Reset() {
    Clear();
    SetInitialByFEN("rnbq/1/bnr/pppppppp/8/7/k/8/7/K/PPPPPPPP/RNB/1/QBNR");
    Print();
}

void Board::Clear() {
    int i = 0;
    for (Piece::Type t : Piece::s_PieceMap) {
        m_White[i].SetIndexColourType(127, Piece::White, t);
        m_Black[i].SetIndexColourType(127, Piece::Black, t);
        i++;;
    }

}

void Board::SetInitialByFEN(const char *fen) {
    char boardIndex = 0;
    while (*fen != '\0') {
        if (*fen >= '1' && *fen <= '8') {
            for (int i = 0; i < *fen - '0'; i++) {
                boardIndex++;
            }
        }
        else if (*fen != '/') {
            Piece::Type t = Piece::GetTypeFromText(*fen);

            if (*fen > 'Z') {
                char pieceIndex = Piece::GetPieceIndexForType(t, m_White);
                if (pieceIndex != 127) {
                    m_White[pieceIndex].SetIndexColourType(boardIndex, Piece::White, t);
                }
            }
            else {
                char pieceIndex = Piece::GetPieceIndexForType(t, m_Black);
                if (pieceIndex != 127) {
                    m_Black[pieceIndex].SetIndexColourType(boardIndex, Piece::Black, t);
                }
            }
            boardIndex++;

        }
        fen++;
    }
}


Piece Board::GetPieceAt(char rank, char file) {
    char boardIndex = (rank - 1) * 8 + file - 'A';
    return GetPieceAtIndex(boardIndex);
}

Piece Board::GetPieceAtIndex(char boardIndex) {
    for (Piece &piece : m_White) {
        if (piece.GetBoardIndex() == boardIndex) {
            return piece;
        }
    }

    for (Piece &piece : m_Black) {
        if (piece.GetBoardIndex() == boardIndex) {
            return piece;
        }
    }

    Piece none;

    return none;
}


void Board::Print() {
    char rank = 8;
    for (; rank >= 1; rank--) {
        std::cout << char('0' + rank) << " ";
        char file = 'A';
        for (; file <= 'H'; file++) {
            Piece p = GetPieceAt(rank, file);
            std::cout << p.GetText();
        }
        std::cout << std::endl;
    }
    std::cout << "  ABCDEFGH" << std::endl;
}

void Board::SetPieceAtIndex(Piece &piece, signed char index) {
    if (piece.GetColour() == Piece::White) {
        for (Piece &p :m_White) {
            if (p.GetBoardIndex() == piece.GetBoardIndex()) {
                p.SetBoardIndex(index);
            }
        }

        for (Piece &p :m_Black) {
            if (p.GetBoardIndex() == index) {
                p.SetBoardIndex(127);
            }
        }


    }
}
