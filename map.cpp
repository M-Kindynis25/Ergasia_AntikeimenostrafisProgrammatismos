/* map.cpp */
#include <iostream>
#include "coordinates.h"
#include "entities.h"
#include "map.h"

using namespace std;

coordinates random_coordinates(int in_x, int in_y);
int random_number(int min, int max);


/*    Map     */
map::map(int in_x, int in_y){
    int i, j;
    coordinates k;
    /* 1-- DAY */
    /* 2-- NIGHT */
    if (random_number(1,2) == 1)
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
        k = random_coordinates(size.x, size.y);
        while (true){
            k = random_coordinates(size.x, size.y);
            if(array[k.y][k.x] == '.')
                array[k.y][k.x] = 'D';
                break;
        }
    }

    /* Topotheto se tuxea thesi nero-limni(~) */
    int number_lake = (size.x * size.y) / 30;
    for (i = 0; i < number_lake; i++)
    {
        k = random_coordinates(size.x, size.y);
        while (true){
            k = random_coordinates(size.x, size.y);
            if(array[k.y][k.x] == '.')
                array[k.y][k.x] = '~';
                break;
        };
    }       
 
          
    
    cout<<"Created Map and it is ";
    if(day_night == 1)
        cout<<"day"<<endl;
    else 
        cout<<"night"<<endl;
}

map::~map()
{
    for (int i = 0; i < size.y; i++)
        delete[] array[i];
    delete[] array;
}





ostream& operator<<(ostream& left, const map& right)
{
    //system("cls");
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















