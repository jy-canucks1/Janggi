#ifndef __BOARD_H__
#define __BOARD_H__
#include "vertex.h"
#include "boarddisplay.h"
#include <set>

class Board {
    int boardSizeR;
    int boardSizeC;
    std::vector<std::vector<Vertex>> board;
    std::shared_ptr<BoardDisplay> display;
    bool winstate = False;
    // set of pairs which represent the position (row, column) 
    //  of all Green pieces on the board
    std::set<std::pair<int, int>> greenPieces;

    // set of pairs which represent the position (row, column) 
    //  of all Red pieces on the board
    std::set<std::pair<int, int>> redPieces;

    // the position of the Green General on the board if there is one,
    //  otherwise the position is (-1, -1)
    std::pair<int, int> greenGeneralPos;

    // the position of the Red General on the board if there is one,
    //  otherwise the position is (-1, -1)
    std::pair<int, int> redGeneralPos;

    // inserts the pair (row, col) which represents the position of a piece
    //  with Colour c into one of the sets
    void insertToPieces(int row, int col, Colour c);

    // erases the pair (row, col) which represents the position of a piece
    //  with Colour c from one of the sets
    void eraseFromPieces(int row, int col, Colour c);
public:
    // initializes the board with squares that have no pieces
    explicit Board(int sizeR, int sizeC);

    // copy constructor used only for the code of Rules::generateLegalMoves,
    //  detaches all BoardDisplay observers to the Squares of the copy Board
    Board(const Board &other);

    // returns the board size
    int getSizeR() const;
    int getSizeC() const;

    // returns a reference to the Square with position (row, col)
    const Vertex &getVertex(int row, int col) const;

    // places all needed pieces for a default chess game 
    void initBoard(int x = 0);

    // places newPiece on the square with position (row, col) on the board
    //  (unless there is no piece on the square with position (row, col),
    //  always call removePiece before calling placePiece!)
    void placePiece(int row, int col, std::shared_ptr<Piece> newPiece);

    // removes a piece from the board, returns a shared_ptr to the piece 
    //  that was removed, otherwise returns a null shared_ptr
    std::shared_ptr<Piece> removePiece(int row, int col);

    // returns a reference to GreenPieces
    const std::set<std::pair<int, int>> &getGreenPieces() const;

    // returns a reference to RedPieces
    const std::set<std::pair<int, int>> &getRedPieces() const;

    // returns a reference to GreenGeneralPos
    const std::pair<int, int> &getGreenGeneralPos() const;

    // returns a reference to RedGeneralPos
    const std::pair<int, int> &getRedGeneralPos() const;

    // forwards the output of the board from BoardDisplay
    friend std::ostream &operator<<(std::ostream &out, Board &b);

    bool setGameResult(bool state);

    bool getGameResult() const;

};

#endif
