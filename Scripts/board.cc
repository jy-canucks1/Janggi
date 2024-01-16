#include "board.h"

void Board::insertToPieces(int row, int col, Colour c) {
    if (c == Colour::Green)
        greenPieces.insert({row, col});
    else
        redPieces.insert({row, col});
}

void Board::eraseFromPieces(int row, int col, Colour c) {
    if (c == Colour::Green)
        greenPieces.erase({row, col});
    else
        redPieces.erase({row, col});
}

Board::Board(int sizeR, int sizeC): boardSizeR{sizeR}, boardSizeC{sizeC}, display{new BoardDisplay{sizeR, sizeC}}, 
greenGeneralPos{-1, -1}, redGeneralPos{-1, -1} {
    for (int i = 0; i < boardSizeR; ++i) {
        board.emplace_back(std::vector<Vertex>{});
        for (int j = 0; j < boardSizeC; ++j) {
            Colour c = (i + j) % 2 == 0 ? Colour::Green : Colour::Red;
            board[i].emplace_back(c, i, j);
            board[i][j].attach(display);
        }
    }
}

Board::Board(const Board &other): boardSizeR{other.boardSizeR}, boardSizeC{other.boardSizeC},
    board{other.board}, display{other.display}, greenPieces{other.greenPieces},
    redPieces{other.redPieces}, greenGeneralPos{other.greenGeneralPos},
    redGeneralPos{other.redGeneralPos}
{
    for (int i = 0; i < boardSizeR; ++i) {
        for (int j = 0; j < boardSizeC; ++j)
            board[i][j].detach(display);
    }
}

int Board::getSizeR() const {
    return boardSizeR;
}

int Board::getSizeC() const {
    return boardSizeC;
}

const Vertex& Board::getVertex(int row, int col) const {
    return board[row][col];
}

void Board::initBoard(int x) {
    // initializes all red pieces
    std::vector<std::string> ehsetups;
    std::string s1, s2;
    std::vector<std::vector<int>> ehposition;
    if(x != 1) {
        std::cout << "Elephant and Horse setup (Red first): "<< std::endl;
    std::cin >> s1 >> s2;
    }
    else {
        s1 = "IE";
        s2 = "IE";
    }
    ehsetups.emplace_back(s1);
    ehsetups.emplace_back(s2);
    for(int i = 0; i < 2; ++i){
        if(ehsetups[i] == "OE") {
        std::vector<int> tmp {1,2,7,6};
        tmp.emplace_back();
        ehposition.emplace_back(tmp);
       
        } else if(ehsetups[i] == "RE") {
        std::vector<int> tmp {2,1,7,6};
        tmp.emplace_back();
        ehposition.emplace_back(tmp);
   
        } else if(ehsetups[i] == "LE"){
        std::vector<int> tmp {1,2,6,7};
        tmp.emplace_back();
        ehposition.emplace_back(tmp);
        } else { // default or IE
        std::vector<int> tmp {2,1,6,7};
        tmp.emplace_back();
        ehposition.emplace_back(tmp);
        }
    }

    board[0][0].setPiece(std::make_shared<Chariot>(Colour::Red));
    board[0][ehposition[0][1]].setPiece(std::make_shared<Horse>(Colour::Red));
    board[2][1].setPiece(std::make_shared<Cannon>(Colour::Red));
    board[0][ehposition[0][0]].setPiece(std::make_shared<Elephant>(Colour::Red));
    board[0][3].setPiece(std::make_shared<Guard>(Colour::Red));
    board[1][4].setPiece(std::make_shared<General>(Colour::Red));
    redGeneralPos = {1, 4};
    board[0][5].setPiece(std::make_shared<Guard>(Colour::Red));
    board[0][ehposition[0][2]].setPiece(std::make_shared<Elephant>(Colour::Red));
    board[2][7].setPiece(std::make_shared<Cannon>(Colour::Red));
    board[0][ehposition[0][3]].setPiece(std::make_shared<Horse>(Colour::Red));
    board[0][8].setPiece(std::make_shared<Chariot>(Colour::Red));
    for (int i = 0; i < boardSizeC; ++i) {
        if(board[3][i].getColour() == Colour::Red && i%2 == 0){
        board[3][i].setPiece(std::make_shared<Soldier>(Colour::Red));
        }
        // inserts all positions of red pieces into redPieces
        if(i != 4) insertToPieces(0, i, Colour::Red);
        else insertToPieces(1, i, Colour::Red);
        if(i == 7 || i == 1) insertToPieces(2, i, Colour::Red);
    }

    // initializes all green pieces
    board[9][0].setPiece(std::make_shared<Chariot>(Colour::Green));
    board[9][ehposition[1][1]].setPiece(std::make_shared<Horse>(Colour::Green));
    board[7][1].setPiece(std::make_shared<Cannon>(Colour::Green));
    board[9][ehposition[1][0]].setPiece(std::make_shared<Elephant>(Colour::Green));
    board[9][3].setPiece(std::make_shared<Guard>(Colour::Green));
    board[8][4].setPiece(std::make_shared<General>(Colour::Green));
    greenGeneralPos = {8, 4};
    board[9][5].setPiece(std::make_shared<Guard>(Colour::Green));
    board[9][ehposition[0][2]].setPiece(std::make_shared<Elephant>(Colour::Green));
    board[7][7].setPiece(std::make_shared<Cannon>(Colour::Green));
    board[9][ehposition[0][3]].setPiece(std::make_shared<Horse>(Colour::Green));
    board[9][8].setPiece(std::make_shared<Chariot>(Colour::Green));
    for (int i = 0; i < boardSizeC; ++i) {
        if(board[6][i].getColour() == Colour::Green && i%2 == 0){
        board[6][i].setPiece(std::make_shared<Soldier>(Colour::Green));
        }
        // inserts all positions of green pieces into greenPieces
        if(i != 4) insertToPieces(9, i, Colour::Green);
        else insertToPieces(8, i, Colour::Green);
        if(i == 7 || i == 1) insertToPieces(7, i, Colour::Green);
    }
}

