#include "rules.h"

bool Rules::isValidPos(int row, int col, const Board &board) 
{
    return 0 <= row && row < board.getSizeR() && 0 <= col && col < board.getSizeC();
}
// counts pieces between two points in the same row
int countHorizontalPieces(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, const Board &board)
{
    int c = 0;

    int row = start.first;
    if(start.second < end.second){
    for(int i = start.second + 1; i < end.second; ++i){
        auto piece1 = board.getVertex(row, i).getPiece();
            if(piece1) {
                c++;
                if(c == 1 && piece1->getType() == PieceType::Cannon) {
                c = 2; 
                break;
                }
            }
        }
    }
    if(start.second > end.second){
    for(int i = start.second - 1; i > end.second; --i){
        auto piece1 = board.getVertex(row, i).getPiece();
            if(piece1) {
                c++;
                if(c == 1 && piece1->getType() == PieceType::Cannon) {
                c = 2; 
                break;
                }
            }
        }
    }
   
    return c;
}
// counts pieces between two points in the same column
int countVerticalPieces(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, const Board &board)
{
    int c = 0;
    int col = start.second;
    if(start.first < end.first){
    for(int i = start.first + 1; i < end.first; ++i){
        auto piece1 = board.getVertex(i, col).getPiece();
            if(piece1) {
                c++;
                if(c == 1 && piece1->getType() == PieceType::Cannon) {
                c = 2; 
                break;
                }
            }
            
        }
    }
    if(start.first > end.first){
    for(int i = start.first - 1; i > end.first; --i){
        auto piece1 = board.getVertex(i, col).getPiece();
            if(piece1) {
                c++;
                if(c == 1 && piece1->getType() == PieceType::Cannon) {
                c = 2; 
                break;
                }
            }
            
        }
    }
 
    return c;
}

bool Rules::addPseudoLegalMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, const Board &board, 
    std::shared_ptr<Piece> &movedPiece, std::vector<Move> &moves)
{
    // if end is a valid vertex position on the board
    if (isValidPos(end.first, end.second, board)) {
        auto capturedPiece = board.getVertex(end.first, end.second).getPiece();

        // if there is no piece on the vertex with position end, adds to Move
        //  and return true
        if (!capturedPiece) {
            moves.emplace_back(movedPiece, start, end);
            return true;
        }

        // if the piece on the vertex with position end has a different colour
        //  than movedPiece, adds to Move and return false
        if (capturedPiece->getColour() != movedPiece->getColour()) {
            moves.emplace_back(movedPiece, start, end, capturedPiece);
            return false;
        }

        // otherwise the the piece on the vertex with position end has the same
        //  colour as movedPiece, so only return false
        return false;
    }
    return false;
}

bool Rules::addPseudoLegalGuardMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, const Board &board, 
    std::shared_ptr<Piece> &movedPiece, std::vector<Move> &moves)
{
    int palacebound1 = movedPiece->getColour() == Colour::Green ? 7 : 0;
    int palacebound2 = movedPiece->getColour() == Colour::Green ? 9 : 2;
    // if end is a valid vertex position on the board
    if (palacebound1 <= end.first && end.first <= palacebound2 
        && end.second >= 3 && end.second <= 5) {
        auto capturedPiece = board.getVertex(end.first, end.second).getPiece();

        // if there is no piece on the vertex with position end, adds to Move
        //  and return true
        if (!capturedPiece) {
            moves.emplace_back(movedPiece, start, end);
            return true;
        }

        // if the piece on the vertex with position end has a different colour
        //  than movedPiece, adds to Move and return false
        if (capturedPiece->getColour() != movedPiece->getColour()) {
            moves.emplace_back(movedPiece, start, end, capturedPiece);
            return false;
        }

        // otherwise the the piece on the vertex with position end has the same
        //  colour as movedPiece, so only return false
        return false;
    }
    return false;
}

