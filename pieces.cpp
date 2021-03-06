/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * pieces.cc
 * Copyright (C) 2015 jbc <john.bc@gmail.com>
 *
 */

#include "pieces.h"


Piece::Type Piece::s_PieceMap[16]{Piece::Pawn, Piece::Pawn, Piece::Pawn, Piece::Pawn, Piece::Pawn, Piece::Pawn,
                                  Piece::Pawn, Piece::Pawn, Piece::Rook,
                                  Piece::Knight, Piece::Bishop, Piece::King, Piece::Queen, Piece::Bishop, Piece::Knight,
                                  Piece::Rook};


/*static*/ Piece::Type Piece::GetTypeFromText(char p) {

    if (p < 'Z' && p > 'A') {
        p += 32;
    }

    if (p == 'p') {
        return Pawn;
    }
    else if (p == 'r') {
        return Rook;
    }
    else if (p == 'b') {
        return Bishop;
    }
    else if (p == 'n') {
        return Knight;
    }
    else if (p == 'k') {
        return King;
    }
    else if (p == 'q') {
        return Queen;
    }
    else {
        return None;
    }
}

/*static*/ char Piece::GetPieceIndexForType(Type t, std::array<Piece, 16> &pieces) {
    char pieceIndex = 0;
    for (Type tm : s_PieceMap) {
        if (t == tm && pieces[pieceIndex].GetBoardIndex() == 127) {
            return pieceIndex;
        }
        pieceIndex++;
    }
    return 127;
}

Piece::Piece() {
    m_Type = None;
    m_Colour = White;
    m_BoardIndex = 127;
}

void Piece::Set(char index, char p) {
    m_BoardIndex = index;
    if (p < 'Z' && p > 'A') {
        m_Colour = Black;
        p += 32;
    }
    else {
        m_Colour = White;
    }

    m_Type = GetTypeFromText(p);

}


std::string Piece::GetText() {
    std::string p = ".";
    if (m_Colour == White) {
        switch (m_Type) {
            case Pawn:
                p = "♙";
                break;
            case King:
                p = "♔";
                break;
            case Queen:
                p = "♕";
                break;
            case Rook:
                p = "♖";
                break;
            case Knight:
                p = "♘";
                break;
            case Bishop:
                p = "♗";
                break;
            default:
                break;
        }
    }
    else {
    switch (m_Type) {
        case Pawn:
            p = "♟";
            break;
        case King:
            p = "♚";
            break;
        case Queen:
            p = "♛";
            break;
        case Rook:
            p = "♜";
            break;
        case Knight:
            p = "♞";
            break;
        case Bishop:
            p = "♝";
            break;
        default:
            break;

    }
    }

    return p;
}
