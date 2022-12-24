/* entities.cpp */
#include <iostream>
#include "coordinates.h"
#include "entities.h"
#include "map.h"

#define MAX_HEIGTH 5;

using namespace std;

coordinates random_coordinates(int in_x, int in_y);
int random_number(int min, int max);

/* Avatar */

avatar::avatar(char in_team, int in_x, int in_y)
{
    health_potions = 1;
    coordinate.x = in_x;
    coordinate.y = in_y;
    team = in_team;
}

coordinates
avatar::get_coordinate()
{
    return coordinate;
}

void avatar::set_coordinate(int in_x, int in_y)
{
    coordinate.x = in_x;
    coordinate.y = in_y;
}

char avatar::move(bool a1, bool a2, bool a3, bool a4, bool a5, bool a6, bool a7, bool a8)
{
    if (!a1 && !a2 && !a3 && !a4)
        return 'b';
    if (a1)
        cout << "Me to pliktro ---W--- o avatar kinite mia thesi panw" << endl;
    if (a2)
        cout << "Me to pliktro ---S--- o avatar kinite mia thesi kato" << endl;
    if (a3)
        cout << "Me to pliktro ---A--- o avatar kinite mia thesi aristera" << endl;
    if (a4)
        cout << "Me to pliktro ---D--- o avatar kinite mia thesi deksia" << endl;

    cout << endl;
    cout << "Me to pliktro ---H--- epoulosi olon ton melon tis omadas sou" << endl;
    cout << "Me to pliktro ---P--- pausi paixnidiou" << endl;
    cout << "Me to pliktro ---O--- telos paixnidiou" << endl;

    char next_direction;
    while (true) {
        cin >> next_direction;
        if ((next_direction == 'P' || next_direction == 'p') || (next_direction == 'O' || next_direction == 'o') || (next_direction == 'H' || next_direction == 'h'))
            return next_direction;
        if ((a1 && (next_direction == 'W' || next_direction == 'w')) || (a2 && (next_direction == 'S' || next_direction == 's')) || (a3 && (next_direction == 'A' || next_direction == 'a')) || (a4 && (next_direction == 'D' || next_direction == 'd')))
            break;
        cout << "Lathos kinisi!!!" << endl << "Dwse allo gramma" << endl;
    }

    return next_direction;

}

int avatar::get_health_potions()
{
    return health_potions;
}

void avatar::set_health_potions(int in_health_potions)
{
    health_potions = in_health_potions;
}

char avatar::get_team()
{
    return team;
}



/* Werewolves */

werewolves::werewolves(int in_x, int in_y)
{
    // Apothikeuw tin arxiki tou thesi
    coordinate.x = in_x;
    coordinate.y = in_y;
    // Arxikopoiw tixea ta basika steixeia tous
    health = MAX_HEIGTH;
    medical = random_number(0, 2);
    power = random_number(1, 3);
    defense = random_number(1, 2);
}

werewolves::~werewolves()
{

}

coordinates werewolves::get_coordinate()
{
    return coordinate;
}

void werewolves::set_coordinate(int in_x, int in_y)
{
    coordinate.x = in_x;
    coordinate.y = in_y;
}
int werewolves::get_health()
{
    return health;
}
void werewolves::set_health(int in_health)
{
    health = in_health;
}
int werewolves::get_medical()
{
    return medical;
}
void werewolves::set_medical(int in_medical)
{
    medical = in_medical;
}
int werewolves::get_power()
{
    return power;
}
void werewolves::set_power(int in_power)
{
    power = in_power;
}
int werewolves::get_defense()
{
    return defense;
}
void werewolves::set_defense(int in_defense)
{
    defense = in_defense;
}

char werewolves::move(bool a1, bool a2, bool a3, bool a4, bool a5, bool a6, bool a7, bool a8)
{
    // epilegi an tha kinithi i tha paraminei stasimos
    if (random_number(1, 2) == 1)
        return 0;

    // An den exei kinisi menei stasimo
    if (!a1 && !a2 && !a3 && !a4)
        return 'b';

    int next;
    int step = 0;
    while (true) {
        next = random_number(1, 4);
        if (a1 == true && next == 1) {
            return 'w';
            break;
        }
        else if (a2 == true && next == 2) {
            return 's';
            break;
        }
        else if (a3 == true && next == 3) {
            return 'a';
            break;
        }
        else if (a4 == true && next == 4) {
            return 'd';
            break;
        }
        if (step > 20)
            break;
        step++;
    }
    return 0;
}

/* Vampires */

vampires::vampires(int in_x, int in_y)
{
    // Apothikeuw tin arxiki tou thesi
    coordinate.x = in_x;
    coordinate.y = in_y;
    // Arxikopoiw tixea ta basika steixeia tous
    health = MAX_HEIGTH;
    medical = random_number(0, 2);
    power = random_number(1, 3);
    defense = random_number(1, 2);
    //number_of_vampires++;
}

vampires::~vampires()
{
    //number_of_vampires--;
}

coordinates vampires::get_coordinate()
{
    return coordinate;
}
void vampires::set_coordinate(int in_x, int in_y)
{
    coordinate.x = in_x;
    coordinate.y = in_y;
}
int vampires::get_health()
{
    return health;
}
void vampires::set_health(int in_health)
{
    health = in_health;
}
int vampires::get_medical()
{
    return medical;
}
void vampires::set_medical(int in_medical)
{
    medical = in_medical;
}
int vampires::get_power()
{
    return power;
}
void vampires::set_power(int in_power)
{
    power = in_power;
}
int vampires::get_defense()
{
    return defense;
}
void vampires::set_defense(int in_defense)
{
    defense = in_defense;
}

char vampires::move(bool a1, bool a2, bool a3, bool a4, bool a5, bool a6, bool a7, bool a8)
{
    // epilegi an tha kinithi i tha paraminei stasimos
    if (random_number(1, 2) == 1)
        return 0;

    // An den exei kinisi menei stasimo
    if (!a1 && !a2 && !a3 && !a4 && !a5 && !a6 && !a7 && !a8)
        return 'b';

    int next;
    int step = 0;
    while (true) {
        next = random_number(1, 8);
        if (a1 == true && next == 1) {
            return 'w';
            break;

        }
        else if (a2 == true && next == 2) {
            return 's';
            break;

        }
        else if (a3 == true && next == 3) {
            return 'a';
            break;

        }
        else if (a4 == true && next == 4) {
            return 'd';
            break;

        }
        else if (a5 == true && next == 5) {
            return 'Q';
            break;

        }
        else if (a6 == true && next == 6) {
            return 'E';
            break;

        }
        else if (a7 == true && next == 7) {
            return 'X';
            break;
        }
        else if (a8 == true && next == 8) {
            return 'Z';
            break;
        }

        if (step > 20)
            break;
        step++;
    }
    return 0;
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





