bool Rules::addPseudoLegalCannonMove(const std::pair<int, int> &start, 
    const std::pair<int, int> &end, const Board &board, 
    std::shared_ptr<Piece> &movedPiece, std::vector<Move> &moves)
{
    // if end is a valid vertex position on the board
    if (isValidPos(end.first, end.second, board)) {
        if(end.first == start.first && countHorizontalPieces(start,end,board) != 1){
            return false;
        }
        if(end.second == start.second && countVerticalPieces(start,end,board) != 1){
            return false;
        }

        auto capturedPiece = board.getVertex(end.first, end.second).getPiece();

        // if there is no piece on the vertex with position end, adds to Move
        //  and return true
        if (!capturedPiece) {
            moves.emplace_back(movedPiece, start, end);
            return true;
        }

        // if the piece on the vertex with position end has a different colour
        //  than movedPiece, adds to Move and return false
        if (capturedPiece->getColour() != movedPiece->getColour() && capturedPiece->getType() != PieceType::Cannon) {
            moves.emplace_back(movedPiece, start, end, capturedPiece);
            return false;
        }

        // otherwise the the piece on the vertex with position end has the same
        //  colour as movedPiece, so only return false
        return false;
    }
    return false;
}

void Rules::addStraightPseudoLegalMoves(const std::pair<int, int> &start, 
    const Board &board, std::shared_ptr<Piece> &piece, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;
    int boardSizeR = board.getSizeR();
    int boardSizeC = board.getSizeC();
    // adds all the horizontal pseudo-legal moves
    for (int i = col + 1; i < boardSizeC; ++i) {
        if (!addPseudoLegalMove(start, {row, i}, board, piece, moves))
            break;
    }
    for (int i = col - 1; i >= 0; --i) {
        if (!addPseudoLegalMove(start, {row, i}, board, piece, moves))
            break;
    }

    // adds all the vertical pseudo-legal moves
    for (int i = row + 1; i < boardSizeR; ++i) {
        if (!addPseudoLegalMove(start, {i, col}, board, piece, moves))
            break;
    }
    for (int i = row - 1; i >= 0; --i) {
        if (!addPseudoLegalMove(start, {i, col}, board, piece, moves))
            break;
    }
}

void Rules::addStraightPseudoLegalCannonMoves(const std::pair<int, int> &start, 
    const Board &board, std::shared_ptr<Piece> &piece, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;
    int boardSizeR = board.getSizeR();
    int boardSizeC = board.getSizeC();

    // adds all the horizontal pseudo-legal moves
    for (int i = col + 1; i < boardSizeC; ++i) {
        if (!addPseudoLegalCannonMove(start, {row, i}, board, piece, moves) 
        && !(countHorizontalPieces(start,{row, i},board) <= 1) ){
            break;
        }
    }
    for (int i = col - 1; i >= 0; --i) {
        if (!addPseudoLegalCannonMove(start, {row, i}, board, piece, moves)
        && !(countHorizontalPieces(start,{row, i},board) <= 1))
            break;
    }

    // adds all the vertical pseudo-legal moves
    for (int i = row + 1; i < boardSizeR; ++i) {
        if (!addPseudoLegalCannonMove(start, {i, col}, board, piece, moves)
        && !(countVerticalPieces(start,{i, col},board) <= 1))
            break;
    }
    for (int i = row - 1; i >= 0; --i) {
        if (!addPseudoLegalCannonMove(start, {i, col}, board, piece, moves)
        && !(countVerticalPieces(start,{i, col},board) <= 1))
            break;
    }
}



