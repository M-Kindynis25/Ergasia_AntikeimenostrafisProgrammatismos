/* entities.h */

class entities{
  public:
    virtual void move()=0;
    virtual coordinates get_coordinate()=0;
    virtual void set_coordinate(int in_x, int in_y)=0;
  protected:
    coordinates coordinate;
};


class avatar: public entities{
  public:
    avatar(char in_team, int in_x, int in_y);
    void move();
    coordinates get_coordinate();
    void set_coordinate(int in_x, int in_y);
  private:
    int health_potions;
    char team;
};

class npc: public entities{
  public:
    
  protected:
    int health;
    int medical;
    int power;
    int defense;
};

class werewolves: public npc{
  public:
    werewolves(int in_x, int in_y);
    coordinates get_coordinate();
    void set_coordinate(int in_x, int in_y);
    void move();
  private:
  
};

class vampires: public npc{
  public:
    vampires(int in_x, int in_y);
    coordinates get_coordinate();
    void set_coordinate(int in_x, int in_y);
    void move();
  private:
  
};

















