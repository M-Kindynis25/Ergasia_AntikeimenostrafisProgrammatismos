/* main.cpp */
#include <iostream>
#include <time.h>
#include "coordinates.h"
#include "entities.h"
#include "map.h"

//int noe;  // Metritis ontotiton

using namespace std;

int
main ()
{
    srand(time(0));
    
    /* Zeitw tes diastasis apo ton xristi */
    int x,y;
/*    while (true) {
        cout << "Insert Width(x): ";
        cin >> x;
        cout << "Insert Heigth(y): ";
        cin >> y;
        if (x >= 10 && y >= 10 && x <= 100 && y <= 100)
            break;
        cout << "Lathos orismata!!!" << endl << "Oi diastasia prepei na einai megaliteres tou 10 kai mikroteres tou 100" << endl;
    }*/
    x = 10;
    y = 10;
    
    
    
    map m(x,y);
    cout<<m;
    while(true){
        m.next_cycle();
        cout<<m;
    }

    
/*  entities *e[3];
  
    e[0] = new avatar('W',5,5);
    e[1] = new werewolves(5,5);
    e[2] = new vampires(5,5);*/

    return 0;
}
