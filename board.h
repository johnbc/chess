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


typedef signed char BoardIndex;
class Board {
public:
    Board();

    void Reset();

    void SetInitialByFEN(const char *fen);

    void Print() const;

    Piece GetPieceAt(char rank, char file) const;

    Piece GetPieceAtIndex(BoardIndex boardIndex) const;

    const std::array<Piece, 16> &GetPieces(Piece::Colour colour) const {
        return colour == Piece::White ? m_White : m_Black;
    }

    void SetPieceAtIndex(Piece &piece, signed char index);


private:
    void Clear();

    std::array<Piece, 16> m_White;
    std::array<Piece, 16> m_Black;

};

#endif // _BOARD_H_

