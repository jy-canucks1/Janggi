#include "human.h"
#include "rules.h"

HumanPlayer::HumanPlayer(Colour c): Player{c}
{
    vertexMap = {
        {"a9", {0, 0}}, {"b9", {0, 1}}, {"c9", {0, 2}}, {"d9", {0, 3}},
        {"e9", {0, 4}}, {"f9", {0, 5}}, {"g9", {0, 6}}, {"h9", {0, 7}}, {"i9", {0, 8}},

        {"a8", {1, 0}}, {"b8", {1, 1}}, {"c8", {1, 2}}, {"d8", {1, 3}},
        {"e8", {1, 4}}, {"f8", {1, 5}}, {"g8", {1, 6}}, {"h8", {1, 7}}, {"i8", {1, 8}},

        {"a7", {2, 0}}, {"b7", {2, 1}}, {"c7", {2, 2}}, {"d7", {2, 3}},
        {"e7", {2, 4}}, {"f7", {2, 5}}, {"g7", {2, 6}}, {"h7", {2, 7}}, {"i7", {2, 8}},

        {"a6", {3, 0}}, {"b6", {3, 1}}, {"c6", {3, 2}}, {"d6", {3, 3}},
        {"e6", {3, 4}}, {"f6", {3, 5}}, {"g6", {3, 6}}, {"h6", {3, 7}}, {"i6", {3, 8}},

        {"a5", {4, 0}}, {"b5", {4, 1}}, {"c5", {4, 2}}, {"d5", {4, 3}},
        {"e5", {4, 4}}, {"f5", {4, 5}}, {"g5", {4, 6}}, {"h5", {4, 7}}, {"i5", {4, 8}},

        {"a4", {5, 0}}, {"b4", {5, 1}}, {"c4", {5, 2}}, {"d4", {5, 3}},
        {"e4", {5, 4}}, {"f4", {5, 5}}, {"g4", {5, 6}}, {"h4", {5, 7}}, {"i4", {5, 8}},

        {"a3", {6, 0}}, {"b3", {6, 1}}, {"c3", {6, 2}}, {"d3", {6, 3}},
        {"e3", {6, 4}}, {"f3", {6, 5}}, {"g3", {6, 6}}, {"h3", {6, 7}}, {"i3", {6, 8}},

        {"a2", {7, 0}}, {"b2", {7, 1}}, {"c2", {7, 2}}, {"d2", {7, 3}},
        {"e2", {7, 4}}, {"f2", {7, 5}}, {"g2", {7, 6}}, {"h2", {7, 7}}, {"i2", {7, 8}},

        {"a1", {8, 0}}, {"b1", {8, 1}}, {"c1", {8, 2}}, {"d1", {8, 3}},
        {"e1", {8, 4}}, {"f1", {8, 5}}, {"g1", {8, 6}}, {"h1", {8, 7}}, {"i1", {8, 8}},

        {"a0", {9, 0}}, {"b0", {9, 1}}, {"c0", {9, 2}}, {"d0", {9, 3}},
        {"e0", {9, 4}}, {"f0", {9, 5}}, {"g0", {9, 6}}, {"h0", {9, 7}}, {"i0", {9, 8}}
    };
}

Move HumanPlayer::makeMove(const Board &board, const Move &previousMove)
{   
    std::string strStart, strEnd, aux;
    std::cin >> strStart >> strEnd;

    // if the arguments are invalid, return a default constructed Move
    //  to indicate prompt failure
    if (!vertexMap.contains(strStart) || !vertexMap.contains(strEnd)) 
    {
        std::cout << "\nInvalid arguments: " << strStart << " or " 
            << strEnd << std::endl;
        std::getline(std::cin, aux);
        return Move();
    }

    // gets the starting and ending positions of the piece to be moved
    std::pair<int, int> start = vertexMap[strStart];
    std::pair<int, int> end = vertexMap[strEnd];

    // gets the piece to be moved
    auto piece = board.getVertex(start.first, start.second).getPiece();

    // if there is no piece on the vertex with position start or the piece
    //  has a different colour than the player's assigned colour, return a 
    //  default constructed Move to indicate prompt failure
    if (!piece || piece->getColour() != getColour()) 
    {    
        std::cout << "\nNo piece to move or invalid piece to move." << std::endl;
        std::getline(std::cin, aux);
        return Move();
    }

    // generate all legal moves for the piece on the vertex with 
    //  position start
    std::vector<Move> fullyLegalMoves = 
        Rules::generateFullyLegalMoves(start, board, previousMove);
    
    for (auto &move : fullyLegalMoves) {

        // if the ending position of one of the legal moves is the same as
        //  end, return that legal move
        if (move.endPos == end) {
            return move;
        }
    }

    // otherwise the player's move is illegal, return a default constructed
    //  Move to indicate prompt failure
    std::cout << "\nMove is illegal." << std::endl;
    std::getline(std::cin, aux);
    return Move();
}

Move HumanPlayer::makeMoveOnline(const Board &board, const Move &previousMove, const std::string strStart, const std::string strEnd)
{   
    std::string aux;

    // if the arguments are invalid, return a default constructed Move
    //  to indicate prompt failure
    if (!vertexMap.contains(strStart) || !vertexMap.contains(strEnd)) 
    {
        std::cout << "\nInvalid arguments: " << strStart << " or " 
            << strEnd << std::endl;
        std::getline(std::cin, aux);
        return Move();
    }

    // gets the starting and ending positions of the piece to be moved
    std::pair<int, int> start = vertexMap[strStart];
    std::pair<int, int> end = vertexMap[strEnd];

    // gets the piece to be moved
    auto piece = board.getVertex(start.first, start.second).getPiece();

    // if there is no piece on the vertex with position start or the piece
    //  has a different colour than the player's assigned colour, return a 
    //  default constructed Move to indicate prompt failure
    if (!piece || piece->getColour() != getColour()) 
    {    
        std::cout << "\nNo piece to move or invalid piece to move." << std::endl;
        std::getline(std::cin, aux);
        return Move();
    }

    // generate all legal moves for the piece on the vertex with 
    //  position start
    std::vector<Move> fullyLegalMoves = 
        Rules::generateFullyLegalMoves(start, board, previousMove);
    
    for (auto &move : fullyLegalMoves) {

        // if the ending position of one of the legal moves is the same as
        //  end, return that legal move
        if (move.endPos == end) {
            return move;
        }
    }

    // otherwise the player's move is illegal, return a default constructed
    //  Move to indicate prompt failure
    std::cout << "\nMove is illegal." << std::endl;
    std::getline(std::cin, aux);
    return Move();
}