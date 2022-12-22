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
        while (true){
            k = random_coordinates(size.x, size.y);
            if(array[k.y][k.x] == '.')
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
    while (true){
        k = random_coordinates(size.x, size.y);
        if(array[k.y][k.x] == '.')
            if(w_or_v == 'l')
                array[k.y][k.x] = 'L';
            else
                array[k.y][k.x] = 'B';
            ent[0] = new avatar(w_or_v,k.x,k.y);
            break;
    }
    
    /* Topotheto se tuxea thesi kai arxikopoio ta werewolves(w) */
    number_werewolves = (size.x * size.y)/15;
    for (i = 1; i < number_werewolves+1; i++){
        while (true){
            k = random_coordinates(size.x, size.y);
            if(array[k.y][k.x] == '.')
                break;
        }
        array[k.y][k.x] = 'w';
        ent[i] = new werewolves(k.x,k.y);
    }
    
    /* Topotheto se tuxea thesi kai arxikopoio ta vampires(v) */
    number_vampires = (size.x * size.y)/15;
    number_entitiese = number_vampires+number_werewolves + 1;
    for (i = number_werewolves+1; i < number_entitiese ; i++){
        while (true){
            k = random_coordinates(size.x, size.y);
            if(array[k.y][k.x] == '.')
                break;
        }
        array[k.y][k.x] = 'v';
        ent[i] = new vampires(k.x,k.y);
    }
    
    /* Topotheto se tuxea thesi to magiko filtro($) */
    while (true){
        k = random_coordinates(size.x, size.y);
        if(array[k.y][k.x] == '.')
            break;
    }
    array[k.y][k.x] = '$';
    
    
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

void map::next_cycle()
{
    char temp, next_d;
    coordinates k;
    // x1 -> pano
    // x2 -> kato
    // x3 -> aristera
    // x4 -> deksia
    int i = 0;
    //for (int i = 0; i < number_entitiese; i++){
        bool x1 = false ,x2 = false ,x3 = false ,x4 = false;
        // elenxoume poies einai oi thesis pou mporei na metakinithi i ontotita
        k = ent[i]->get_coordinate();
        if(k.y != 0)
            if(array[k.y-1][k.x] == '.')
                x1 = true;
        if(k.y != size.y - 1)
            if(array[k.y+1][k.x] == '.')
                x2 = true;
        if(k.x != 0)
            if(array[k.y][k.x-1] == '.')
                x3 = true;
        if(k.x != size.x - 1)
            if(array[k.y][k.x+1] == '.')
                x4 = true;
        
        cout<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<endl;    
        next_d = ent[i]->move(x1,x2,x3,x4);
        
        if(next_d == 'w' || next_d == 'W'){
            temp = array[k.y][k.x];
            array[k.y][k.x] = '.';
            array[k.y-1][k.x] = temp;
            ent[i]->set_coordinate(k.x,k.y-1);
            
        }else if(next_d == 's' || next_d == 'S'){
            temp = array[k.y][k.x];
            array[k.y][k.x] = '.';
            array[k.y+1][k.x] = temp;
            ent[i]->set_coordinate(k.x,k.y+1);
            
        }else if(next_d == 'a' || next_d == 'A'){
            temp = array[k.y][k.x];
            array[k.y][k.x] = '.';
            array[k.y][k.x-1] = temp;
            ent[i]->set_coordinate(k.x-1,k.y);
            
        }else if(next_d == 'd' || next_d == 'D'){
            temp = array[k.y][k.x];
            array[k.y][k.x] = '.';
            array[k.y][k.x+1] = temp;
            ent[i]->set_coordinate(k.x+1,k.y);
        }
    //}
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















