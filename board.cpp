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
    SetInitialByFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBKQBNR");
    // SetInitialByFEN("5/r/2/q/7/8/8/4/n/B/2/p/1/k/1/N/3/P/7/3/K/4");
    SetInitialByFEN("8/8/8/4/p/p/2/");
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


Piece Board::GetPieceAt(char rank, char file) const {
    BoardIndex boardIndex = (rank - 1) * 8 + file - 'A';
    return GetPieceAtIndex(boardIndex);
}

Piece Board::GetPieceAtIndex(signed char boardIndex) const {
    for (const Piece &piece : m_White) {
        if (piece.GetBoardIndex() == boardIndex) {
            return piece;
        }
    }

    for (const Piece &piece : m_Black) {
        if (piece.GetBoardIndex() == boardIndex) {
            return piece;
        }
    }

    Piece none;

    return none;
}


void Board::Print() const {
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

    if (piece.GetColour() == Piece::Black) {
        for (Piece &p :m_Black) {
            if (p.GetBoardIndex() == piece.GetBoardIndex()) {
                p.SetBoardIndex(index);
            }
        }

        for (Piece &p :m_White) {
            if (p.GetBoardIndex() == index) {
                p.SetBoardIndex(127);
            }
        }
    }
}
