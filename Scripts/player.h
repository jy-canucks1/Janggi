#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "board.h"
#include "move.h"

class Player {
    Colour colour;
public:
    explicit Player(Colour c);

    Colour getColour() const;

    virtual Move makeMove(const Board &board, const Move &previousMove) = 0;
    
    virtual Move makeMoveOnline(const Board &board, const Move &previousMove, const std::string strStart, const std::string strEnd) = 0;
    
    virtual ~Player() = default;
};

#endif