void Rules::addDiagonalPseudoLegalMoves(const std::pair<int, int> &start, 
    const Board &board, std::shared_ptr<Piece> &piece, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;
    int boardSizeR = board.getSizeR();
    int boardSizeC = board.getSizeC();

    for (int i = row + 1, j = col + 1; i < boardSizeR && j < boardSizeC; ++i, ++j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < boardSizeC; --i, ++j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row + 1, j = col - 1; i < boardSizeR && j >= 0; ++i, --j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
}

void Rules::addPalaceDiagonalPseudoLegalMoves(const std::pair<int, int> &start, 
    const Board &board, std::shared_ptr<Piece> &piece, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;
    int boardSizeR = board.getSizeR();
    int boardSizeC = board.getSizeC();
    if( (row == 0 && col == 3) || (row == 0 && col == 5) ||
        (row == 1 && col == 4) || (row == 2 && col == 3) || (row == 2 && col == 5)){
    for (int i = row + 1, j = col + 1; i < 3 && j < 6; ++i, ++j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 3; --i, --j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < 6; --i, ++j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row + 1, j = col - 1; i < 3 && j >= 3; ++i, --j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    }
    if( (row == 8 && col == 4) || (row == 7 && col == 3) || (row == 7 && col == 5) ||
        (row == 9 && col == 3) || (row == 9 && col == 5)){
    for (int i = row + 1, j = col + 1; i < 10 && j < 6; ++i, ++j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col - 1; i >=  7 && j >= 3; --i, --j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col + 1; i >= 7 && j < 6; --i, ++j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row + 1, j = col - 1; i < 10 && j >= 3; ++i, --j) {
        if (!addPseudoLegalMove(start, {i, j}, board, piece, moves))
            break;
    }
    }
}

void Rules::addPalaceDiagonalPseudoLegalCannonMoves(const std::pair<int, int> &start, 
    const Board &board, std::shared_ptr<Piece> &piece, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;
    int boardSizeR = board.getSizeR();
    int boardSizeC = board.getSizeC();
    auto hurdlePiece1 = board.getVertex(1, 4).getPiece();
    auto hurdlePiece2 = board.getVertex(8, 4).getPiece();
    if(hurdlePiece1 && ((row == 0 && col == 3) || (row == 0 && col == 5) ||
        (row == 2 && col == 3) || (row == 2 && col == 5))){
    for (int i = row + 1, j = col + 1; i < 3 && j < 6; ++i, ++j) {
        if (!addPseudoLegalCannonMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 3; --i, --j) {
        if (!addPseudoLegalCannonMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col + 1; i >= 0 && j < 6; --i, ++j) {
        if (!addPseudoLegalCannonMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row + 1, j = col - 1; i < 3 && j >= 3; ++i, --j) {
        if (!addPseudoLegalCannonMove(start, {i, j}, board, piece, moves))
            break;
    }
    }
    if( hurdlePiece2 && ((row == 7 && col == 3) || (row == 7 && col == 5) ||
        (row == 9 && col == 3) || (row == 9 && col == 5))){
    for (int i = row + 1, j = col + 1; i < 10 && j < 6; ++i, ++j) {
        if (!addPseudoLegalCannonMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col - 1; i >=  7 && j >= 3; --i, --j) {
        if (!!addPseudoLegalCannonMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row - 1, j = col + 1; i >= 7 && j < 6; --i, ++j) {
        if (!!addPseudoLegalCannonMove(start, {i, j}, board, piece, moves))
            break;
    }
    for (int i = row + 1, j = col - 1; i < 10 && j >= 3; ++i, --j) {
        if (!!addPseudoLegalCannonMove(start, {i, j}, board, piece, moves))
            break;
    }
    }
}

void Rules::addGuardStandardMoves(const std::pair<int, int> &start, 
    const Board &board, std::shared_ptr<Piece> &guard, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;
    if((guard->getColour() == Colour::Green)){
    if((start.first == 8 && start.second == 4) ||
    (start.first == 7 && start.second == 3) || 
    (start.first == 7 && start.second == 5) ||
    (start.first == 9 && start.second == 3) ||
    (start.first == 9 && start.second == 5)){
            addPseudoLegalGuardMove(start, {row - 1, col}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row + 1, col}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row, col - 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row, col + 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row - 1, col - 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row + 1, col + 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row - 1, col + 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row + 1, col - 1}, board, guard, moves);
        }
    else {
            addPseudoLegalGuardMove(start, {row - 1, col}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row + 1, col}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row, col - 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row, col + 1}, board, guard, moves);
        }
    
    } else {
        if((start.first == 1 && start.second == 4) || 
        (start.first == 0 && start.second == 3) || 
            (start.first == 0 && start.second == 5) ||
            (start.first == 2 && start.second == 3) ||
            (start.first == 2 && start.second == 5)){
            addPseudoLegalGuardMove(start, {row - 1, col}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row + 1, col}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row, col - 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row, col + 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row - 1, col - 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row + 1, col + 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row - 1, col + 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row + 1, col - 1}, board, guard, moves);
        }
        else {
            addPseudoLegalGuardMove(start, {row - 1, col}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row + 1, col}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row, col - 1}, board, guard, moves);
            addPseudoLegalGuardMove(start, {row, col + 1}, board, guard, moves);
        }
    }
    
}

