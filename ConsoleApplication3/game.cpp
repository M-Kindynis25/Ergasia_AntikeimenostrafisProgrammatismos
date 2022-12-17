/* game.cpp */

#include <iostream>
#include <stdlib.h>
//#include <time.h>
#include <vector>
#include "coordinates.h"
#include "game.h"
#include "entities.h"

using namespace std;

coordinates random_coordinates(int min, int max);
int random_number(int min, int max);



game::game()
{
    /* 1-- DAY */
    /* 2-- NIGHT */
    pl_day_night = random_number(0, 10);
    if (pl_day_night % 10 == 0)
        day_night = 1;

    /* Zeitw tes diastasis apo ton xristi */
    int i, j;
    while (true) {
        int temp = 0;
        cout << "Dwse x: ";
        cin >> temp;
        size.x = temp;
        cout << "Dwse y: ";
        cin >> temp;
        size.y = temp;
        if (size.x >= 10 && size.y >= 10 && size.x <= 100 && size.y <= 100)
            break;
        cout << "Lathos orismata!!!" << endl << "Oi diastasia prepei na einai megaliteres tou 10 kai mikroteres tou 100" << endl;
    }

    /*  */
    map = new char* [size.y];
    for (i = 0; i < size.y; i++)
    {
        map[i] = new char[size.x];
    }

    /*  */
    number_werewolves = (size.x * size.y) / 15;
    number_vampires = (size.x * size.y) / 15;
    number_entitiese = 1 + number_werewolves + number_vampires;


    /* Arxikopio oles tes theseis me gi(.) */
    for (i = 0; i < size.y; i++)
        for (j = 0; j < size.x; j++)
            map[i][j] = '.';

    cout << (size.x * size.y) / 15 << endl;
    cout << (size.x * size.y) / 30 << endl;

    coordinates k;

    /* Topotheto se tuxea thesi ta debtra(D) */
    int number_tree = (size.x * size.y) / 30;
    for (i = 0; i < number_tree; i++)
    {
        k = random_coordinates(size.x, size.y);
        while (map[k.y][k.x] != '.')
            k = random_coordinates(size.x, size.y);

        map[k.y][k.x] = 'D';
    }

    /* Topotheto se tuxea thesi nero-limni(~) */
    int number_lake = (size.x * size.y) / 30;
    for (i = 0; i < number_lake; i++)
    {
        k = random_coordinates(size.x, size.y);
        while (map[k.y][k.x] != '.' && map[k.y][k.x] != 'D')
            k = random_coordinates(size.x, size.y);

        map[k.y][k.x] = '~';
    }

    /* Topotheto se tuxea thesi, zeitw apo ton xristi na epileksi omada kai arxikopoio to avatar(W or V) */
    k = random_coordinates(size.x, size.y);
    while (map[k.y][k.x] != '.' && map[k.y][k.x] != 'D' && map[k.y][k.x] != '~')
        k = random_coordinates(size.x, size.y);

    int w_or_v;
    while (true) {
        cout << "Werewolves---(1)\nVampires-----(2)\nPoio omada upostirizeis:" << endl;
        cin >> w_or_v;
        if (w_or_v == 1 || w_or_v == 2)
            break;
    }
    if (w_or_v == 1) {
        map[k.y][k.x] = 'W';
    }
    else {
        map[k.y][k.x] = 'V';
    }
    ent[0] = new avatar(k, map[k.y][k.x]);
    int n = 1; // Thesi neas ontotitas 

    /* Topotheto se tuxea thesi kai arxikopoio ta werewolves(w) */
    for (i = 0; i < number_werewolves; i++)
    {
        k = random_coordinates(size.x, size.y);
        while (map[k.y][k.x] != '.' && map[k.y][k.x] != 'D' && map[k.y][k.x] != '~' && map[k.y][k.x] != 'V' && map[k.y][k.x] != 'W')
            k = random_coordinates(size.x, size.y);

        map[k.y][k.x] = 'w';
        ent[n] = new werewolves(k);
        n++;
    }

    /* Topotheto se tuxea thesi kai arxikopoio ta vampires(v) */
    for (i = 0; i < number_vampires; i++)
    {
        k = random_coordinates(size.x, size.y);
        while (map[k.y][k.x] != '.' && map[k.y][k.x] != 'D' && map[k.y][k.x] != '~' && map[k.y][k.x] != 'V' && map[k.y][k.x] != 'W' && map[k.y][k.x] != 'w')
            k = random_coordinates(size.x, size.y);

        map[k.y][k.x] = 'v';
        ent[n] = new vampires(k);
        n++;
    }


    /* Topotheto se tuxea thesi to magiko filtro($) */
    k = random_coordinates(size.x, size.y);
    while (map[k.y][k.x] != '.' && map[k.y][k.x] != 'D' && map[k.y][k.x] != '~' && map[k.y][k.x] != 'w' && map[k.y][k.x] != 'v' && map[k.y][k.x] != 'W' && map[k.y][k.x] != 'V')
        k = random_coordinates(size.x, size.y);
    map[k.y][k.x] = '$';
}

game::~game()
{
    for (int i = 0; i < number_entitiese; i++)
        delete ent[i];

    for (int i = 0; i < size.y; i++)
        delete[] map[i];
    delete[] map;
}


