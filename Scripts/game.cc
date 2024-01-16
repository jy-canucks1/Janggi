#include "game.h"

Move Game::getPreviousMove() const {
    return moveHistory.top();
}

Game::Game(int sizeR, int sizeC): board{sizeR, sizeC}, greenScore{0.0}, redScore{0.0} {

    // adds an default initialized move to moveHistory, used as a dummy object
    //  to represent that there was no previous move
    moveHistory.emplace();
}

void Game::start() {
    std::string outerCommand, aux;
    bool customSetup = false;
    Colour firstPlayerColour = Colour::Green;

    while (true) {

        std::cout << "\nEnter command: ";
        std::cin >> outerCommand;

        if (!std::cin)
            break;

        if (outerCommand == "game") {
            std::string greenPlayer, redPlayer;
            std::cin >> greenPlayer >> redPlayer;

            if (greenPlayer == "human")
                player1 = std::make_unique<HumanPlayer>(Colour::Green);
            /*
            else if (greenPlayer == "computer[1]")
                player1 = std::make_unique<ComputerPlayer>(Colour::Green, 1);
            else if (greenPlayer == "computer[2]")
                player1 = std::make_unique<ComputerPlayer>(Colour::Green, 2);
            else if (greenPlayer == "computer[3]")
                player1 = std::make_unique<ComputerPlayer>(Colour::Green, 3);
            else
                player1 = std::make_unique<ComputerPlayer>(Colour::Green, 4);
            */
            if (redPlayer == "human")
                player2 = std::make_unique<HumanPlayer>(Colour::Red);
            /*
            else if (redPlayer == "computer[1]")
                player2 = std::make_unique<ComputerPlayer>(Colour::Red, 1);
            else if (redPlayer == "computer[2]")
                player2 = std::make_unique<ComputerPlayer>(Colour::Red, 2);
            else if (redPlayer == "computer[3]")
                player2 = std::make_unique<ComputerPlayer>(Colour::Red, 3);
            else
                player2 = std::make_unique<ComputerPlayer>(Colour::Red, 4);
            */
            // if setup mode has not been enteRed, initialized the board with
            //  all the needed pieces for a default janggi game
            if (!customSetup)
                board.initBoard();
            
            // output the current board
            std::cout << "\n" << board << std::endl;

            // set up which colour player will play first
            Player *currentPlayer = firstPlayerColour == Colour::Green ?
                player1.get() : player2.get();

            std::string innerCommand;

            while (true) {
                
                std::cout << "\n" << (currentPlayer->getColour() == Colour::Green ?
                    "Green " : "Red ") << "player's turn: ";
                std::cin >> innerCommand;

                if (!std::cin)
                    break;

                if (innerCommand == "move") {

                    // gets the player's move
                    Move playerMove = 
                        currentPlayer->makeMove(board, getPreviousMove());
                    
                    // if the player's move is invalid or illegal, reprompt
                    //  the player for another move (should only apply to
                    //  human players)
                    if (!playerMove.movedPiece)
                        continue;
                    
                    int startRow = playerMove.startPos.first;
                    int startCol = playerMove.startPos.second;

                    int endRow = playerMove.endPos.first;
                    int endCol = playerMove.endPos.second;

                    // move the attacGeneral piece and remove the captuRed piece
                    //  (if there is one)
                    auto attacGeneralPiece = board.removePiece(startRow, startCol);
                    board.removePiece(endRow, endCol);
                    board.placePiece(endRow, endCol, attacGeneralPiece);

                    // if the attacGeneral piece has moved yet, set to to be moved
                    if (!attacGeneralPiece->isMoved())
                        attacGeneralPiece->firstMove();
                    
                    // gets the colour of the attacGeneral piece
                    Colour attacGeneralColour = attacGeneralPiece->getColour();

                    // if the move was enPassant, remove the enPassanted piece
                    

                    // add the player's move to moveHistory
                    moveHistory.push(playerMove);

                    // output the current board
                    std::cout << "\n" << board << std::endl;

                    // gets the colour of the current player
                    Colour allyColour = currentPlayer->getColour();

                    // gets the colour of the other player
                    Colour enemyColour = allyColour == Colour::Green ? 
                        Colour::Red : Colour::Green;
                    
                    // if the other player's General is now in check
                    if (Rules::check(enemyColour, board, getPreviousMove())) {

                        // if the other player's General is now in checkmate
                        if (Rules::checkmate(enemyColour, board, getPreviousMove())) {
                            std::cout << "\n" << "Checkmate! " 
                                << (allyColour == Colour::Green ? "Green " : "Red ")
                                << "wins!" << std::endl;
                            
                            // increment the score for current player's colour
                            allyColour == Colour::Green ? ++greenScore : ++redScore;

                            // end the current game
                            break;
                        }
                        
                        else
                            std::cout << "\n" << (enemyColour == Colour::Green ? 
                                "Green " : "Red ") << "is in check."  << std::endl;
                    }
                    // if the other player's General is not in check and bikjang
                    else if (Rules::bikjang(enemyColour, board, getPreviousMove())) {
                        char a;
                        std::cout << "call Bikjang? (y/n)"<< std::endl;
                        std::cin >> a;
                        if(a == 'y') {
                            std::cout << "\nBikjang!" << std::endl << "Draw!" <<std::endl;
                        
                        // increment both scores by half a point
                        greenScore += 0.5;
                        redScore += 0.5;

                        // end the current game
                        break;
                        }
                    }
                    
                    // alternate the current player to the other player
                    currentPlayer = currentPlayer == player1.get() ? 
                        player2.get() : player1.get();

                } else if (innerCommand == "resign") {
                    std::cout << "\n" << (currentPlayer->getColour() == Colour::Green ? 
                        "Red wins!" : "Green wins!") << std::endl;

                    // increment the score for other player's colour
                    currentPlayer->getColour() == Colour::Green ? 
                        ++redScore : ++greenScore;

                    // end the current game
                    break;

                } else if (innerCommand == "pass") {
                    currentPlayer = currentPlayer == player1.get() ? 
                        player2.get() : player1.get();
                    
                } else if(innerCommand == "undo") {
                    
                    auto previousMove = moveHistory.top();
                    moveHistory.pop();
                    int startRow = previousMove.startPos.first;
                    int startCol = previousMove.startPos.second;

                    int endRow = previousMove.endPos.first;
                    int endCol = previousMove.endPos.second;

                    // move the attacGeneral piece back and regenerate the captured piece
                    //  (if there is one)
                    auto attacGeneralPiece = board.removePiece(endRow, endCol);
                    if(previousMove.capturedPiece) board.placePiece(endRow, endCol, previousMove.capturedPiece);
                    board.placePiece(startRow, startCol, attacGeneralPiece);
                    std::cout << "\n" << board << std::endl;
                    currentPlayer = currentPlayer == player1.get() ? 
                        player2.get() : player1.get();

                } else {
                    std::cout << "\nInvalid command: " << innerCommand << std::endl;
                    std::getline(std::cin, aux);
                }
            }
            
            // reset the customSetup flag, should replace with a board cleanup
            //  method later
            customSetup = false;
        }

        else if (outerCommand == "setup") {
            
            // indicate that setup mode has been enteRed
            customSetup = true;

            std::string fnCommand;

            // maps a string that represents the vertex position to a pair 
            //  of ints that represent the vertex position
            std::map<std::string, std::pair<int, int>> vertexMap = {

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

            // maps a string that represents a piece to a pair of a Colour
            //  and a PieceType
            std::map<std::string, std::pair<Colour, PieceType>> pieceTypeMap {

                {"G", {Colour::Green, PieceType::General}}, 
                {"U", {Colour::Green, PieceType::Guard}}, 
                {"H", {Colour::Green, PieceType::Horse}}, 
                {"C", {Colour::Green, PieceType::Chariot}}, 
                {"A", {Colour::Green, PieceType::Cannon}},
                {"E", {Colour::Green, PieceType::Elephant}}, 
                {"S", {Colour::Green, PieceType::Soldier}},

                {"g", {Colour::Red, PieceType::General}}, 
                {"u", {Colour::Red, PieceType::Guard}}, 
                {"h", {Colour::Red, PieceType::Horse}}, 
                {"c", {Colour::Red, PieceType::Chariot}}, 
                {"a", {Colour::Red, PieceType::Cannon}},
                {"e", {Colour::Red, PieceType::Elephant}}, 
                {"s", {Colour::Red, PieceType::Soldier}},
            };

            while (true) {

                std::cout << "\nEnter function command: ";
                std::cin >> fnCommand;

                if (!std::cin)
                    break;

                if (fnCommand == "+") {
                    std::string strPiece, strPos;
                    std::cin >> strPiece >> strPos;
                        
                    // if the arguments are invalid
                    if (!pieceTypeMap.contains(strPiece) || 
                        !vertexMap.contains(strPos))
                    {
                        std::cout << "\nInvalid arguments: " << strPiece
                            << " or " << strPos << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    // if the piece to be placed is the Green General
                    if (strPiece == "G") {
                        
                        // gets the pair representing the position of the 
                        //  Green General on the board
                        std::pair<int, int> greenGeneralPos = board.getGreenGeneralPos();

                        // if there is already a Green General on the board
                        if (greenGeneralPos.first != -1 && greenGeneralPos.second != -1)
                        {
                            std::cout << "\nGreen General already on the board." 
                                << std::endl;
                            std::getline(std::cin, aux);
                            continue;
                        }
                    }

                    // if the piece to be placed is the Red General
                    if (strPiece == "g") {

                        // gets the pair representing the position of the 
                        //  Red General on the board
                        std::pair<int, int> RedGeneralPos = board.getRedGeneralPos();

                        // if there is already a Red General on the board
                        if (RedGeneralPos.first != -1 && RedGeneralPos.second != -1)
                        {
                            std::cout << "\nRed General already on the board. " 
                                << std::endl;
                            std::getline(std::cin, aux);
                            continue;
                        }
                    }

                    Colour colour = pieceTypeMap[strPiece].first;
                    PieceType type = pieceTypeMap[strPiece].second;
                    int row = vertexMap[strPos].first;
                    int col = vertexMap[strPos].second;
                    
                    // remove the piece on the vertex with position
                    //  (row, col) if there is one, and place the newly
                    //  allocate piece
                    board.removePiece(row, col);
                    auto newPiece = generatePiece(colour, type);
                    board.placePiece(row, col, newPiece);

                    // explicitly set the placed piece as moved to not
                   
                    newPiece->firstMove();

                    // Redisplay the board
                    std::cout << "\n" << board << std::endl;
                }

                else if (fnCommand == "-") {
                    std::string strPos;
                    std::cin >> strPos;
                        
                    // if the argument are invalid
                    if (!vertexMap.contains(strPos)) 
                    {
                        std::cout << "\nInvalid argument: " << strPos << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    int row = vertexMap[strPos].first;
                    int col = vertexMap[strPos].second;

                    // remove the piece on the vertex with position
                    //  (row, col) if there is one
                    auto removedPiece = board.removePiece(row, col);

                    // if there is no piece on the vertex with position 
                    //  (row, col)
                    if (!removedPiece)
                    {
                        std::cout << "\nNo piece on " << strPos << "." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    // Redisplay the board
                    std::cout << "\n" << board << std::endl;
                }

                else if (fnCommand == "=") {
                    std::string strColour;
                    std::cin >> strColour;

                    if (strColour != "Green" && strColour != "Red")
                    {
                        std::cout << "\nInvalid argument: " << strColour 
                            << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    // set the player who will play first to the
                    //  the choice of colour
                    firstPlayerColour = strColour == "Green" ? 
                        Colour::Green : Colour::Red;
                    
                    std::cout << "\n" << (firstPlayerColour == Colour::Green ? 
                        "Green" : "Red") << " player will have the first move." 
                        << std::endl;
                }

                else if (fnCommand == "done") {

                    // gets the vertex positions of the Green General and Red
                    //  General on the board
                    std::pair<int, int> greenGeneralPos = board.getGreenGeneralPos();
                    std::pair<int, int> RedGeneralPos = board.getRedGeneralPos();

                    // if there is no Green General or Red General on the board
                    if ((greenGeneralPos.first == -1 && greenGeneralPos.second == -1) ||
                        (RedGeneralPos.first == -1 && RedGeneralPos.second == -1))
                    {
                        std::cout << "\nInvalid board setup. Green General or Red General"
                            " missing. Continue to setup the board." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }


                    if (Rules::checkmate(Colour::Green, board, getPreviousMove()))
                    {
                        std::cout << "\nInvalid board setup. Checkmate! Red wins."
                            " Continue to setup the board." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    if (Rules::checkmate(Colour::Red, board, getPreviousMove()))
                    {
                        std::cout << "\nInvalid board setup. Checkmate! Green wins."
                            " Continue to setup the board." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }
                    // if the Green General is in check
                    if (Rules::check(Colour::Green, board, getPreviousMove()))
                    {
                        std::cout << "\nInvalid board setup. Green General in check."
                            " Continue to setup the board." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }
                    

                    // if the Red General is in check
                    if (Rules::check(Colour::Red, board, getPreviousMove()))
                    {
                        std::cout << "\nInvalid board setup. Red General in check."
                            " Continue to setup the board." << std::endl;
                        std::getline(std::cin, aux);
                        continue;
                    }

                    
                    
                    std::cout << "\nBoard setup success." << std::endl;

                    // leave setup mode
                    break;
                }

                else {
                    std::cout << "\nInvalid command: " << fnCommand << std::endl;
                    std::getline(std::cin, aux);
                }
            }
        }
        
        else {
            std::cout << "\nInvalid command: " << outerCommand << std::endl;
            std::getline(std::cin, aux);
        }
    }

    // display the final score 
    std::cout << "\n\nFinal score:" << std::endl;
    std::cout << "Green: " << greenScore << std::endl;
    std::cout << "Red: " << redScore << std::endl;
}
