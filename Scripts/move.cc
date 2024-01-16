#include "move.h"

Move::Move(): movedPiece{nullptr}, startPos{-1, -1}, endPos{-1, -1},
    capturedPiece{nullptr} {}

Move::Move(std::shared_ptr<Piece> movedPiece, 
    const std::pair<int, int> &startPos, 
    const std::pair<int, int> &endPos,
    std::shared_ptr<Piece> capturedPiece): movedPiece{movedPiece}, startPos{startPos}, endPos{endPos}, capturedPiece{capturedPiece} {}

std::ostream &operator<<(std::ostream &out, const Move &move) {
    std::map<PieceType, std::string> pieceTypeMap{
        {PieceType::General, "General"}, {PieceType::Guard, "Guard"},
        {PieceType::Horse, "Horse"}, {PieceType::Chariot, "Chariot"},
        {PieceType::Cannon, "Cannon"}, {PieceType::Elephant, "Elephant"} , {PieceType::Soldier, "Soldier"}
    };
    
    std::map<Colour, std::string> colourMap{
        {Colour::Green, "Green"}, {Colour::Red, "Red"}
    };

    std::map<int, std::string> posRowMap{
        {0, "9"}, {1, "8"}, {2, "7"}, {3, "6"}, {4, "5"}, {5, "4"}, {6, "3"}, {7, "2"}, {8, "1"}, {9, "0"}
    };

    std::map<int, std::string> posColMap{
        {0, "a"}, {1, "b"}, {2, "c"}, {3, "d"}, {4, "e"}, {5, "f"}, {6, "g"}, {7, "h"}, {8, "i"}
    };

    if (move.movedPiece) {
        out << "Moved Piece: " << colourMap[move.movedPiece->getColour()] << " "
            << pieceTypeMap[move.movedPiece->getType()] << std::endl;
    }
    if (move.startPos.first != -1 && move.startPos.second != -1) {
        out << "Moved Piece start: " << posColMap[move.startPos.second]
            << posRowMap[move.startPos.first] << std::endl;
    }
    if (move.endPos.first != -1 && move.endPos.second != -1) {
        out << "Moved Piece end: " << posColMap[move.endPos.second]
            << posRowMap[move.endPos.first] << std::endl;
    }
    if (move.capturedPiece) {
        out << "Captured Piece: " << colourMap[move.capturedPiece->getColour()] << " "
            << pieceTypeMap[move.capturedPiece->getType()] << std::endl;
    }
    
    return out;
}
