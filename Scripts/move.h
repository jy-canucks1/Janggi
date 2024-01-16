#ifndef __MOVE_H__
#define __MOVE_H__
#include "piece.h"
#include <memory>
#include <map>

struct Move {
    // shared_ptr that points to the moved piece (if castling occured, 
    //  movedPiece would point to the castled King)
    std::shared_ptr<Piece> movedPiece;

    // pair that represents the row and column of the Square to which
    //  the moved piece was before the move (if castling occured, startPos
    //  represents the row and column of the Square to which the castled King
    //  was before the castle)
    std::pair<int, int> startPos;

    // pair that represents the row and column of the Square to which
    //  the moved piece was after the move (if castling occured, startPos
    //  represents the row and column of the Square to which the castled King
    //  was after the castle)
    std::pair<int, int> endPos;

    // shared_ptr that points to the captured piece if there is one, otherwise
    //  capturedPiece is nullptr
    std::shared_ptr<Piece> capturedPiece;

    // default constructor for Move, all shared_ptr fields are initialized to
    //  nullptr and all pairs are initialized to (-1, -1)
    Move();

    // constructor for Move
    Move(std::shared_ptr<Piece> movedPiece, 
        const std::pair<int, int> &startPos, 
        const std::pair<int, int> &endPos,
        std::shared_ptr<Piece> capturedPiece = nullptr);
};

std::ostream &operator<<(std::ostream &out, const Move &move);

#endif
