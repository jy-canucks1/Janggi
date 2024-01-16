#ifndef __PIECE_H__
#define __PIECE_H__
#include "colour.h"
#include <string>
#include <memory>

enum class PieceType { General, Guard, Horse, Elephant, Chariot, Cannon, Soldier};

class Piece {
    Colour colour;
    PieceType type;
    bool hasMoved = false;
public:
    Piece(Colour c, PieceType pt);

    // returns a char representation of the piece
    virtual char getSymbol() const = 0;

    // returns a unicode string representation of the piece
    virtual std::string getUnicodeSymbol() const = 0;

    Colour getColour() const;
    PieceType getType() const;

    // sets hasMoved to true, used to indicate the piece has been moved
    void firstMove();

    // returns hasMoved
    bool isMoved() const;

    virtual ~Piece() = default;
};

class General final: public Piece {
public:
    General(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
};

class Guard final: public Piece {
public:
    Guard(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
};

class Horse final: public Piece {
public:
    Horse(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
};

class Chariot final: public Piece {
public:
    Chariot(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
};

class Cannon final: public Piece {
public:
    Cannon(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
};

class Elephant final: public Piece {
public:
    Elephant(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
};

class Soldier final: public Piece {
public:
    Soldier(Colour c);
    virtual char getSymbol() const override;
    virtual std::string getUnicodeSymbol() const override;
};

// returns a shared_ptr to a newly allocated Piece of specified Colour c
//  and PieceType type
std::shared_ptr<Piece> generatePiece(Colour c, PieceType type);

#endif
