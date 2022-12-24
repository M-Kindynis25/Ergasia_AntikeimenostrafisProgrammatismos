/* entities.h */

class entities {
public:
    virtual char move(bool a1, bool a2, bool a3, bool a4, bool a5 = false, bool a6 = false, bool a7 = false, bool a8 = false) = 0;
    virtual coordinates get_coordinate() = 0;
    virtual void set_coordinate(int in_x, int in_y) = 0;
    virtual int get_health_potions() = 0;
    virtual void set_health_potions(int in_health_potions) = 0;
    virtual char get_team() = 0;
    virtual int get_health() = 0;
    virtual void set_health(int in_health) = 0;
    virtual int get_medical() = 0;
    virtual void set_medical(int in_medical) = 0;
    virtual int get_power() = 0;
    virtual void set_power(int in_power) = 0;
    virtual int get_defense() = 0;
    virtual void set_defense(int in_defense) = 0;
protected:
    coordinates coordinate;
};


class avatar : public entities {
public:
    avatar(char in_team, int in_x, int in_y);
    coordinates get_coordinate();
    void set_coordinate(int in_x, int in_y);
    char move(bool a1, bool a2, bool a3, bool a4, bool a5 = false, bool a6 = false, bool a7 = false, bool a8 = false);
    int get_health_potions();
    void set_health_potions(int in_health_potions);
    char get_team();
    virtual int get_health() { return 1; }
    virtual void set_health(int in_health) {}
    virtual int get_medical() { return 1; }
    virtual void set_medical(int in_medical) {}
    virtual int get_power() { return 1; }
    virtual void set_power(int in_power) {}
    virtual int get_defense() { return 1; }
    virtual void set_defense(int in_defense) {}
private:
    int health_potions;
    char team;
};

class npc : public entities {
public:
    virtual int get_health_potions() = 0;
    virtual void set_health_potions(int in_health_potions) = 0;
    virtual char get_team() = 0;
    virtual int get_health() = 0;
    virtual void set_health(int in_health) = 0;
    virtual int get_medical() = 0;
    virtual void set_medical(int in_medical) = 0;
    virtual int get_power() = 0;
    virtual void set_power(int in_power) = 0;
    virtual int get_defense() = 0;
    virtual void set_defense(int in_defense) = 0;
protected:
    int health;
    int medical;
    int power;
    int defense;
};

class werewolves : public npc {
public:
    werewolves(int in_x, int in_y);
    ~werewolves();
    coordinates get_coordinate();
    void set_coordinate(int in_x, int in_y);
    char move(bool a1, bool a2, bool a3, bool a4, bool a5 = false, bool a6 = false, bool a7 = false, bool a8 = false);
    int get_health_potions() { return 0; }
    virtual char get_team() { return 0; }
    void set_health_potions(int in_health_potions) {}
    int get_health();
    void set_health(int in_health);
    int get_medical();
    void set_medical(int in_medical);
    int get_power();
    void set_power(int in_power);
    int get_defense();
    void set_defense(int in_defense);
private:

};


class vampires : public npc {
public:
    vampires(int in_x, int in_y);
    ~vampires();
    coordinates get_coordinate();
    void set_coordinate(int in_x, int in_y);
    char move(bool a1, bool a2, bool a3, bool a4, bool a5 = false, bool a6 = false, bool a7 = false, bool a8 = false);
    int get_health_potions() { return 0; }
    virtual char get_team() { return 0; }
    void set_health_potions(int in_health_potions) {}
    int get_health();
    void set_health(int in_health);
    int get_medical();
    void set_medical(int in_medical);
    int get_power();
    void set_power(int in_power);
    int get_defense();
    void set_defense(int in_defense);
private:

};




















