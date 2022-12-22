/* entities.cpp */
#include <iostream>
#include "coordinates.h"
#include "entities.h"
#include "map.h"

using namespace std;

coordinates random_coordinates(int in_x, int in_y);
int random_number(int min, int max);

/* Avatar */

avatar::avatar (char in_team, int in_x, int in_y)
{
  health_potions = 1;
  coordinate.x = in_x;
  coordinate.y = in_y;
  team = in_team;
  cout << "Created Avatar" << endl;
}

coordinates
avatar::get_coordinate ()
{
  return coordinate;
}

void avatar::set_coordinate (int in_x, int in_y)
{
  coordinate.x = in_x;
  coordinate.y = in_y;
}

char avatar::move (bool a1, bool a2, bool a3, bool a4)
{
    cout<< "Move Avatar" << endl;
    if(a1)
        cout << "Me to pliktro ---W--- o avatar kinite mia thesi panw" << endl;
    if(a2)
        cout << "Me to pliktro ---S--- o avatar kinite mia thesi kato" << endl;
    if(a3)
        cout << "Me to pliktro ---A--- o avatar kinite mia thesi aristera" << endl;
    if(a4)
        cout << "Me to pliktro ---D--- o avatar kinite mia thesi deksia" << endl;
        
    char next_direction;
    while(true){
        cin>>next_direction;
        if((a1 && (next_direction == 'W' || next_direction == 'w')) || (a2 && (next_direction == 'S' || next_direction == 's')) || (a3 && (next_direction == 'A' || next_direction == 'a')) || (a4 && (next_direction == 'D' || next_direction == 'd')))
            break;
        cout<<"Lathos kinisi!!!"<<endl<<"Dwse allo gramma"<<endl;
    }
    
    return next_direction;   
    
}



/* Werewolves */

werewolves::werewolves(int in_x, int in_y)
{
    // Apothikeuw tin arxiki tou thesi
    coordinate.x = in_x;
    coordinate.y = in_y;
    // Arxikopoiw tixea ta basika steixeia tous
    health = 5;
    medical = random_number(0,2);
    power = random_number(1,3);
    defense = random_number(1,2);
    cout << "Created Werewolves" << endl;
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

char werewolves::move(bool a1, bool a2, bool a3, bool a4)
{
    cout<< "Move Werewolves" << endl;
    return 0;
}

/* Vampires */

vampires::vampires(int in_x, int in_y)
{
    // Apothikeuw tin arxiki tou thesi
    coordinate.x = in_x;
    coordinate.y = in_y;
    // Arxikopoiw tixea ta basika steixeia tous
    health = 5;
    medical = random_number(0,2);
    power = random_number(1,3);
    defense = random_number(1,2);
    cout << "Created Vampires" << endl;
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

char vampires::move(bool a1, bool a2, bool a3, bool a4)
{
    cout<< "Move Vampires" << endl;
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





