bool game::next_step_game()
{
    int i, j, k, e1, e2;
    coordinates c;
    // Orizontia: otan duo onta einai dipla kata ton aksona x
    for (i = 0; i < size.y; i++){
        for (j = 0; j < size.x-1; j++) {
            // idias omadas
            if (map[i][j] == map[i][j + 1]) {
                if (map[i][j] == 'w') {
                    for (k = 1; k <= number_werewolves; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i && c.x == j) 
                            e1 = k;
                        else if (c.y == i && c.x == j + 1)
                            e2 = k;
                    }
                    cout << endl << "idio w sto x aksona" << endl;

                }
                else if (map[i][j] == 'v') {
                    for (k = number_werewolves + 1; k < number_entitiese; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i && c.x == j)
                            e1 = k;
                        else if (c.y == i && c.x == j + 1)
                            e2 = k;
                    }
                    cout << endl << "idio v sto x aksona" << endl;
                }
            
            // antipalis omadas
            }else if ((map[i][j] == 'w' && map[i][j+1] == 'v') || (map[i][j] == 'v' && map[i][j+1] == 'w')) {
                if (map[i][j] == 'w') {
                    for (k = 1; k <= number_werewolves; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = k;
                            break;
                        }                           
                    }
                    for (k = number_werewolves + 1; k < number_entitiese; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i && c.x == j+1) {
                            e2 = k;
                            break;
                        }
                    }
                    cout << endl << "antipaloi w and v sto x aksona   " <<e1<<" "<<e2<< endl;

                }
                else if (map[i][j] == 'v') {
                    for (k = number_werewolves + 1; k < number_entitiese; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = k;
                            break;
                        }
                    }
                    for (k = 1; k <= number_werewolves; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i && c.x == j + 1) {
                            e2 = k;
                            break;
                        }
                    }
                    
                    cout << endl << "antipaloi v and w sto x aksona   " << e1 << " " << e2 << endl;
                }
            }
        }
    }
    // Katheta: otan duo onta einai dipla kata ton aksona y
    for (i = 0; i < size.y-1; i++) {
        for (j = 0; j < size.x; j++) {
            // idias omadas
            if (map[i][j] == map[i+1][j]) {
                if (map[i][j] == 'w') {
                    for (k = 1; k <= number_werewolves; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i && c.x == j)
                            e1 = k;
                        else if (c.y == i + 1 && c.x == j)
                            e2 = k;
                    }
                    cout << endl << "idio w sto y aksona    " << e1 << " " << e2 << endl;
                }
                else if (map[i][j] == 'v') {
                    for (k = number_werewolves + 1; k < number_entitiese; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i && c.x == j)
                            e1 = k;
                        else if (c.y == i + 1 && c.x == j)
                            e2 = k;
                    }
                    cout << endl << "idio v sto y aksona    " << e1 << " " << e2 << endl;
                }
               
            // antipalis omadas
            }else if ((map[i][j] == 'w' && map[i+1][j] == 'v') || (map[i][j] == 'v' && map[i+1][j] == 'w')) {
                if (map[i][j] == 'w') {
                    for (k = 1; k <= number_werewolves; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = k;
                            break;
                        }
                    }
                    for (k = number_werewolves + 1; k < number_entitiese; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i +1 && c.x == j) {
                            e2 = k;
                            break;
                        }
                    }
                    cout << endl << "antipaloi w and v sto y aksona   " << e1 << " " << e2 << endl;
                }
                else if (map[i][j] == 'v') {
                    for (k = number_werewolves + 1; k < number_entitiese; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = k;
                            break;
                        }
                    }
                    for (k = 1; k <= number_werewolves; k++) {
                        c = ent[k]->get_coordinate();
                        if (c.y == i+1 && c.x == j) {
                            e2 = k;
                            break;
                        }                 
                    }
                    cout << endl << "antipaloi v and x sto y aksona   " << e1 << " " << e2 << endl;
                }
            }
        }
    }
    // Diagonia: otan duo onta einai dipla kata ton aksona x*y
    // Mono ta v
    
    /*        */

    /* 1-- DAY */
    /* 2-- NIGHT */
    pl_day_night++;
    if (pl_day_night >= 10) {
        pl_day_night = 0;
        if (day_night == 2)
            day_night = 1;
        else
            day_night = 2;
    }
    bool m = ent[0]->move(map, size, day_night);
    if (!m)
        return false;

    for (i = 1; i < number_entitiese; i++) {
        ent[i]->move(map, size, day_night);
    }

    return true;
}


ostream& operator<<(ostream& left, const game& right)
{
    //system("cls");
    left << endl;
    int i, j;
    for (i = 0; i < right.size.y; i++) {
        for (j = 0; j < right.size.x; j++) {
            left << right.map[i][j] << " ";
        }
        left << endl;
    }

    /* 1-- DAY */
    /* 2-- NIGHT */
    if (right.day_night == 1)
        left << endl << "DAY" << endl;
    else
        left << endl << "NIGHT" << endl;
    return left;
}









coordinates random_coordinates(int in_x, int in_y)
{
    coordinates c;
    c.x = rand() % in_x;
    c.y = rand() % in_y;

    return c;
}

int random_number(int min, int max)
{
    return rand() % (max - min + 1) + min;
}