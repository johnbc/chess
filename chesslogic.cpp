//
// Created by jbc on 13/05/15.
//

#include <assert.h>
#include "chesslogic.h"


ChessLogic::ChessLogic() {

}

ChessLogic::Move ChessLogic::GetBestMove(Piece::Colour colour, Board &board) {
    Move bestMove;
    std::vector<ChessLogic::Move> moves;
    for (Piece &p : board.GetPieces(colour)) {
        assert(p.GetColour() == colour);
        assert(p.GetType() != Piece::None);

        GenerateMoves(p, board, moves);
    }

    assert(moves.size() > 0);
    int i = 0;
    int sign = colour == Piece::White ? 1 : -1;
    bestMove.m_Score = -10000;
    for (ChessLogic::Move &m : moves) {
        assert(m.m_Piece.GetColour() == colour && m.m_Piece.GetType() != Piece::None);
        m.m_Board = board;
        ApplyMove(m, m.m_Board);
        m.m_Score = ScoreBoard(m.m_Board) * sign;
        if (m.m_Score > bestMove.m_Score) {
            bestMove = m;
            i++;
        }
    }

    assert(i > 0);
    assert(bestMove.m_Piece.GetColour() == colour);

    return bestMove;
}


void ChessLogic::GenerateMoves(Piece &piece, Board &board, std::vector<Move> &out_moves) {
    switch (piece.GetType()) {
        case Piece::Pawn:
            GenerateMovesPawn(piece, board, out_moves);
            break;
        case Piece::Rook:
            GenerateMoveRook(piece, board, out_moves);
            break;
        case Piece::Bishop:
            GenerateMoveBishop(piece, board, out_moves);
            break;
        case Piece::Knight:
            GenerateMoveKnight(piece, board, out_moves);
            break;
        case Piece::King:
            GenerateMoveKing(piece, board, out_moves);
            break;
        case Piece::Queen:
            GenerateMoveBishop(piece, board, out_moves);
            GenerateMoveRook(piece, board, out_moves);
            break;
        case Piece::None:
            break;
        default:
            break;

    }
}


void ChessLogic::ApplyMove(ChessLogic::Move &move, Board &board) {
    board.SetPieceAtIndex(move.m_Piece, move.m_To);
}


void ChessLogic::GenerateMovesPawn(Piece &piece, Board &board, std::vector<ChessLogic::Move> &out_moves) {
    // pawn move logic

    signed char sign = piece.GetColour() == Piece::White ? 1 : -1;

    signed char destBoardIndex = piece.GetBoardIndex() + 8 * sign;

    if (destBoardIndex < 0 || destBoardIndex > 63) {
        return;
    }
    Move move;
    move.m_From = piece.GetBoardIndex();
    move.m_Piece = piece;

    Piece destPiece = board.GetPieceAtIndex(destBoardIndex);
    if (destPiece.GetType() == Piece::None) {

        move.m_To = destBoardIndex;

        out_moves.push_back(move);
        if (piece.GetRank() == 2) {
            destBoardIndex += 8 * sign;
            destPiece = board.GetPieceAtIndex(destBoardIndex);
            if (destPiece.GetType() == Piece::None) {
                move.m_To = destBoardIndex;
                out_moves.push_back(move);
            }
        }
    }

    // captures
    destBoardIndex = move.m_From + 7 * sign;

    destPiece = board.GetPieceAtIndex(destBoardIndex);
    if (destPiece.GetType() != Piece::None && destPiece.GetColour() != piece.GetColour()) {
        move.m_To = destBoardIndex;
        out_moves.push_back(move);
    }

    destBoardIndex = move.m_From + 9 * sign;
    destPiece = board.GetPieceAtIndex(destBoardIndex);
    if (destPiece.GetType() != Piece::None && destPiece.GetColour() != piece.GetColour()) {
        move.m_To = destBoardIndex;
        out_moves.push_back(move);
    }
}

void ChessLogic::GenerateMoveRook(Piece &piece, Board &board, std::vector<ChessLogic::Move> &out_moves) {

    // rook move logic
    signed char rank = piece.GetRank();
    signed char rank_range_index_max = rank * 8 - 1;
    signed char rank_range_index_min = (rank - 1) * 8;

    Move move;
    move.m_From = piece.GetBoardIndex();
    move.m_Piece = piece;

    signed char mvr[4] = {8, -8, 1, -1};
    for (signed char m :mvr) {
        signed char destBoardIndex = piece.GetBoardIndex() + m;
        while (true) {
            if (destBoardIndex < 0 || destBoardIndex > 63) {
                break;
            }

            if (m == 1 || m == -1) {
                if (destBoardIndex < rank_range_index_min || destBoardIndex > rank_range_index_max) {
                    break;
                }
            }

            Piece destPiece = board.GetPieceAtIndex(destBoardIndex);
            if (destPiece.GetType() == Piece::None) {
                move.m_To = destBoardIndex;
                out_moves.push_back(move);
            }
            else if (destPiece.GetType() != Piece::None) {
                if (piece.GetColour() != destPiece.GetColour()) {  // Capture
                    move.m_To = destBoardIndex;
                    out_moves.push_back(move);
                }

                // we're done in this direction
                break;
            }

            destBoardIndex += m;

        }
    }


}

