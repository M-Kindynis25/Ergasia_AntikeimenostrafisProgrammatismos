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

void avatar::move ()
{

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

void werewolves::move()
{
    
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

void vampires::move()
{
    
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





















