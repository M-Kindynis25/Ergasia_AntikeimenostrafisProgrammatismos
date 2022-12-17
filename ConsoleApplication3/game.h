/* game.h */

using namespace std;

class entities;

class game {
public:
    game();
    ~game();
    friend ostream& operator<<(ostream& left, const game& right);
    bool next_step_game();
private:
    char** map;
    coordinates size;
    entities* ent[700];
    int number_werewolves;
    int number_vampires;
    int number_entitiese;
    int pl_day_night;
    int day_night;
};