void ChessLogic::GenerateMoveBishop(Piece &piece, Board &board, std::vector<ChessLogic::Move> &out_moves) {
    // rook move logic

    signed char rank = piece.GetRank();
    signed char rank_range_index_max = rank * 8 - 1;
    signed char rank_range_index_min = (rank - 1) * 8;

    Move move;
    move.m_From = piece.GetBoardIndex();
    move.m_Piece = piece;

    signed char mvr[4] = {9, -9, 7, -7};
    for (signed char m :mvr) {
        signed char destBoardIndex = piece.GetBoardIndex() + m;
        while (true) {
            if (destBoardIndex < 0 || destBoardIndex > 63) {
                break;
            }

            if (m == -9 || m == 7) {
                if ((destBoardIndex + 1) % 8 == 0) {
                    break;
                }
            }

            if (m == 9 || m == -7) {
                if ((destBoardIndex % 8 == 0)) {
                    break;
                }
            }

            Piece destPiece = board.GetPieceAtIndex(destBoardIndex);
            if (destPiece.GetType() == Piece::None) {
                move.m_To = destBoardIndex;
                out_moves.push_back(move);
            }
            else if (destPiece.GetType() != Piece::None) {
                if (piece.GetColour() != destPiece.GetColour()) {  // Capture
                    move.m_To = destBoardIndex;
                    out_moves.push_back(move);
                }

                // we're done in this direction
                break;
            }

            destBoardIndex += m;

        }
    }

}

void ChessLogic::GenerateMoveKnight(Piece &piece, Board &board, std::vector<ChessLogic::Move> &out_moves) {

    signed char rank = piece.GetRank();
    signed char rank_range_index_max = rank * 8 - 1;
    signed char rank_range_index_min = (rank - 1) * 8;
    char file = piece.GetFile();

    Move move;
    move.m_From = piece.GetBoardIndex();
    move.m_Piece = piece;

    signed char mvr[8] = {6, 10, 15, 17, -6, -10, -15, -17};
    for (signed char m :mvr) {
        signed char destBoardIndex = piece.GetBoardIndex() + m;

        if (destBoardIndex < 0 || destBoardIndex > 63) {
            continue;
        }


        Piece destPiece = board.GetPieceAtIndex(destBoardIndex);

        char destFile = 'A' + destBoardIndex % 8;
        if (m == 6 || m == 15 || m == -10 || m == -17) {
            if (destFile > file) {
                continue;
            }
        }
        else {
            if (destFile < file) {
                continue;
            }
        }


        if (destPiece.GetType() == Piece::None) {
            move.m_To = destBoardIndex;
            out_moves.push_back(move);
        }
        else if (destPiece.GetType() != Piece::None) {
            if (piece.GetColour() != destPiece.GetColour()) {  // Capture
                move.m_To = destBoardIndex;
                out_moves.push_back(move);
            }
        }

    }

}

void ChessLogic::GenerateMoveKing(Piece &piece, Board &board, std::vector<ChessLogic::Move> &out_moves) {

    signed char rank = piece.GetRank();
    signed char rank_range_index_max = rank * 8 - 1;
    signed char rank_range_index_min = (rank - 1) * 8;
    char file = piece.GetFile();

    Move move;
    move.m_From = piece.GetBoardIndex();
    move.m_Piece = piece;

    signed char mvr[8] = {1, -1, 8, -8, 7, 9, -7, -9};
    for (signed char m :mvr) {
        signed char destBoardIndex = piece.GetBoardIndex() + m;

        if (destBoardIndex < 0 || destBoardIndex > 63) {
            continue;
        }

        char destFile = 'A' + destBoardIndex % 8;
        if (m == -1 || m == -9 || m == 7) {
            if (destFile > file) {
                continue;
            }
        }
        else if (m == 1 || m == 9 || m == -7) {
            if (destFile < file) {
                continue;
            }
        }


        bool addMove = false;
        Piece destPiece = board.GetPieceAtIndex(destBoardIndex);
        if (destPiece.GetType() == Piece::None) {
            addMove = true;
        }
        else if (destPiece.GetType() != Piece::None) {
            if (piece.GetColour() != destPiece.GetColour()) {  // Capture
                addMove = true;
            }
        }
        if (addMove == true) { // test for op king
            signed char mvr[8] = {1, -1, 8, -8, 7, 9, -7, -9};
            for (signed char m :mvr) {
                signed char adjToDestBoardIndex = destBoardIndex + m;

                if (adjToDestBoardIndex < 0 || adjToDestBoardIndex > 63) {
                    continue;
                }

                char adjDestFile = 'A' + adjToDestBoardIndex % 8;
                if (m == -1 || m == -9 || m == 7) {
                    if (adjDestFile > destFile) {
                        continue;
                    }
                }
                else if (m == 1 || m == 9 || m == -7) {
                    if (adjDestFile < destFile) {
                        continue;
                    }
                }

                Piece adjToDestPiece = board.GetPieceAtIndex(adjToDestBoardIndex);
                if (adjToDestPiece.GetType() == Piece::King && adjToDestPiece.GetColour() != piece.GetColour()) {
                    addMove = false;
                }
            }

        }

        if (addMove == true) {
            move.m_To = destBoardIndex;
            out_moves.push_back(move);
        }


    }

}

int ChessLogic::ScoreBoard(Board &board) {
    int score = 0;
    for (Piece &p : board.GetPieces(Piece::White)) {
        score += p.GetScore();
    }

    for (Piece &p : board.GetPieces(Piece::Black)) {
        score += p.GetScore();
    }
    return score;
}