void Rules::addSoldierStandardMoves(const std::pair<int, int> &start, 
    const Board &board, std::shared_ptr<Piece> &soldier, std::vector<Move> &moves)
{
    int row = start.first, col = start.second;

    // gets an increment value based on the Soldier's colour
    int allowed_dir = soldier->getColour() == Colour::Green ? -1 : 1;

    // determines if the Pawn's standard move is pseudo-legal
    addPseudoLegalMove(start, {row + allowed_dir, col}, board, soldier, moves);
    addPseudoLegalMove(start, {row, col + 1}, board, soldier, moves);
    addPseudoLegalMove(start, {row, col - 1}, board, soldier, moves);
    if((start.first == 8 && start.second == 4) || (start.first == 1 && start.second == 4)){
            addPseudoLegalGuardMove(start, {row + allowed_dir, col - 1}, board, soldier, moves);
            addPseudoLegalGuardMove(start, {row + allowed_dir, col + 1}, board, soldier, moves);
        }
    
    if((start.first == 7 && start.second == 3) || (start.first == 2 && start.second == 3)) addPseudoLegalGuardMove(start, {row + allowed_dir, col + 1}, board, soldier, moves);
    if((start.first == 7 && start.second == 5) || (start.first == 2 && start.second == 5)) addPseudoLegalGuardMove(start, {row + allowed_dir, col - 1}, board, soldier, moves);
    
    
}
void Rules::addHorseStandardMoves(const std::pair<int, int> &start, 
    const Board &board, std::shared_ptr<Piece> &horse, std::vector<Move> &moves,
    const std::pair<int, int> &dir, const std::pair<int, int> &fork)
{
    int row = start.first, col = start.second;
    int dr = dir.first, dc = dir.second;
    int fr = fork.first, fc = fork.second;
    
    if (isValidPos(row + dr, col + dc, board)) {
        auto piece1 = board.getVertex(row + fr, col + fc).getPiece();
        
        // if there is no piece on the vertex with position (row + rowInc, col)
        if (!piece1) {
            auto capturePiece = board.getVertex(row+dr, col+dc).getPiece();
            if(!capturePiece)
                moves.emplace_back(horse, start, 
                    std::pair<int, int>{row + dr, col + dc});
            if (capturePiece && capturePiece->getColour() != horse->getColour())
                moves.emplace_back(horse, start, 
                    std::pair<int, int>{row + dr, col + dc}, capturePiece);
            
        }
    }
    
}

void Rules::addElephantStandardMoves(const std::pair<int, int> &start, 
    const Board &board, std::shared_ptr<Piece> &elephant, std::vector<Move> &moves,
    const std::pair<int, int> &dir, const std::pair<int, int> &fork)
{
    int row = start.first, col = start.second;
    int dr = dir.first, dc = dir.second;
    int fr = fork.first, fc = fork.second;
  
    if (isValidPos(row + dr, col + dc, board)) {
        auto piece1 = board.getVertex(row + fr, col + fc).getPiece();
        auto piece2 = board.getVertex(row + (dr+fr)/2, col + (dc+fc)/2).getPiece();
        
        // if there is no piece on the vertex with position (row + rowInc, col)
        if (!piece1 && !piece2) {
            auto capturePiece = board.getVertex(row+dr, col+dc).getPiece();
            if(!capturePiece)
                moves.emplace_back(elephant, start, 
                    std::pair<int, int>{row + dr, col + dc});
            if (capturePiece && capturePiece->getColour() != elephant->getColour())
                moves.emplace_back(elephant, start, 
                    std::pair<int, int>{row + dr, col + dc}, capturePiece);
            
        }
    }
}


std::vector<Move> 
Rules::generatePseudoLegalMoves(const std::pair<int, int> &start, 
    const Board &board, const Move &previousMove)
{
    std::vector<Move> moves;

    int row = start.first, col = start.second;
    auto piece = board.getVertex(row, col).getPiece();

    if (piece->getType() == PieceType::General || piece->getType() == PieceType::Guard) {
        addGuardStandardMoves(start, board, piece, moves);
    }
    else if (piece->getType() == PieceType::Cannon) {
        addStraightPseudoLegalCannonMoves(start, board, piece, moves);
        addPalaceDiagonalPseudoLegalCannonMoves(start, board, piece, moves);
    }
    else if (piece->getType() == PieceType::Chariot) {
        addStraightPseudoLegalMoves(start, board, piece, moves);
        addPalaceDiagonalPseudoLegalMoves(start, board, piece, moves);
    }
    else if (piece->getType() == PieceType::Horse) {
        addHorseStandardMoves(start, board, piece, moves, {1,2}, {0,1});
        addHorseStandardMoves(start, board, piece, moves, {-1,2}, {0,1});
        addHorseStandardMoves(start, board, piece, moves, {1,-2}, {0,-1});
        addHorseStandardMoves(start, board, piece, moves, {-1,-2}, {0,-1});
        addHorseStandardMoves(start, board, piece, moves, {2,1}, {1,0});
        addHorseStandardMoves(start, board, piece, moves, {2,-1}, {1,0});
        addHorseStandardMoves(start, board, piece, moves, {-2,1}, {-1,0});
        addHorseStandardMoves(start, board, piece, moves, {-2,-1}, {-1,0});
    }
    else if (piece->getType() == PieceType::Elephant) {
        addElephantStandardMoves(start, board, piece, moves, {2,3}, {0,1});
        addElephantStandardMoves(start, board, piece, moves, {-2,3}, {0,1});
        addElephantStandardMoves(start, board, piece, moves, {2,-3}, {0,-1});
        addElephantStandardMoves(start, board, piece, moves, {-2,-3}, {0,-1});
        addElephantStandardMoves(start, board, piece, moves, {3,2}, {1,0});
        addElephantStandardMoves(start, board, piece, moves, {3,-2}, {1,0});
        addElephantStandardMoves(start, board, piece, moves, {-3,2}, {-1,0});
        addElephantStandardMoves(start, board, piece, moves, {-3,-2}, {-1,0});
    }  
    else if (piece->getType() == PieceType::Soldier) {
        addSoldierStandardMoves(start, board, piece, moves);
    }
    return moves;
}

