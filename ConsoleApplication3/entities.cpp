/* entities.cpp */

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

/*    AVATAR     */

avatar::avatar(coordinates in_coordinate, char in_team)
{
    coordinate = in_coordinate;
    magic_potions = 1;
    team = in_team;
}

bool avatar::move(char** g_map, coordinates g_size, int in_d_or_n)
{
    char next_step;
    cout << "Magika Filtra = " << magic_potions << endl << endl;

    if (coordinate.y != 0)
        cout << "Me to pliktro ---W--- o avatar kinite mia thesi panw" << endl;
    if (coordinate.y != g_size.y - 1)
        cout << "Me to pliktro ---S--- o avatar kinite mia thesi kato" << endl;
    if (coordinate.x != 0)
        cout << "Me to pliktro ---A--- o avatar kinite mia thesi aristera" << endl;
    if (coordinate.x != g_size.x - 1)
        cout << "Me to pliktro ---D--- o avatar kinite mia thesi deksia" << endl;

    cout << "Me to pliktro ---1--- termatizei to paixnidi" << endl;
    cout << "Me to pliktro ---T--- kaneis tin idiki sou" << endl;

    while (true) {
        next_step = '0';
        cin >> next_step;
        if (next_step == 't') {
            if (team == 'V' && in_d_or_n == 1 && magic_potions > 0) {
                cout << "Magili epouloso olon ton melon tis omadas ton Vampires" << endl;
                magic_potions--;
                /*     */

            }
            else if (team == 'W' && in_d_or_n == 2 && magic_potions > 0) {
                cout << "Magili epouloso olon ton melon tis omadas ton Werewolves" << endl;
                magic_potions--;
                /*     */
            }
            continue;
        }
        if ((coordinate.y != 0 && next_step == 'w') || (coordinate.y != g_size.y - 1 && next_step == 's') || (coordinate.x != 0 && next_step == 'a') || (coordinate.x != g_size.x - 1 && next_step == 'd') || next_step == '1' || next_step == 't')
            break;
    }

    if (next_step == '1')
        return false;

    int i = 0;
    if (coordinate.y != 0) {
        if ((g_map[coordinate.y - 1][coordinate.x] == '.' || g_map[coordinate.y - 1][coordinate.x] == '$') && next_step == 'w') {
            if (g_map[coordinate.y - 1][coordinate.x] == '$')
                i++;
            g_map[coordinate.y][coordinate.x] = '.';
            g_map[coordinate.y - 1][coordinate.x] = team;
            coordinate.y = coordinate.y - 1;
        }
    }
    if (coordinate.y != g_size.y - 1) {
        if ((g_map[coordinate.y + 1][coordinate.x] == '.' || g_map[coordinate.y + 1][coordinate.x] == '$') && next_step == 's') {
            if (g_map[coordinate.y + 1][coordinate.x] == '$')
                i++;
            g_map[coordinate.y][coordinate.x] = '.';
            g_map[coordinate.y + 1][coordinate.x] = team;
            coordinate.y = coordinate.y + 1;
        }
    }
    if (coordinate.x != 0) {
        if ((g_map[coordinate.y][coordinate.x - 1] == '.' || g_map[coordinate.y][coordinate.x - 1] == '$') && next_step == 'a') {
            if (g_map[coordinate.y][coordinate.x - 1] == '$')
                i++;
            g_map[coordinate.y][coordinate.x] = '.';
            g_map[coordinate.y][coordinate.x - 1] = team;
            coordinate.x = coordinate.x - 1;
        }
    }
    if (coordinate.x != g_size.x - 1) {
        if ((g_map[coordinate.y][coordinate.x + 1] == '.' || g_map[coordinate.y][coordinate.x + 1] == '$') && next_step == 'd') {
            if (g_map[coordinate.y][coordinate.x + 1] == '$')
                i++;
            g_map[coordinate.y][coordinate.x] = '.';
            g_map[coordinate.y][coordinate.x + 1] = team;
            coordinate.x = coordinate.x + 1;
        }
    }



    if (i == 1) {
        magic_potions++;
        /* Topotheto se tuxea thesi to magiko filtro($) */
        coordinates k;
        k = random_coordinates(g_size.x, g_size.y);
        while (g_map[k.y][k.x] != '.' && g_map[k.y][k.x] != 'D' && g_map[k.y][k.x] != '~' && g_map[k.y][k.x] != 'w' && g_map[k.y][k.x] != 'v' && g_map[k.y][k.x] != 'W' && g_map[k.y][k.x] != 'V')
            k = random_coordinates(g_size.x, g_size.y);
        g_map[k.y][k.x] = '$';
    }

    return true;
}

/*     BEINGS     */

beings::beings()
{
    health = 5;
    medical = random_number(0, 2);
    power = random_number(1, 3);
    defense = random_number(1, 2);
}

/*     WEREWOLVES     */

werewolves::werewolves(coordinates in_coordinate)
{
    coordinate = in_coordinate;
}