void Board::placePiece(int row, int col, std::shared_ptr<Piece> newPiece) {
    
    // if newPiece is a null shared_ptr, return
    if (!newPiece)
        return;

    // inserts the position of the new piece into one of the sets
    insertToPieces(row, col, newPiece->getColour());

    // if newPiece is a King, update square positions for the King
    if (newPiece->getType() == PieceType::General) {
        if (newPiece->getColour() == Colour::Green)
            greenGeneralPos = {row, col};
        else
            redGeneralPos = {row, col};
    }
    board[row][col].setPiece(newPiece);
}

std::shared_ptr<Piece> Board::removePiece(int row, int col) {
    std::shared_ptr<Piece> piece = board[row][col].getPiece();

    // erases the position if piece is not null
    if (piece) {
        Colour c = piece->getColour();
        eraseFromPieces(row, col, c);

        // if piece is a King, reset the square positions to (-1, -1)
        if (piece->getType() == PieceType::General) {
            if (c == Colour::Green)
                greenGeneralPos = {-1, -1};
            else
                redGeneralPos = {-1, -1};
        }
    }
    return board[row][col].setPiece(std::shared_ptr<Piece>{});
}

const std::set<std::pair<int, int>>& Board::getGreenPieces() const {
    return greenPieces;
}

const std::set<std::pair<int, int>>& Board::getRedPieces() const {
    return redPieces;
}

const std::pair<int, int>& Board::getGreenGeneralPos() const {
    return greenGeneralPos;
}

const std::pair<int, int>& Board::getRedGeneralPos() const {
    return redGeneralPos;
}

std::ostream &operator<<(std::ostream &out, Board &b) {
    out << *b.display;
    return out;
}

bool Board::setGameResult(bool state){
    winstate = state;
 }

bool Board::getGameResult() const {
    return winstate;
}