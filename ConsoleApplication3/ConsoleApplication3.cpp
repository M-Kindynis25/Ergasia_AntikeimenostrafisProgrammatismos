/* main.cpp */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "coordinates.h"
#include "game.h"
#include "entities.h"

using namespace std;



int main()
{
    srand(time(0));

    bool circle = true;
    game m;

    while (circle) {
        cout << m;
        circle = m.next_step_game();
    }



    return 0;
}
