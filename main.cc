/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2015 jbc <john.bc@gmail.com>
 * 
 * chess is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * chess is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include "chess.h"

int main() {
    std::cout << "Hello chess!" << std::endl;

    Chess chess;

    for (int i = 0; i < 20; i++) {
        chess.GenerateMove(Piece::White);
        chess.DumpBoard();
        chess.GenerateMove(Piece::Black);
        chess.DumpBoard();


    }

    return 0;
}

