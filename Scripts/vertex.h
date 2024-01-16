#ifndef __VERTEX_H__
#define __VERTEX_H__
#include "subject.h"
#include "piece.h"

class Vertex final: public Subject {
    Colour colour;
    int row, column;
    std::shared_ptr<Piece> piece;
public:
    Vertex(Colour colour, int r, int c);
    ~Vertex() = default;
    Colour getColour() const;
    int getRow() const;
    int getColumn() const;
    
    // returns a shared_ptr to the piece replaced, if no piece exists, 
    //  returns a null shared_ptr
    std::shared_ptr<Piece> setPiece(std::shared_ptr<Piece> newPiece);

    // returns a shared_ptr to the piece on this Vertex, if no piece exists,
    //  returns a null shared_ptr
    std::shared_ptr<Piece> getPiece() const;

    virtual void notify() override;
};

#endif
