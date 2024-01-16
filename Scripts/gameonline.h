#ifndef __GAMEONLINE_H__
#define __GAMEONLINE_H__
#include "human.h"
#include "rules.h"
#include <stack>

class Gameonline {
    Board board;

    // unique_ptr to the first player
    std::unique_ptr<Player> player1;

    // unique_ptr to the second player
    std::unique_ptr<Player> player2;

    // keeps track of the score for green player
    double greenScore;

    // keeps track of the score for red player
    double redScore;

    // keeps track of the moves made throughout the game
    std::stack<Move> moveHistory;

    // returns the previous move made
    Move getPreviousMove() const;
public:
    explicit Gameonline(int sizeR = 10, int sizeC = 9);

    // starts the command interpreter for the chess program
    void start();
};

#endif
