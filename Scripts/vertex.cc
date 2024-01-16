#include "vertex.h"

Vertex::Vertex(Colour colour, int r, int c): 
    colour{colour}, row{r}, column{c}, piece{nullptr} {}

Colour Vertex::getColour() const {
    return colour;
}

int Vertex::getRow() const {
    return row;
}

int Vertex::getColumn() const {
    return column;
}

std::shared_ptr<Piece> Vertex::setPiece(std::shared_ptr<Piece> newPiece) {
    std::shared_ptr<Piece> tmp = piece;
    piece = newPiece;
    notify();
    return tmp;
}

std::shared_ptr<Piece> Vertex::getPiece() const {
    return piece;
}

void Vertex::notify() {
    for (auto o : observers)
        o->update(*this);
}
