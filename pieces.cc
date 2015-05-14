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


char Piece::GetText() {
    char p = ' ';
    switch (m_Type) {
        case Pawn:
            p = 'p';
            break;
        case King:
            p = 'k';
            break;
        case Queen:
            p = 'q';
            break;
        case Rook:
            p = 'r';
            break;
        case Knight:
            p = 'n';
            break;
        case Bishop:
            p = 'b';
            break;
        default:
            break;
    }

    if (m_Colour == Black) {
        p -= 32;
    }

    return p;
}

int Piece::GetScore() {
    if (m_BoardIndex == 127) {
        return 0;
    }

    int score = 0;
    switch (m_Type) {
        case None:
            break;
        case Pawn:
            score = 1;
            break;
        case Rook:
            score = 5;
            break;
        case Knight:
            score = 4;
            break;
        case Bishop:
            score = 3;
            break;
        case King:
            score = 10000;
            break;
        case Queen:
            score = 8;
            break;
    }

    if (m_Colour == Black) {
        score *= -1;
    }

    return score;
}