bool Rules::isUnderAttack(Colour c, const std::pair<int, int> &pos, 
    const Board &board, const Move &previousMove)
{
    if (c == Colour::Green) {

        // gets a reference to the set of all positions of vertices that have
        //  green pieces
        auto &greenPieces = board.getGreenPieces();
        for (auto &start : greenPieces) {

            // generate all pseudo-legal moves for the green piece on the
            //  vertex with position start
            auto moves = generatePseudoLegalMoves(start, board, previousMove);
            for (auto &move : moves) {

                // if the end position of the move is the same as pos,
                //  return true
                if (move.endPos == pos)
                    return true;
            }
        }
        return false;
    }
    else {

        // gets a reference to the set of all positions of vertices that have
        //  red pieces
        auto &redPieces = board.getRedPieces();

        for (auto &start : redPieces) {

            // generate all pseudo-legal moves for the red piece on the
            //  vertex with position start
            auto moves = generatePseudoLegalMoves(start, board, previousMove);
            for (auto &move : moves) {

                // if the end position of the move is the same as pos,
                //  return true
                if (move.endPos == pos)
                    return true;
            }
        }
        return false;
    }
}

std::vector<Move> 
Rules::generateFullyLegalMoves(const std::pair<int, int> &start, 
    const Board &board, const Move &previousMove)
{
    int row = start.first, col = start.second;
    auto piece = board.getVertex(row, col).getPiece();

    // if there is no piece on the vertex with position start, return no moves
    if (!piece)
        return std::vector<Move>{};

    std::vector<Move> moves{generatePseudoLegalMoves(start, board, previousMove)};

    // gets a copy of the current board
    Board tmpBoard{board};

    auto it = moves.begin();
    while (it != moves.end()) {
        int endRow = it->endPos.first, endCol = it->endPos.second;
        bool inCheck;
        
        // make the move
        auto attacGeneralPiece = tmpBoard.removePiece(row, col);
        auto capturedPiece = tmpBoard.removePiece(endRow, endCol);
        tmpBoard.placePiece(endRow, endCol, attacGeneralPiece);

        // check if the General with the same colour as piece is in check
        //  on tmpBoard
        inCheck = check(piece->getColour(), tmpBoard, *it);

        // undo the move
        attacGeneralPiece = tmpBoard.removePiece(endRow, endCol);
        tmpBoard.placePiece(endRow, endCol, capturedPiece);
        tmpBoard.placePiece(row, col, attacGeneralPiece);
        

        // if the General with the same colour as piece is in check on tmpBoard,
        //  erase the move, otherwise check the next move
        if (inCheck)
            it = moves.erase(it);
        else
            ++it;
    }
    
    
    return moves;
}

