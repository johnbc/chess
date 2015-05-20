/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * pieces.h
 * Copyright (C) 2015 jbc <john.bc@gmail.com>
 *
 */

#include <array>

#ifndef _PIECES_H_
#define _PIECES_H_

class Piece {
public:

    enum Colour {
        Black, White
    };
    enum Type {
        None, Pawn, Rook, Knight, Bishop, King, Queen
    };

    Piece();

    static Type s_PieceMap[16];

    static Type GetTypeFromText(char t);

    static char GetPieceIndexForType(Type t, std::array<Piece, 16> &pieces);

    Colour GetColour() const { return m_Colour; }

    signed char GetBoardIndex() const { return m_BoardIndex; }

    void SetBoardIndex(signed char index) { m_BoardIndex = index; }

    signed char GetRank() const { return static_cast<signed char>((m_BoardIndex / 8) + 1 ); }

    char GetFile() const { return static_cast<char>('A' + m_BoardIndex % 8); }

    void SetIndexColourType(char index, Colour colour,
                            Type type) { m_BoardIndex = index, m_Colour = colour, m_Type = type; }

    void Set(char index, char p);

    void Clear() { m_BoardIndex = 127; }

    bool IsOnBoard() const { return m_BoardIndex != 127; }

    Type GetType() const { return m_Type; }

    char GetText();

private:
    signed char m_BoardIndex;
    Colour m_Colour;
    Type m_Type;

};


#endif // _PIECES_H_

