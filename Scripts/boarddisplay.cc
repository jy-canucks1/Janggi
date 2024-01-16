#include "boarddisplay.h"
#include "vertex.h"

BoardDisplay::BoardDisplay(int sizeR, int sizeC): boardSizeR{sizeR}, boardSizeC{sizeC}, graphicsDisplay{700, 700} {
    for (int i = 0; i < boardSizeR; ++i) {
        textDisplay.emplace_back(std::vector<char>{});
        for (int j = 0; j < boardSizeC; ++j) {
            char v = '+';
            textDisplay[i].emplace_back(v);
        }
    }
    graphicsDisplay.fillRectangle(39, 39, 490, 540, Xwindow::Green);
    graphicsDisplay.fillRectangle(57, 57, 449, 505, Xwindow::Black);
    for(int i = 0; i < boardSizeC - 1; ++i){
        for(int j = 0; j < boardSizeR - 1; ++j){
           graphicsDisplay.fillRectangle(58+56*i, 58+56*j, 55, 55, Xwindow::White);
        }
    }
    graphicsDisplay.drawLine(58+56*3, 58+56*0, 58+56*4, 58+56*1);
    graphicsDisplay.drawLine(58+56*5, 58+56*0, 58+56*4, 58+56*1);
    graphicsDisplay.drawLine(58+56*3, 58+56*2, 58+56*4, 58+56*1);
    graphicsDisplay.drawLine(58+56*5, 58+56*2, 58+56*4, 58+56*1);
    graphicsDisplay.drawLine(58+56*3, 58+56*7, 58+56*4, 58+56*8);
    graphicsDisplay.drawLine(58+56*5, 58+56*7, 58+56*4, 58+56*8);
    graphicsDisplay.drawLine(58+56*5, 58+56*9, 58+56*4, 58+56*8);
    graphicsDisplay.drawLine(58+56*3, 58+56*9, 58+56*4, 58+56*8);
    for(int i = 0; i < boardSizeC; ++i){
        for(int j = 0; j < boardSizeR; ++j){
            graphicsDisplay.fillRectangle(47 + 56 * i, 47 + 56 * j, 22, 22, Xwindow::Black);
            graphicsDisplay.fillRectangle(48 + 56 * i, 48 + 56 * j, 20, 20, Xwindow::White);
        }
    }

    for(int i = 0; i < boardSizeC; ++i){
        char x = 'a' + i;
        std::string xaxis = std::string(1, x);
        graphicsDisplay.drawString(58 + 55 * i, 30, xaxis);
        graphicsDisplay.drawString(58 + 55 * i, 600, xaxis);
    }
    for(int i = 0; i < boardSizeR; ++i){
        char x = '1'+ 8-i;
        std::string yaxis = std::string(1, x);
        graphicsDisplay.drawString(20, 68 + 55 * i, yaxis);
        graphicsDisplay.drawString(550, 68 + 55 * i, yaxis);
    }

}

int BoardDisplay::getBoardSizeR() const {
    return boardSizeR;
}

int BoardDisplay::getBoardSizeC() const {
    return boardSizeC;
}

void BoardDisplay::update(Vertex &vertex) {
    int row = vertex.getRow(), col = vertex.getColumn();
    char symbol;
    std::string dsymbol;
    if (vertex.getPiece()) {
        symbol = vertex.getPiece()->getSymbol();
        dsymbol = std::string(1, symbol);
    }
    else {
        symbol = '+';
    }
    textDisplay[row][col] = symbol;
    if(dsymbol != "") {
        if(dsymbol[0] < 91) graphicsDisplay.drawString(56+56*col, 58+56*row, dsymbol, Xwindow::Blue);
        else if(dsymbol[0] > 96 ) graphicsDisplay.drawString(56+56*col, 58+56*row, dsymbol, Xwindow::Red);
        /*
        if(dsymbol == "g") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "漢", Xwindow::Red);
        if(dsymbol == "e") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "象", Xwindow::Red);
        if(dsymbol == "h") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "馬", Xwindow::Red);
        if(dsymbol == "c") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "車", Xwindow::Red);
        if(dsymbol == "u") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "士", Xwindow::Red);
        if(dsymbol == "s") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "兵", Xwindow::Red);
        if(dsymbol == "a") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "包", Xwindow::Red);
        if(dsymbol == "G") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "楚", Xwindow::Blue);
        if(dsymbol == "E") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "象", Xwindow::Blue);
        if(dsymbol == "H") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "馬", Xwindow::Blue);
        if(dsymbol == "C") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "車", Xwindow::Blue);
        if(dsymbol == "U") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "士", Xwindow::Blue);
        if(dsymbol == "S") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "卒", Xwindow::Blue);
        if(dsymbol == "A") graphicsDisplay.drawString(58 + 55.5 * col, 58 + 55.5 * row, "包", Xwindow::Blue);
        */
    }
   else {
        graphicsDisplay.fillRectangle(48 + 56 * col, 48 + 56 * row, 20, 20, Xwindow::White);
    }
}

