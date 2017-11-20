#include <iostream>
#include <time.h>
#include <memory>
#include <conio.h>
#include "GameMode.h"

using namespace std;



int main() {
    srand(time(NULL));


    GameMode game;
    game.start();
    
    return 0;
}