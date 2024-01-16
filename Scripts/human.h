#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "player.h"

class HumanPlayer final: public Player {
    std::map<std::string, std::pair<int, int>> vertexMap;
public:
    explicit HumanPlayer(Colour c);

    // returns a Move by prompting the human player
    virtual Move
        makeMove(const Board &board, const Move &previousMove) override;
    
    // returns a Move by prompting the human player
    virtual Move 
        makeMoveOnline(const Board &board, const Move &previousMove, const std::string strStart, const std::string strEnd);
};

#endif