std::ostream &operator<<(std::ostream &out, BoardDisplay &d) {
    for (int i = 0; i < d.getBoardSizeR() - 1; ++i) {
        if(i == 0){
        out << d.getBoardSizeR() - i - 1 << " ";
        for (int j = 0; j < d.getBoardSizeC() - 1; ++j)
            out << d.textDisplay[i][j] << "ㅡ";
        out << d.textDisplay[i][d.getBoardSizeC() - 1];
        out << std::endl << "  ";
        for(int k = 0; k < d.getBoardSizeC() - 1; ++k){
            if(k == 3) {out << "|\\ "; continue;}
            if(k == 4) {out << "| /"; continue;}
            out << "|  ";
        }
        out << "|" << std::endl;
        continue;
        } else if(i == 1){
        out << d.getBoardSizeR() - i - 1 << " ";
        for (int j = 0; j < d.getBoardSizeC() - 1; ++j)
            out << d.textDisplay[i][j] << "ㅡ";
        out << d.textDisplay[i][d.getBoardSizeC() - 1];
        out << std::endl << "  ";
        for(int k = 0; k < d.getBoardSizeC() - 1; ++k){
            if(k == 3) {out << "|/ "; continue;}
            if(k == 4) {out << "| \\"; continue;}
            out << "|  ";
        }
        out << "|" << std::endl;
        continue;
        }
        else if(i == d.getBoardSizeR() - 3){
        out << d.getBoardSizeR() - i - 1 << " ";
        for (int j = 0; j < d.getBoardSizeC() - 1; ++j)
            out << d.textDisplay[i][j] << "ㅡ";
        out << d.textDisplay[i][d.getBoardSizeC() - 1];
        out << std::endl << "  ";
        for(int k = 0; k < d.getBoardSizeC() - 1; ++k){
            if(k == 3) {out << "|\\ "; continue;}
            if(k == 4) {out << "| /"; continue;}
            out << "|  ";
        }
        out << "|" << std::endl;
        continue;
        } else if(i == d.getBoardSizeR() - 2){
        out << d.getBoardSizeR() - i - 1 << " ";
        for (int j = 0; j < d.getBoardSizeC() - 1; ++j)
            out << d.textDisplay[i][j] << "ㅡ";
        out << d.textDisplay[i][d.getBoardSizeC() - 1];
        out << std::endl << "  ";
        for(int k = 0; k < d.getBoardSizeC() - 1; ++k){
            if(k == 3) {out << "|/ "; continue;}
            if(k == 4) {out << "| \\"; continue;}
            out << "|  ";
        }
        out << "|" << std::endl;
        continue;
        }
        out << d.getBoardSizeR() - i - 1 << " ";
        for (int j = 0; j < d.getBoardSizeC() - 1; ++j)
            out << d.textDisplay[i][j] << "ㅡ";
        out << d.textDisplay[i][d.getBoardSizeC() - 1];
        out << std::endl << "  ";
        for(int k = 0; k < d.getBoardSizeC() - 1; ++k)
            out << "|  ";
        out << "|" << std::endl; 
    } 
    out << 0 << " ";
    for (int j = 0; j < d.getBoardSizeC() - 1; ++j)
        out << d.textDisplay[d.getBoardSizeR() - 1][j] << "ㅡ";
    out << d.textDisplay[d.getBoardSizeR() - 1][d.getBoardSizeC() - 1];       
    out << std::endl << "  a  b  c  d  e  f  g  h  i";
    return out;
}

BoardDisplay::~BoardDisplay(){
    
}

