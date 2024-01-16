#ifndef __BOARD_DISPLAY_H__
#define __BOARD_DISPLAY_H__
#include "observer.h"
#include "window.h"
#include <vector>

class BoardDisplay final: public Observer {
    int boardSizeR;
    int boardSizeC;
    std::vector<std::vector<char>> textDisplay;
    Xwindow graphicsDisplay;
public:
    explicit BoardDisplay(int sizeR, int sizeC);
    int getBoardSizeR() const;
    int getBoardSizeC() const;
    virtual void update(Vertex &vertex) override;
    friend std::ostream &operator<<(std::ostream &out, BoardDisplay &d);
    void Display();
    ~BoardDisplay();
};

#endif
