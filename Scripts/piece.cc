#include "piece.h"

Piece::Piece(Colour c, PieceType pt): colour{c}, type{pt} {}

Colour Piece::getColour() const {
    return colour;
}

PieceType Piece::getType() const {
    return type;
}

void Piece::firstMove() {
    hasMoved = true;
}

bool Piece::isMoved() const {
    return hasMoved;
}

General::General(Colour c): Piece{c, PieceType::General} {}

char General::getSymbol() const {
    return getColour() == Colour::Green ? 'G' : 'g';
}

std::string General::getUnicodeSymbol() const {
    return getColour() == Colour::Green ? "\u265a" : "\u2654";
}

Guard::Guard(Colour c): Piece{c, PieceType::Guard} {}

char Guard::getSymbol() const {
    return getColour() == Colour::Green ? 'U' : 'u';
}

std::string Guard::getUnicodeSymbol() const {
    return getColour() == Colour::Green ? "\u265b" : "\u2655";
}

Horse::Horse(Colour c): Piece{c, PieceType::Horse} {}

char Horse::getSymbol() const {
    return getColour() == Colour::Green ? 'H' : 'h';
}

std::string Horse::getUnicodeSymbol() const {
    return getColour() == Colour::Green ? "\u265d" : "\u2657";
}

Chariot::Chariot(Colour c): Piece{c, PieceType::Chariot} {}

char Chariot::getSymbol() const {
    return getColour() == Colour::Green ? 'C' : 'c';
}

std::string Chariot::getUnicodeSymbol() const {
    return getColour() == Colour::Green ? "\u265c" : "\u2656";
}

Cannon::Cannon(Colour c): Piece{c, PieceType::Cannon} {}

char Cannon::getSymbol() const {
    return getColour() == Colour::Green ? 'A' : 'a';
}

std::string Cannon::getUnicodeSymbol() const {
    return getColour() == Colour::Green ? "\u265e" : "\u2658";
}

Elephant::Elephant(Colour c): Piece{c, PieceType::Elephant} {}

char Elephant::getSymbol() const {
    return getColour() == Colour::Green ? 'E' : 'e';
}

std::string Elephant::getUnicodeSymbol() const {
    return getColour() == Colour::Green ? "\u265f" : "\u2659";
}

Soldier::Soldier(Colour c): Piece{c, PieceType::Soldier} {}

char Soldier::getSymbol() const {
    return getColour() == Colour::Green ? 'S' : 's';
}

std::string Soldier::getUnicodeSymbol() const {
    return getColour() == Colour::Green ? "\u265f" : "\u2659";
}

std::shared_ptr<Piece> generatePiece(Colour c, PieceType type) {
    if (type == PieceType::General)
        return std::make_shared<General>(c);

    else if (type == PieceType::Guard)
        return std::make_shared<Guard>(c);

    else if (type == PieceType::Horse)
        return std::make_shared<Horse>(c);

    else if (type == PieceType::Chariot)
        return std::make_shared<Chariot>(c);

    else if (type == PieceType::Cannon)
        return std::make_shared<Cannon>(c);

    else if (type == PieceType::Elephant)
        return std::make_shared<Elephant>(c);
           
    else
        return std::make_shared<Soldier>(c);
}
