#include "sculptor.h"

int main(){
    Sculptor s(50,50,50);

    s.setColor(1.0, 0.0, 0.0, 1.0);
    s.putBox( 0, 49, 0, 49, 25, 49);
    s.setColor(1.0, 1.0, 1.0, 1.0);
    s.putBox(0, 49, 0, 49, 0, 25);
    s.setColor(0.0,0.0,0.0,1.0);
    s.putBox(0, 10, 20, 30, 20, 30);
    s.setColor(0.0,0.0,0.0,1.0);
    s.putBox( 0, 49, 0, 49, 23, 27);
    s.setColor(1.0,1.0,1.0,1.0);
    s.putBox(0, 10, 22, 28, 22, 28);


    s.writeOFF("caixateste.off");

    return 0;
}
