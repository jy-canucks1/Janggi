#include "gameonline.h"
#include <bits/stdc++.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 50


Move Gameonline::getPreviousMove() const {
    return moveHistory.top();
}

Gameonline::Gameonline(int sizeR, int sizeC): board{sizeR, sizeC}, greenScore{0.0}, redScore{0.0} {

    // adds an default initialized move to moveHistory, used as a dummy object
    //  to represent that there was no previous move
    moveHistory.emplace();
}


void Gameonline::start() {
    std::string outerCommand, aux;
    bool customSetup = false;
    int connection;
    Colour firstPlayerColour = Colour::Green;
    Colour you;
    Colour counterpart;
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
      
    socklen_t clnt_adr_sz;
    struct sockaddr_in serv_adr, clnt_adr;
    serv_sock = socket(AF_INET , SOCK_STREAM , 0);
    int port;
    std::cout << "port number? ";
    std::cin >> port;
    if(serv_sock == -1)
        std::cout << "Creation of socket failed" << std::endl;

    std::cout << "\nChoose one of 1-3"<< std::endl;
    // server(green)
    std::cout << "\n1. Create Session (Green)"<< std::endl;
    // client(red)
    std::cout << "2. Join Session (Red)"<< std::endl;
    std::cout << "3. Quit"<< std::endl;
    std::cin >> outerCommand;

    if (outerCommand == "3") { return; }
            
    if (outerCommand == "1") {
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(port);
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        std::cout << "Socket binding has failed" << std::endl;
    // listens to the client while others are waiting in queue of size 4
	int listenStatus = listen(serv_sock , 4);
	if(listenStatus < 0) {	
        // when queue is full listen fails
		std::cout << "Listener has failed" << std::endl;
		return;
    }
        
    std::cout << "\t\t...Waiting for connection...1 \n\n";
    clnt_adr_sz = sizeof(clnt_adr);
    connection = accept(serv_sock , (struct sockaddr*) &clnt_adr , &clnt_adr_sz);
	if(connection < 0) {
		std::cout << "Server didn't accept the request." << std::endl;
		    return;
	}
	else
    {
	std::cout << "Server accepted the request. \n" ;
	}
    std::cout << "Do not exceed 30 characters and input q when you want to end the chatting session."<<std::endl;
    std::cout << "Decide Red(r) or Green(g)!"<<std::endl;
    std::cout << "\t\t...Waiting for counterpart's message... \n\n";
    char message1[BUF_SIZE];
        
    while(true) {
        char text1[BUF_SIZE];
        int received = recv(connection, message1, BUF_SIZE, 0);
        if( received > 0) {
            std::cout << "\nCounterpart : " << message1 <<std::endl;
            // starts the game when special code(gl - Good Luck) is input 
            if(!strcmp(message1, "gl") && !strcmp(text1, "gl")) {
                std::cout << "Conversation ended. Game Starts."<< std::endl;
                send(connection, text1, strlen(text1)+1, 0);
                you = Colour::Green;
                counterpart = Colour::Red;
                    
                break;

            } else if(!strcmp(message1, "q")){
                break;
            } 
                
            if(!strcmp(text1, "q")){
                close(serv_sock);
                break;
            }    
                  
            std::cout << "You: ";
                
            std::string s;
            getline(std::cin, s);
            int n = s.size();
			for(int i = 0 ; i < n ; i++){
				    text1[i] = s[i];
			    }

			text1[n] = '\0';
            send(connection, text1, strlen(text1)+1, 0);
            }
        }    
        
    } else if(outerCommand == "2"){
       
        serv_adr.sin_family = AF_INET;
        serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serv_adr.sin_port = htons(port);

        std::cout << "\t\t...Waiting for connection...2 \n\n";
        //listen to the client while others are waiting in queue of size 5
	    if(connect(serv_sock,  (struct sockaddr*) & serv_adr , sizeof(serv_adr)) < 0) {
		    std::cout << "Connection Error..." << std::endl;
		    return;
	    } else
	    {
		std::cout << "\t\tConnection Established..." << std::endl;
	    }

        std::cout << "Do not exceed 30 characters and input q when you want to end the chatting session."<<std::endl;
        std::cout << "Decide Red(r) or Green(g)!"<<std::endl;
        while(true)
        {
          
            std::string s;
            char text2[BUF_SIZE];
            std::cout << "You: ";
            getline(std::cin, s);
            int n = s.size();
			for(int i = 0 ; i < n ; i++) {
				text2[i] = s[i];
			}

			text2[n] = '\0';
            send(serv_sock, text2, strlen(text2)+1, 0);
            char message2[BUF_SIZE];
           
            if(!strcmp(text2, "q")) {
                close(serv_sock);
                break;
            }

            int received = recv(serv_sock, message2, BUF_SIZE, 0);
            if(received < 0)
		    {
			std::cout << "Packet recieve failed." << std::endl;
			return;
		    }
		    else if(received == 0)
		    {
			std::cout << "Server is off." << std::endl;
			return;
		    }

            std::cout << "\nCounterpart: " << message2 <<std::endl;
            if((!strcmp(message2, "gl") && !strcmp(text2, "gl"))) {
                  
                std::cout << "Conversation ended. Game Starts."<< std::endl;
                send(serv_sock, text2, strlen(text2)+1, 0);
                
                you = Colour::Red;
                counterpart = Colour::Green;

                break;
            } else if(!strcmp(message2, "q") || s == "q"){
                break;
            }     

        }
        } 

    while (true) {
        char text[BUF_SIZE];
        player1 = std::make_unique<HumanPlayer>(Colour::Green);
        player2 = std::make_unique<HumanPlayer>(Colour::Red);
        if (!std::cin)
            break;

        if (!customSetup)
            board.initBoard(1);
            
            
        // output the current board
        std::cout << "\n" << board << std::endl;
        
        // set up which colour player will play first
        Player *currentPlayer = firstPlayerColour == Colour::Green ?
            player1.get() : player2.get();

        std::string innerCommand;
        std::string strstart;
        std::string strend;
        while (true) {
                
            std::cout << "\n" << (currentPlayer->getColour() == Colour::Green ?
                "Green " : "Red ") << "player's turn ";
            if(currentPlayer->getColour() == you) { 
                std::cout << "\nYour turn. Enter commend: ";
                std::cin >> innerCommand;
                } 
            else {
                std::cout << "Waiting for the Counterpart........" << std::endl;
                clnt_adr_sz = sizeof(clnt_adr);
                // str_len = recv(serv_sock, message, BUF_SIZE, 0);
                while(true){
                if(outerCommand == "1"){
                str_len = recv(connection, message, BUF_SIZE, 0);
                }
                else if(outerCommand == "2"){
                str_len = recv(serv_sock, message, BUF_SIZE, 0);
                }

                if(str_len > 0){
                std::istringstream iss{message};

                std::string strarry[3] = {"", "", ""};
                int i = 0;
                while(iss || i < 3) { 
                iss >> strarry[i];
                i++;
                }
                innerCommand = strarry[0];
                strstart = strarry[1];
                strend = strarry[2];
                break;
                }
                }
            }

            if (!std::cin){
                std::string mes = "end";
                for(int i = 0 ; i < BUF_SIZE ; i++){
				        text[i] = '\0';
			            }
                int n = mes.size();
			    for(int i = 0 ; i < n ; i++){
				        text[i] = mes[i];
			            }

			    text[n] = '\0';
                        
                if(outerCommand == "1"){
                    send(connection, text, strlen(text)+1, 0);
                    }
                else if(outerCommand == "2"){
                    send(serv_sock, text, strlen(text)+1, 0);
                    }
                std::cout << "\n\nFinal score:" << std::endl;
                std::cout << "Green: " << greenScore << std::endl;
                std::cout << "Red: " << redScore << std::endl;
                close(serv_sock);
                break;
                }
            if (!strcmp(message, "end")){
                std::cout << "\n\nFinal score:" << std::endl;
                std::cout << "Green: " << greenScore << std::endl;
                std::cout << "Red: " << redScore << std::endl;
                close(serv_sock);
                return;
            }
            if (innerCommand == "move") {
                Move playerMove;
                // gets the player's move
                if(currentPlayer->getColour() == you) {
                    std::string m1;
                    std::string m2;
                    std::cin >> m1 >> m2;
                    strstart = m1;
                    strend = m2;
                    std::string t;
                    t = innerCommand + " " + m1 + " " + m2;
                    for(int i = 0 ; i < BUF_SIZE ; i++){
				    text[i] = '\0';
			        }
                    int n = t.size();
			        for(int i = 0 ; i < n ; i++){
				    text[i] = t[i];
			        }

			        text[n] = '\0';
                    //send(connection, text, strlen(text)+1, 0);
                    if(outerCommand == "1"){
                    send(connection, text, strlen(text)+1, 0);
                    }
                    else if(outerCommand == "2"){
                    send(serv_sock, text, strlen(text)+1, 0);
                    }
                    playerMove = currentPlayer->makeMoveOnline(board, getPreviousMove(), strstart, strend);
                } else {
                     playerMove = 
                        currentPlayer->makeMoveOnline(board, getPreviousMove(), strstart, strend);
                }
                    
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
                // if the other player's General is not in check and stalemated
                else if (Rules::bikjang(enemyColour, board, getPreviousMove())) {
                    char a;
                    std::cout << "Call Bikjang? (y/n)"<< std::endl;
                    std::cin >> a;
                    if(a == 'y') {
                        std::cout << "\nBikjang!" << std::endl << "Draw!" <<std::endl;
                        std::string mes = "\nBikjang!\nDraw!";
                        for(int i = 0 ; i < BUF_SIZE ; i++){
				        text[i] = '\0';
			            }
                        int n = mes.size();
			            for(int i = 0 ; i < n ; i++){
				        text[i] = mes[i];
			            }

			            text[n] = '\0';
                        //send(serv_sock, text, strlen(text)+1, 0);
                        if(outerCommand == "1"){
                        send(connection, text, strlen(text)+1, 0);
                        }
                        else if(outerCommand == "2"){
                        send(serv_sock, text, strlen(text)+1, 0);
                        }
                    }
                        
                    // increment both scores by half a point
                    greenScore += 0.5;
                    redScore += 0.5;

                    // end the current game
                    break;
                } 
                    
                // alternate the current player to the other player
                currentPlayer = currentPlayer == player1.get() ? 
                    player2.get() : player1.get();

            } else if (!strcmp(message, "\nBikjang!\nDraw!")) {
                  std::cout << message <<std::endl;
                  greenScore += 0.5;
                  redScore += 0.5;
                  break;  
            } else if (innerCommand == "resign") {
                
                std::cout << "\n" << (currentPlayer->getColour() == Colour::Green ? 
                    "Red wins!" : "Green wins!") << std::endl;

                // increment the score for other player's colour
                currentPlayer->getColour() == Colour::Green ? 
                    ++redScore : ++greenScore;
                std::string mes = "resign!";
                for(int i = 0 ; i < BUF_SIZE ; i++){
				        text[i] = '\0';
			            }
                int n = mes.size();
			    for(int i = 0 ; i < n ; i++){
				        text[i] = mes[i];
			            }

			    text[n] = '\0';
                        
                if(outerCommand == "1"){
                    send(connection, text, strlen(text)+1, 0);
                    }
                else if(outerCommand == "2"){
                    send(serv_sock, text, strlen(text)+1, 0);
                    }
                    // end the current game
                break;
            }
            else if (!strcmp(message, "resign!")) {
                std::cout << "\n" << (currentPlayer->getColour() == Colour::Green ? 
                    "Red wins!" : "Green wins!") << std::endl;
                currentPlayer->getColour() == Colour::Green ? 
                    ++redScore : ++greenScore;
                  break;    
            } else if (innerCommand == "pass") {
                currentPlayer = currentPlayer == player1.get() ? 
                    player2.get() : player1.get();
                std::string mes = "pass!";
                for(int i = 0 ; i < BUF_SIZE ; i++){
				        text[i] = '\0';
			            }
                int n = mes.size();
			    for(int i = 0 ; i < n ; i++){
				        text[i] = mes[i];
			            }

			    text[n] = '\0';
                        
                if(outerCommand == "1"){
                    send(connection, text, strlen(text)+1, 0);
                    }
                else if(outerCommand == "2"){
                    send(serv_sock, text, strlen(text)+1, 0);
                    }  
            }else if (!strcmp(message, "pass!")) {
                currentPlayer = currentPlayer == player1.get() ? 
                    player2.get() : player1.get();
            } else if(innerCommand == "gl"){
                continue;
            } else {
                    std::cout << "\nInvalid command: " << innerCommand << std::endl;
                    std::getline(std::cin, aux);
            }
        }
            
            // reset the customSetup flag, should replace with a board cleanup
        customSetup = false;
        
    }

    // display the final score 
    
}