bool Rules::check(Colour c, const Board &board, const Move &previousMove) 
{
    if (c == Colour::Green) {

        // gets a reference to the set of all positions of vertices that have
        //  red pieces
        auto &redPieces = board.getRedPieces();
        for (auto &start : redPieces) {

            // generate all pseudo-legal moves for the red piece on the
            //  vertex with position start
            auto moves = generatePseudoLegalMoves(start, board, previousMove);
            for (auto &move : moves) {

                // gets a reference to the captured piece of the move
                auto &piece = move.capturedPiece;

                // if the captured piece is a General, return true
                if (piece && piece->getType() == PieceType::General)
                    return true;
            }
        }
        return false;
    }
    else {

        // gets a reference to the set of all positions of vertices that have
        //  green pieces
        auto &greenPieces = board.getGreenPieces();

        for (auto &start : greenPieces) {

            // generate all pseudo-legal moves for the green piece on the
            //  vertex with position start
            auto moves = generatePseudoLegalMoves(start, board, previousMove);
            for (auto &move : moves) {

                // gets a reference to the captured piece of the move
                auto &piece = move.capturedPiece;

                // if the captured piece is a General, return true
                if (piece && piece->getType() == PieceType::General)
                    return true;
            }
        }
        return false;
    }
}

bool Rules::checkmate(Colour c, const Board &board, const Move &previousMove)
{
    std::pair<int, int> greenGeneralPos = board.getGreenGeneralPos();
    std::pair<int, int> redGeneralPos = board.getRedGeneralPos();

    // gets a reference to the set of all positions of vertices that have
    //  green pieces
    auto &greenPieces = board.getGreenPieces();

    // gets a reference to the set of all positions of vertices that have
    //  red pieces
    auto &redPieces = board.getRedPieces();
    if(check(c, board, previousMove)){
    
    
        if (c == Colour::Green) {

        // gets a reference to the set of all positions of vertices that have
        //  green pieces
        auto &greenPieces = board.getGreenPieces();
        for (auto &start : greenPieces) {
            
            // if the green player has any legal moves, return true
            if (generateFullyLegalMoves(start, board, previousMove).size() > 0)
                return false;
        }
        return true;
    }
    else {

        // gets a reference to the set of all positions of vertices that have
        //  red pieces
        auto &redPieces = board.getRedPieces();
        for (auto &start : redPieces) {
            
            // if the red player has any legal moves, return true
            if (generateFullyLegalMoves(start, board, previousMove).size() > 0)
                return false;
        }
        return true;
    }

    }
    return false;        
}



bool Rules::bikjang(Colour c, const Board &board, const Move &previousMove) 
{
    std::pair<int, int> greenGeneralPos = board.getGreenGeneralPos();
    std::pair<int, int> redGeneralPos = board.getRedGeneralPos();
    if (greenGeneralPos.second == redGeneralPos.second && 
    countVerticalPieces(greenGeneralPos, redGeneralPos, board) == 0){
        if (c == Colour::Green) {
        // gets a reference to the set of all positions of vertices that have
        //  green pieces
        auto &greenPieces = board.getGreenPieces();
        for (auto &start : greenPieces) {
            
            // if the green player has any legal moves, return true
            auto moves = generateFullyLegalMoves(start, board, previousMove);
            if (moves.size() > 0){
                for(auto &move: moves){
                    if(move.movedPiece->getType() != PieceType::General){
                        if((move.endPos.second == redGeneralPos.second) &&  
                        (move.endPos.first < greenGeneralPos.first && move.endPos.first > redGeneralPos.first) ){
                            return false;
                            }
                        }
                    if(move.movedPiece->getType() == PieceType::General){
                        if(!(move.endPos.second == redGeneralPos.second) ){
                            return false;
                        } else if(countVerticalPieces(move.endPos, redGeneralPos, board) != 0){
                            return false;
                        }
                    }
                } 
                return true;
                }
                
            }
            return false;
        } else {

        // gets a reference to the set of all positions of vertices that have
        //  red pieces
        auto &redPieces = board.getRedPieces();
        for (auto &start : redPieces) {
          
            // if the red player has any legal moves, return true
            auto moves = generateFullyLegalMoves(start, board, previousMove);
            if (moves.size() > 0){
                for(auto &move: moves){
                    if(move.movedPiece->getType() != PieceType::General){
                        if((move.endPos.second == greenGeneralPos.second) &&  
                        (move.endPos.first < greenGeneralPos.first && move.endPos.first > redGeneralPos.first) ){
                            return false;
                            }
                        }
                    if(move.movedPiece->getType() == PieceType::General){
                        if(!(move.endPos.second == greenGeneralPos.second) ){
                            return false;
                        } else if(countVerticalPieces(move.endPos, greenGeneralPos, board) != 0){
                            return false;
                        }
                    }
                } 
                return true;
                }
        }
        return false;
        }
    }
    return false;
}


