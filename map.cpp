/* map.cpp */
#include <iostream>
#include "coordinates.h"
#include "entities.h"
#include "map.h"

#define MAX_HEIGTH 5;

using namespace std;

coordinates random_coordinates(int in_x, int in_y);
int random_number(int min, int max);
int number_of_entities(char** arr, coordinates s, char entit);


/*    Map     */
map::map(int in_x, int in_y) {
    int i, j;
    coordinates k;
    /* 1-- DAY */
    /* 2-- NIGHT */
    max_day_nigth = 0;
    if (random_number(1, 2) == 1)
        day_night = 1;
    else
        day_night = 2;


    size.x = in_x;
    size.y = in_y;


    array = new char* [size.y];
    for (i = 0; i < size.y; i++)
    {
        array[i] = new char[size.x];
    }

    /* Arxikopio oles tes theseis me gi(.) */
    for (i = 0; i < size.y; i++)
        for (j = 0; j < size.x; j++)
            array[i][j] = '.';

    /* Topotheto se tuxea thesi ta debtra(D) */
    int number_tree = (size.x * size.y) / 30;
    for (i = 0; i < number_tree; i++)
    {
        while (true) {
            k = random_coordinates(size.x, size.y);
            if (array[k.y][k.x] == '.')
                array[k.y][k.x] = 'D';
            break;
        }
    }

    /* Topotheto se tuxea thesi nero-limni(~) */
    int number_lake = (size.x * size.y) / 30;
    for (i = 0; i < number_lake; i++)
    {
        while (true) {
            k = random_coordinates(size.x, size.y);
            if (array[k.y][k.x] == '.')
                array[k.y][k.x] = '~';
            break;
        }
    }

    // Zeitw apo ton xristi na epileksi omada 
    char w_or_v;
    while (true) {
        cout << "Werewolves---(L)\nVampires-----(B)\nPoio omada upostirizeis:" << endl;
        cin >> w_or_v;
        if (w_or_v == 'l' || w_or_v == 'b')
            break;
    }

    /* Topotheto se tuxea thesi ton avatar, kai arxikopoio to avatar(L or B) */
    while (true) {
        k = random_coordinates(size.x, size.y);
        if (array[k.y][k.x] == '.') {
            if (w_or_v == 'l')
                array[k.y][k.x] = 'L';
            else
                array[k.y][k.x] = 'B';
            ent[0] = new avatar(w_or_v, k.x, k.y);
            break;
        }
    }

    /* Topotheto se tuxea thesi kai arxikopoio ta werewolves(w) */
    number_werewolves = (size.x * size.y) / 15;
    for (i = 1; i < number_werewolves + 1; i++) {
        while (true) {
            k = random_coordinates(size.x, size.y);
            if (array[k.y][k.x] == '.')
                break;
        }
        array[k.y][k.x] = 'w';
        ent[i] = new werewolves(k.x, k.y);
    }

    /* Topotheto se tuxea thesi kai arxikopoio ta vampires(v) */
    number_vampires = (size.x * size.y) / 15;
    number_entitiese = number_vampires + number_werewolves + 1;
    for (i = number_werewolves + 1; i < number_entitiese; i++) {
        while (true) {
            k = random_coordinates(size.x, size.y);
            if (array[k.y][k.x] == '.')
                break;
        }
        array[k.y][k.x] = 'v';
        ent[i] = new vampires(k.x, k.y);
    }

    /* Topotheto se tuxea thesi to magiko filtro($) */
    while (true) {
        k = random_coordinates(size.x, size.y);
        if (array[k.y][k.x] == '.')
            break;
    }
    array[k.y][k.x] = '$';


    cout << "Created Map and it is ";
    if (day_night == 1)
        cout << "day" << endl;
    else
        cout << "night" << endl;
}

map::~map()
{
    for (int i = 0; i < size.y; i++)
        delete[] array[i];
    delete[] array;
}


