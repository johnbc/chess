/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * board.h
 * Copyright (C) 2015 jbc <john.bc@gmail.com>
 *
 */

#include <sched.h>

#include <array>
#include "pieces.h"

#ifndef _BOARD_H_
#define _BOARD_H_

class Board {
public:
    Board();

    void Reset();

    void SetInitialByFEN(const char *fen);

    void Print();

    Piece GetPieceAt(char rank, char file);

    Piece GetPieceAtIndex(char boardIndex);

    std::array<Piece, 16> &GetPieces() { return m_White; }

    void SetPieceAtIndex(Piece &piece, signed char index);


private:
    void Clear();

    std::array<Piece, 16> m_White;
    std::array<Piece, 16> m_Black;

};

#endif // _BOARD_H_
