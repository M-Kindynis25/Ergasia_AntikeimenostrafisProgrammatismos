/* main.cpp */
#include <iostream>
#include <time.h>
#include "coordinates.h"
#include "entities.h"
#include "map.h"



using namespace std;


int
main()
{
    srand(time(0));

    /* Zeitw tes diastasis apo ton xristi */
    int x, y;
    while (true) {
        cout << "Insert Width(x): ";
        cin >> x;
        cout << "Insert Heigth(y): ";
        cin >> y;
        if (x >= 10 && y >= 10 && x <= 100 && y <= 100)
            break;
        cout << "Lathos orismata!!!" << endl << "Oi diastasia prepei na einai megaliteres tou 10 kai mikroteres tou 100" << endl;
    }
    system("cls");

    bool next_game = true;

    map m(x, y);

    while (next_game) {
        system("cls");
        cout << m;
        next_game = m.next_cycle();
    }
    cout << m;

    return 0;
}
















