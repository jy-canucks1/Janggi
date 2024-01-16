#include "game.h"
#include "gameonline.h"
using namespace std;

int main() {
    while(true){
    cout << "Play Online? (y / n) or Quit(q) ";
    string s;
    cin >> s;
    
    if(s == "n"){
    Game janggi;
    janggi.start();
    } else if(s == "y"){
        Gameonline janggionline;
        janggionline.start();
    } else if(!cin || s == "q")
        return 0;
    else {
        cout << "choose y or n"<< endl;
        continue;
        }
        return 0;
    }
}