bool werewolves::move(char** g_map, coordinates g_size, int in_d_or_n)
{
    // Me to 1 meni stethori i ontotita
    // Me to 2 keinite h ontotita
    if (random_number(1, 2) == 1)
        return true;

    int i = 0, pl;

    while (true) {
        i++;
        // Se periptosi pou den vri kinisi meta apo 15 prospathies 
        // Tote meni akoinito
        if (i > 15) {
            pl = 5;
            break;
        }
        pl = random_number(1, 4);
        if (coordinate.y != 0 && g_map[coordinate.y - 1][coordinate.x] == '.' && pl == 1)
            break;
        if (coordinate.y != g_size.y - 1 && g_map[coordinate.y + 1][coordinate.x] == '.' && pl == 2)
            break;
        if (coordinate.x != 0 && g_map[coordinate.y][coordinate.x - 1] == '.' && pl == 3)
            break;
        if (coordinate.x != g_size.x - 1 && g_map[coordinate.y][coordinate.x + 1] == '.' && pl == 4)
            break;
    }

    switch (pl) {
        // pano
    case 1:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y - 1][coordinate.x] = 'w';
        coordinate.y = coordinate.y - 1;
        break;

        // kato
    case 2:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y + 1][coordinate.x] = 'w';
        coordinate.y = coordinate.y + 1;
        break;

        // aristera   
    case 3:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y][coordinate.x - 1] = 'w';
        coordinate.x = coordinate.x - 1;
        break;

    case 4:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y][coordinate.x + 1] = 'w';
        coordinate.x = coordinate.x + 1;
        break;

    default:
        break;
    }


    return true;
}


/*     VAMPIRES     */

vampires::vampires(coordinates in_coordinate)
{
    coordinate = in_coordinate;
}

bool vampires::move(char** g_map, coordinates g_size, int in_d_or_n)
{
    // Me to 1 meni stethori i ontotita
    // Me to 2 keinite h ontotita
    if (random_number(1, 2) == 1)
        return true;

    int i = 0, pl;

    while (true) {
        i++;
        // Se periptosi pou den vri kinisi meta apo 25 prospathies 
        // Tote meni akoinito
        if (i > 25) {
            pl = 5;
            break;
        }
        pl = random_number(1, 8);
        if (coordinate.y != 0)
            if (g_map[coordinate.y - 1][coordinate.x] == '.' && pl == 1)               // 1
                break;
        if (coordinate.y != g_size.y - 1)
            if (g_map[coordinate.y + 1][coordinate.x] == '.' && pl == 2)               // 2
                break;
        if (coordinate.x != 0)
            if (g_map[coordinate.y][coordinate.x - 1] == '.' && pl == 3)               // 3
                break;
        if (coordinate.x != g_size.x - 1)
            if (g_map[coordinate.y][coordinate.x + 1] == '.' && pl == 4)               // 4
                break;
        if (coordinate.y != 0 && coordinate.x != 0)
            if (g_map[coordinate.y - 1][coordinate.x - 1] == '.' && pl == 5)             // 5 = 1 & 3
                break;
        if (coordinate.y != 0 && coordinate.x != g_size.x - 1)
            if (g_map[coordinate.y - 1][coordinate.x + 1] == '.' && pl == 6)             // 6 = 1 & 4
                break;
        if (coordinate.y != g_size.y - 1 && coordinate.x != g_size.x - 1)
            if (g_map[coordinate.y + 1][coordinate.x + 1] == '.' && pl == 7)         // 7 = 2 & 4
                break;
        if (coordinate.y != g_size.y - 1 && coordinate.x != 0)
            if (g_map[coordinate.y + 1][coordinate.x - 1] == '.' && pl == 8)             // 8 = 2 & 3
                break;
    }

    switch (pl) {
        // pano
    case 1:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y - 1][coordinate.x] = 'v';
        coordinate.y = coordinate.y - 1;
        break;

        // kato
    case 2:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y + 1][coordinate.x] = 'v';
        coordinate.y = coordinate.y + 1;
        break;

        // aristera   
    case 3:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y][coordinate.x - 1] = 'v';
        coordinate.x = coordinate.x - 1;
        break;

        // deksia  
    case 4:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y][coordinate.x + 1] = 'v';
        coordinate.x = coordinate.x + 1;
        break;

        // pano deksia
    case 5:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y - 1][coordinate.x - 1] = 'v';
        coordinate.x = coordinate.x - 1;
        coordinate.y = coordinate.y - 1;
        break;

        // pano aristera
    case 6:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y - 1][coordinate.x + 1] = 'v';
        coordinate.x = coordinate.x + 1;
        coordinate.y = coordinate.y - 1;
        break;

        // kato aristera
    case 7:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y + 1][coordinate.x + 1] = 'v';
        coordinate.x = coordinate.x + 1;
        coordinate.y = coordinate.y + 1;
        break;

        // kato deksia
    case 8:
        g_map[coordinate.y][coordinate.x] = '.';
        g_map[coordinate.y + 1][coordinate.x - 1] = 'v';
        coordinate.x = coordinate.x - 1;
        coordinate.y = coordinate.y + 1;
        break;

    default:
        break;
    }

    return true;
}






















