/* entities.h */


class entities {
public:
    entities(){ }
    virtual coordinates get_coordinate() = 0;
    virtual bool move(char** g_map, coordinates g_size, int in_d_or_n) { return 0; }
protected:
    coordinates coordinate;

};

class avatar : public entities {
public:
    avatar(coordinates in_coordinate, char in_team);
    coordinates get_coordinate();
    bool move(char** g_map, coordinates g_size, int in_d_or_n);
private:
    int magic_potions;
    char team;
};


class beings : public entities {
public:
    beings();
    virtual coordinates get_coordinate() = 0;
    bool move(char** g_map, coordinates g_size, int in_d_or_n) { return 0; }
protected:
    int health;
    int medical;
    int power;
    int defense;
};

class werewolves : public beings {
public:
    werewolves(coordinates in_coordinate);
    coordinates get_coordinate();
    bool move(char** g_map, coordinates g_size, int in_d_or_n);
private:

};

class vampires : public beings {
public:
    vampires(coordinates in_coordinate);
    coordinates get_coordinate();
    bool move(char** g_map, coordinates g_size, int in_d_or_n);
private:

};