bool map::next_cycle()
{
    int i, j, n, e1, e2, attack;
    coordinates c, h;
    // Orizontia: otan duo onta einai dipla kata ton aksona x
    for (i = 0; i < size.y; i++) {
        for (j = 0; j < size.x - 1; j++) {
            // idias omadas
            if (array[i][j] == array[i][j + 1]) {
                if (array[i][j] == 'w') {
                    for (n = 1; n <= number_werewolves; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j)
                            e1 = n;
                        if (c.y == i && c.x == j + 1)
                            e2 = n;
                    }
                    // Otan den einai plires i zwi tou e1 kai to e2 exei giatriko 
                    // kai episis epilegi tixea an tha dwsi giatriko i oxi
                    if (ent[e1]->get_health() < 5 && ent[e2]->get_medical() > 0 && random_number(1, 2) == 1) {
                        ent[e1]->set_health(ent[e1]->get_health() + 1);//auksano tin zwi tou e1 kata 1
                        ent[e2]->set_medical(ent[e2]->get_medical() - 1);//meionw tin zwi tou e2 kata 1
                    }
                    // Otan den einai plires i zwi tou e2 kai to e1 exei giatriko 
                    // kai episis epilegi tixea an tha dwsi giatriko i oxi
                    if (ent[e2]->get_health() < 5 && ent[e1]->get_medical() > 0 && random_number(1, 2) == 1) {
                        ent[e2]->set_health(ent[e2]->get_health() + 1);//auksano tin zwi tou e2 kata 1
                        ent[e1]->set_medical(ent[e1]->get_medical() - 1);//meionw tin zwi tou e1 kata 1
                    }

                }
                else if (array[i][j] == 'v') {
                    for (n = number_werewolves + 1; n < number_entitiese; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j)
                            e1 = n;
                        if (c.y == i && c.x == j + 1)
                            e2 = n;
                    }
                    // Otan den einai plires i zwi tou e1 kai to e2 exei giatriko 
                    // kai episis epilegi tixea an tha dwsi giatriko i oxi
                    if (ent[e1]->get_health() < 5 && ent[e2]->get_medical() > 0 && random_number(1, 2) == 1) {
                        ent[e1]->set_health(ent[e1]->get_health() + 1);//auksano tin zwi tou e1 kata 1
                        ent[e2]->set_medical(ent[e2]->get_medical() - 1);//meionw tin zwi tou e2 kata 1
                    }
                    // Otan den einai plires i zwi tou e2 kai to e1 exei giatriko 
                    // kai episis epilegi tixea an tha dwsi giatriko i oxi
                    if (ent[e2]->get_health() < 5 && ent[e1]->get_medical() > 0 && random_number(1, 2) == 1) {
                        ent[e2]->set_health(ent[e2]->get_health() + 1);//auksano tin zwi tou e2 kata 1
                        ent[e1]->set_medical(ent[e1]->get_medical() - 1);//meionw tin zwi tou e1 kata 1
                    }
                }


                // antipalis omadas
            }
            else if ((array[i][j] == 'w' && array[i][j + 1] == 'v') || (array[i][j] == 'v' && array[i][j + 1] == 'w')) {
                if (array[i][j] == 'w') {
                    for (n = 1; n <= number_werewolves; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = n;
                            break;
                        }
                    }
                    for (n = number_werewolves + 1; n < number_entitiese; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j + 1) {
                            e2 = n;
                            break;
                        }
                    }
                    if (ent[e1]->get_power() >= ent[e2]->get_power()) {
                        attack = ent[e1]->get_power() - ent[e2]->get_defense();
                        if (attack > 0) {
                            ent[e2]->set_health(ent[e2]->get_health() - attack);
                        }
                        if (ent[e2]->get_health() <= 0) {
                            h = ent[e2]->get_coordinate();
                            array[h.y][h.x] = '.';
                            ent[e2]->set_coordinate(-1, -1);
                        }
                    }
                    if (ent[e2]->get_power() >= ent[e1]->get_power()) {
                        attack = ent[e2]->get_power() - ent[e1]->get_defense();
                        if (attack > 0) {
                            ent[e1]->set_health(ent[e1]->get_health() - attack);
                        }
                        if (ent[e1]->get_health() <= 0) {
                            h = ent[e1]->get_coordinate();
                            array[h.y][h.x] = '.';
                            ent[e1]->set_coordinate(-1, -1);
                        }
                    }

                }
                else if (array[i][j] == 'v') {
                    for (n = number_werewolves + 1; n < number_entitiese; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = n;
                            break;
                        }
                    }
                    for (n = 1; n <= number_werewolves; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j + 1) {
                            e2 = n;
                            break;
                        }
                    }
                    if (ent[e1]->get_power() >= ent[e2]->get_power()) {
                        attack = ent[e1]->get_power() - ent[e2]->get_defense();
                        if (attack > 0) {
                            ent[e2]->set_health(ent[e2]->get_health() - attack);
                        }
                        if (ent[e2]->get_health() <= 0) {
                            h = ent[e2]->get_coordinate();
                            array[h.y][h.x] = '.';
                            ent[e2]->set_coordinate(-1, -1);
                        }
                    }
                    if (ent[e2]->get_power() >= ent[e1]->get_power()) {
                        attack = ent[e2]->get_power() - ent[e1]->get_defense();
                        if (attack > 0) {
                            ent[e1]->set_health(ent[e1]->get_health() - attack);
                        }
                        if (ent[e1]->get_health() <= 0) {
                            h = ent[e1]->get_coordinate();
                            array[h.y][h.x] = '.';
                            ent[e1]->set_coordinate(-1, -1);
                        }
                    }

                }
            }
        }
    }
    // Katheta: otan duo onta einai dipla kata ton aksona y
    for (i = 0; i < size.y - 1; i++) {
        for (j = 0; j < size.x; j++) {
            // idias omadas
            if (array[i][j] == array[i + 1][j]) {
                if (array[i][j] == 'w') {
                    for (n = 1; n <= number_werewolves; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j)
                            e1 = n;
                        if (c.y == i + 1 && c.x == j)
                            e2 = n;
                    }
                    // Otan den einai plires i zwi tou e1 kai to e2 exei giatriko 
                    // kai episis epilegi tixea an tha dwsi giatriko i oxi
                    if (ent[e1]->get_health() < 5 && ent[e2]->get_medical() > 0 && random_number(1, 2) == 1) {
                        ent[e1]->set_health(ent[e1]->get_health() + 1);//auksano tin zwi tou e1 kata 1
                        ent[e2]->set_medical(ent[e2]->get_medical() - 1);//meionw tin zwi tou e2 kata 1
                    }
                    // Otan den einai plires i zwi tou e2 kai to e1 exei giatriko 
                    // kai episis epilegi tixea an tha dwsi giatriko i oxi
                    if (ent[e2]->get_health() < 5 && ent[e1]->get_medical() > 0 && random_number(1, 2) == 1) {
                        ent[e2]->set_health(ent[e2]->get_health() + 1);//auksano tin zwi tou e2 kata 1
                        ent[e1]->set_medical(ent[e1]->get_medical() - 1);//meionw tin zwi tou e1 kata 1
                    }
                }
                else if (array[i][j] == 'v') {
                    for (n = number_werewolves + 1; n < number_entitiese; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j)
                            e1 = n;
                        if (c.y == i + 1 && c.x == j)
                            e2 = n;
                    }
                    // kai episis epilegi tixea an tha dwsi giatriko i oxi
                    if (ent[e1]->get_health() < 5 && ent[e2]->get_medical() > 0 && random_number(1, 2) == 1) {
                        ent[e1]->set_health(ent[e1]->get_health() + 1);//auksano tin zwi tou e1 kata 1
                        ent[e2]->set_medical(ent[e2]->get_medical() - 1);//meionw tin zwi tou e2 kata 1
                    }
                    // Otan den einai plires i zwi tou e2 kai to e1 exei giatriko 
                    // kai episis epilegi tixea an tha dwsi giatriko i oxi
                    if (ent[e2]->get_health() < 5 && ent[e1]->get_medical() > 0 && random_number(1, 2) == 1) {
                        ent[e2]->set_health(ent[e2]->get_health() + 1);//auksano tin zwi tou e2 kata 1
                        ent[e1]->set_medical(ent[e1]->get_medical() - 1);//meionw tin zwi tou e1 kata 1
                    }
                }

                // antipalis omadas
            }
            else if ((array[i][j] == 'w' && array[i + 1][j] == 'v') || (array[i][j] == 'v' && array[i + 1][j] == 'w')) {
                if (array[i][j] == 'w') {
                    for (n = 1; n <= number_werewolves; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = n;
                            break;
                        }
                    }
                    for (n = number_werewolves + 1; n < number_entitiese; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i + 1 && c.x == j) {
                            e2 = n;
                            break;
                        }
                    }
                    if (ent[e1]->get_power() >= ent[e2]->get_power()) {
                        attack = ent[e1]->get_power() - ent[e2]->get_defense();
                        if (attack > 0) {
                            ent[e2]->set_health(ent[e2]->get_health() - attack);
                        }
                        if (ent[e2]->get_health() <= 0) {
                            h = ent[e2]->get_coordinate();
                            array[h.y][h.x] = '.';
                            ent[e2]->set_coordinate(-1, -1);
                        }
                    }
                    if (ent[e2]->get_power() >= ent[e1]->get_power()) {
                        attack = ent[e2]->get_power() - ent[e1]->get_defense();
                        if (attack > 0) {
                            ent[e1]->set_health(ent[e1]->get_health() - attack);
                        }
                        if (ent[e1]->get_health() <= 0) {
                            h = ent[e1]->get_coordinate();
                            array[h.y][h.x] = '.';
                            ent[e1]->set_coordinate(-1, -1);
                        }
                    }
                }
                else if (array[i][j] == 'v') {
                    for (n = number_werewolves + 1; n < number_entitiese; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = n;
                            break;
                        }
                    }
                    for (n = 1; n <= number_werewolves; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i + 1 && c.x == j) {
                            e2 = n;
                            break;
                        }
                    }
                    if (ent[e1]->get_power() >= ent[e2]->get_power()) {
                        attack = ent[e1]->get_power() - ent[e2]->get_defense();
                        if (attack > 0) {
                            ent[e2]->set_health(ent[e2]->get_health() - attack);
                        }
                        if (ent[e2]->get_health() <= 0) {
                            h = ent[e2]->get_coordinate();
                            array[h.y][h.x] = '.';
                            ent[e2]->set_coordinate(-1, -1);
                        }
                    }
                    if (ent[e2]->get_power() >= ent[e1]->get_power()) {
                        attack = ent[e2]->get_power() - ent[e1]->get_defense();
                        if (attack > 0) {
                            ent[e1]->set_health(ent[e1]->get_health() - attack);
                        }
                        if (ent[e1]->get_health() <= 0) {
                            h = ent[e1]->get_coordinate();
                            array[h.y][h.x] = '.';
                            ent[e1]->set_coordinate(-1, -1);
                        }
                    }
                }
            }
        }
    }
    // Diagonia: otan duo onta einai dipla kata ton aksona x*y
    // Mono ta v
    for (i = 0; i < size.y - 1; i++) {
        for (j = 0; j < size.x - 1; j++) {
            // idias omadas
            if (array[i][j] == array[i + 1][j + 1] && array[i][j] == 'v') {
                for (n = number_werewolves + 1; n < number_entitiese; n++) {
                    c = ent[n]->get_coordinate();
                    if (c.y == i && c.x == j)
                        e1 = n;
                    if (c.y == i + 1 && c.x == j + 1)
                        e2 = n;
                }
                // Otan den einai plires i zwi tou e1 kai to e2 exei giatriko 
                // kai episis epilegi tixea an tha dwsi giatriko i oxi
                int hhh = ent[e1]->get_health();
                int mmm = ent[e2]->get_medical();
                if (hhh < 5 && mmm > 0 && random_number(1, 2) == 1) {
                    ent[e1]->set_health(ent[e1]->get_health() + 1);//auksano tin zwi tou e1 kata 1
                    ent[e2]->set_medical(ent[e2]->get_medical() - 1);//meionw tin zwi tou e2 kata 1
                }
                // Otan den einai plires i zwi tou e2 kai to e1 exei giatriko 
                // kai episis epilegi tixea an tha dwsi giatriko i oxi
                if (ent[e2]->get_health() < 5 && ent[e1]->get_medical() > 0 && random_number(1, 2) == 1) {
                    ent[e2]->set_health(ent[e2]->get_health() + 1);//auksano tin zwi tou e2 kata 1
                    ent[e1]->set_medical(ent[e1]->get_medical() - 1);//meionw tin zwi tou e1 kata 1
                }

            }
            else if ((array[i][j] == 'w' && array[i + 1][j + 1] == 'v') || (array[i][j] == 'v' && array[i + 1][j + 1] == 'w')) {
                if (array[i][j] == 'w') {
                    for (n = 1; n <= number_werewolves; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = n;
                            break;
                        }
                    }
                    for (n = number_werewolves + 1; n < number_entitiese; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i + 1 && c.x == j + 1) {
                            e2 = n;
                            break;
                        }
                    }
                    if (ent[e1]->get_power() >= ent[e2]->get_power()) {
                        attack = ent[e1]->get_power() - ent[e2]->get_defense();
                        if (attack > 0) {
                            ent[e2]->set_health(ent[e2]->get_health() - attack);
                        }
                        if (ent[e2]->get_health() <= 0) {
                            h = ent[e2]->get_coordinate();
                            array[h.y][h.x] = '.';
                            ent[e2]->set_coordinate(-1, -1);
                        }
                    }

                }
                else if (array[i][j] == 'v') {
                    for (n = number_werewolves + 1; n < number_entitiese; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = n;
                            break;
                        }
                    }
                    for (n = 1; n <= number_werewolves; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i + 1 && c.x == j + 1) {
                            e2 = n;
                            break;
                        }
                    }
                    if (ent[e1]->get_power() >= ent[e2]->get_power()) {
                        attack = ent[e1]->get_power() - ent[e2]->get_defense();
                        if (attack > 0) {
                            ent[e2]->set_health(ent[e2]->get_health() - attack);
                        }
                        if (ent[e2]->get_health() <= 0) {
                            h = ent[e2]->get_coordinate();
                            array[h.y][h.x] = '.';
                            ent[e2]->set_coordinate(-1, -1);
                        }
                    }
                }
            }
        }
    }
    // Diagonia: otan duo onta einai dipla kata ton aksona x*(-y)
    // Mono ta v
    for (i = 1; i < size.y; i++) {
        for (j = 0; j < size.x - 1; j++) {
            // idias omadas
            if (array[i][j] == array[i - 1][j + 1] && array[i][j] == 'v') {
                for (n = number_werewolves + 1; n < number_entitiese; n++) {
                    c = ent[n]->get_coordinate();
                    if (c.y == i && c.x == j)
                        e1 = n;
                    else if (c.y == i - 1 && c.x == j + 1)
                        e2 = n;
                }
                // Otan den einai plires i zwi tou e1 kai to e2 exei giatriko 
                // kai episis epilegi tixea an tha dwsi giatriko i oxi
                if (ent[e1]->get_health() < 5 && ent[e2]->get_medical() > 0 && random_number(1, 2) == 1) {
                    ent[e1]->set_health(ent[e1]->get_health() + 1);//auksano tin zwi tou e1 kata 1
                    ent[e2]->set_medical(ent[e2]->get_medical() - 1);//meionw tin zwi tou e2 kata 1
                }
                // Otan den einai plires i zwi tou e2 kai to e1 exei giatriko 
                // kai episis epilegi tixea an tha dwsi giatriko i oxi
                if (ent[e2]->get_health() < 5 && ent[e1]->get_medical() > 0 && random_number(1, 2) == 1) {
                    ent[e2]->set_health(ent[e2]->get_health() + 1);//auksano tin zwi tou e2 kata 1
                    ent[e1]->set_medical(ent[e1]->get_medical() - 1);//meionw tin zwi tou e1 kata 1
                }

            }
            else if ((array[i][j] == 'w' && array[i - 1][j + 1] == 'v') || (array[i][j] == 'v' && array[i - 1][j + 1] == 'w')) {
                if (array[i][j] == 'w') {
                    for (n = 1; n <= number_werewolves; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = n;
                            break;
                        }
                    }
                    for (n = number_werewolves + 1; n < number_entitiese; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i - 1 && c.x == j + 1) {
                            e2 = n;
                            break;
                        }
                    }
                    if (ent[e1]->get_power() >= ent[e2]->get_power()) {
                        attack = ent[e1]->get_power() - ent[e2]->get_defense();
                        if (attack > 0) {
                            ent[e2]->set_health(ent[e2]->get_health() - attack);
                        }
                        if (ent[e2]->get_health() <= 0) {
                            h = ent[e2]->get_coordinate();
                            array[h.y][h.x] = '.';
                        }
                    }

                }
                else if (array[i][j] == 'v') {
                    for (n = number_werewolves + 1; n < number_entitiese; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i && c.x == j) {
                            e1 = n;
                            break;
                        }
                    }
                    for (n = 1; n <= number_werewolves; n++) {
                        c = ent[n]->get_coordinate();
                        if (c.y == i - 1 && c.x == j + 1) {
                            e2 = n;
                            break;
                        }
                    }
                    if (ent[e1]->get_power() >= ent[e2]->get_power()) {
                        attack = ent[e1]->get_power() - ent[e2]->get_defense();
                        if (attack > 0) {
                            ent[e2]->set_health(ent[e2]->get_health() - attack);
                        }
                        if (ent[e2]->get_health() <= 0) {
                            h = ent[e2]->get_coordinate();
                            array[h.y][h.x] = '.';
                        }
                    }
                }
            }
        }
    }


    if (number_of_entities(array, size, 'v') == 0) {
        cout << "WEREWOLVES NIKITES" << endl;
        return false;
    }
    if (number_of_entities(array, size, 'w') == 0) {
        cout << "VAMPIRES NIKITES" << endl;
        return false;
    }

    char temp, next_d;
    coordinates k;
    // x1 -> pano(W)
    // x2 -> kato(S)
    // x3 -> aristera(A)
    // x4 -> deksia(D)
    // x5 -> pano aristera(Q)
    // x6 -> pano deksia(E)
    // x7 -> kato deksia(X)
    // x8 -> kato aristera(Z)
    for (int i = 0; i < number_entitiese; i++) {
        //  prepri na exei zoi i ontotita gia na metekinithi, ektos an einai o avatar
        if (i == 0 || ent[i]->get_health() > 0) {
            bool x1 = false, x2 = false, x3 = false, x4 = false, x5 = false, x6 = false, x7 = false, x8 = false;
            k = ent[i]->get_coordinate();
            // Otan i ontotita diagraftike
            if (k.y == -1 || k.x == -1) {
                cout << "lathos ontotita" << endl;
                break;
            }
            // elenxoume poies einai oi thesis pou mporei na metakinithi i ontotita
            // opou i=0 ara sto avatar ipologizw kai tin periptosi pou exei dipla magiko filtro
            if (k.y != 0)
                if (array[k.y - 1][k.x] == '.' || (array[k.y - 1][k.x] == '$' && i == 0))
                    x1 = true;                                                              // W
            if (k.y != size.y - 1)
                if (array[k.y + 1][k.x] == '.' || (array[k.y + 1][k.x] == '$' && i == 0))
                    x2 = true;                                                              // S
            if (k.x != 0)
                if (array[k.y][k.x - 1] == '.' || (array[k.y][k.x - 1] == '$' && i == 0))
                    x3 = true;                                                              // A
            if (k.x != size.x - 1)
                if (array[k.y][k.x + 1] == '.' || (array[k.y][k.x + 1] == '$' && i == 0))
                    x4 = true;                                                              // D

            if (i > number_werewolves) {
                if (k.y != 0 && k.x != 0)
                    if (array[k.y - 1][k.x - 1] == '.')
                        x5 = true;                                                          // Q
                if (k.y != 0 && k.x != size.x - 1)
                    if (array[k.y - 1][k.x + 1] == '.')
                        x6 = true;                                                          // E
                if (k.y != size.y - 1 && k.x != size.x - 1)
                    if (array[k.y + 1][k.x + 1] == '.')
                        x7 = true;                                                         // X
                if (k.y != size.y - 1 && k.x != 0)
                    if (array[k.y + 1][k.x - 1] == '.')
                        x8 = true;                                                          // Z
            }

            // Sto avatar kai sta werewolves i move pernei tesera orirmata 
            // enw sta vampires perni 8
            // analoga me tes poses kinisis mporei na kani h kathe ontotita
            if (i < number_werewolves + 1)
                next_d = ent[i]->move(x1, x2, x3, x4);
            else
                next_d = ent[i]->move(x1, x2, x3, x4, x5, x6, x7, x8);

            /*   Otan to paixnidi tethte se pausi */
            if (i == 0 && (next_d == 'p' || next_d == 'P')) {
                cout << "To paixnidi tethike se pausi!!!" << endl << endl << endl;
                cout << "Magika filtra: " << ent[i]->get_health_potions() << endl;
                /*    na tiponi ton arithno ton werewolves   */
                cout << "Numder of Werewolves: " << number_of_entities(array, size, 'w') << endl;
                /*     na tiponi ton arithno ton vampires    */
                cout << "Numder of Vampires: " << number_of_entities(array, size, 'v') << endl;
                cout << endl << endl << endl;
                while (true) {
                    char m;
                    cout << "Me to pliktro ---P--- sinexeia paixnidiou" << endl;
                    cout << "Me to pliktro ---O--- telos paixnidiou" << endl;
                    cin >> m;
                    if (m == 'O' || m == 'o')
                        return false;
                    if (m == 'P' || m == 'p')
                        break;
                    cout << "To paixnidi einai se pausi!!!" << endl;
                }
                return true;
            }

            if (i == 0 && (next_d == 'o' || next_d == 'O')) {
                return false;
            }

            if (next_d == 'b') {
                break;
            }

            if (i == 0 && (next_d == 'h' || next_d == 'H')) {
                if (ent[i]->get_health_potions() > 0) {
                    if (day_night == 1 && ent[i]->get_team() == 'b') {
                        ent[i]->set_health_potions(ent[i]->get_health_potions() - 1);
                        for (int n = number_werewolves + 1; n < number_entitiese; n++) {
                            if (ent[n]->get_health() > 0 && ent[n]->get_health() < 5) {
                                ent[n]->set_health(ent[n]->get_health() + 1);
                            }
                        }
                        cout << "Epouloni tous Werewolves" << endl;

                    }
                    else if (day_night == 2 && ent[i]->get_team() == 'l') {
                        ent[i]->set_health_potions(ent[i]->get_health_potions() - 1);
                        for (int n = 1; n <= number_werewolves; n++) {
                            if (ent[n]->get_health() > 0 && ent[n]->get_health() < 5) {
                                ent[n]->set_health(ent[n]->get_health() + 1);
                            }
                        }
                        cout << "Epouloni ta Vampires" << endl;
                    }
                    else {
                        cout << "Lathos periodos" << endl;
                    }
                }
                else {
                    cout << "DEN exete mafika filtra" << endl;
                }
                break;
            }

            if (next_d == 'w' || next_d == 'W') {
                // Otan einai magiko filtro tote kalo tin sinasrisi 
                if (i == 0 && array[k.y - 1][k.x] == '$') {
                    ent[i]->set_health_potions((ent[i]->get_health_potions()) + 1);
                }
                temp = array[k.y][k.x];
                array[k.y][k.x] = '.';
                array[k.y - 1][k.x] = temp;
                ent[i]->set_coordinate(k.x, k.y - 1);

            }
            else if (next_d == 's' || next_d == 'S') {
                // Otan einai magiko filtro tote kalo tin sinasrisi 
                if (i == 0 && array[k.y + 1][k.x] == '$') {
                    ent[i]->set_health_potions((ent[i]->get_health_potions()) + 1);
                }
                temp = array[k.y][k.x];
                array[k.y][k.x] = '.';
                array[k.y + 1][k.x] = temp;
                ent[i]->set_coordinate(k.x, k.y + 1);

            }
            else if (next_d == 'a' || next_d == 'A') {
                // Otan einai magiko filtro tote kalo tin sinasrisi 
                if (i == 0 && array[k.y][k.x - 1] == '$') {
                    ent[i]->set_health_potions((ent[i]->get_health_potions()) + 1);
                }
                temp = array[k.y][k.x];
                array[k.y][k.x] = '.';
                array[k.y][k.x - 1] = temp;
                ent[i]->set_coordinate(k.x - 1, k.y);

            }
            else if (next_d == 'd' || next_d == 'D') {
                // Otan einai magiko filtro tote kalo tin sinasrisi 
                if (i == 0 && array[k.y][k.x + 1] == '$') {
                    ent[i]->set_health_potions((ent[i]->get_health_potions()) + 1);
                }
                temp = array[k.y][k.x];
                array[k.y][k.x] = '.';
                array[k.y][k.x + 1] = temp;
                ent[i]->set_coordinate(k.x + 1, k.y);

            }
            else if (next_d == 'Q') {
                temp = array[k.y][k.x];
                array[k.y][k.x] = '.';
                array[k.y - 1][k.x - 1] = temp;
                ent[i]->set_coordinate(k.x - 1, k.y - 1);

            }
            else if (next_d == 'E') {
                temp = array[k.y][k.x];
                array[k.y][k.x] = '.';
                array[k.y - 1][k.x + 1] = temp;
                ent[i]->set_coordinate(k.x + 1, k.y - 1);

            }
            else if (next_d == 'X') {
                temp = array[k.y][k.x];
                array[k.y][k.x] = '.';
                array[k.y + 1][k.x + 1] = temp;
                ent[i]->set_coordinate(k.x + 1, k.y + 1);

            }
            else if (next_d == 'Z') {
                temp = array[k.y][k.x];
                array[k.y][k.x] = '.';
                array[k.y + 1][k.x - 1] = temp;
                ent[i]->set_coordinate(k.x - 1, k.y + 1);
            }
        }
    }


    /*  Alagi meras me nixta kai to antitheto  */
    if (max_day_nigth == 10) {
        max_day_nigth = 0;
        if (day_night == 1)
            day_night = 2;
        else
            day_night = 1;
    }
    max_day_nigth++;
    return true;
}



ostream& operator<<(ostream& left, const map& right)
{
    left << endl;
    int i, j;
    for (i = 0; i < right.size.y; i++) {
        for (j = 0; j < right.size.x; j++) {
            left << right.array[i][j] << " ";
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




int number_of_entities(char** arr, coordinates s, char entit) {
    int i, j, sum = 0;
    for (i = 0; i < s.y; i++)
        for (j = 0; j < s.x; j++)
            if (arr[i][j] == entit)
                sum++;

    return sum;
}













