/* map.h */
using namespace std;

class map {
public:
    map(int in_x, int in_y);
    ~map();
    bool next_cycle();   // gia na kali tes sinartisis move ton ontotonon
    friend ostream& operator<<(ostream& left, const map& right);
private:
    int day_night;
    int max_day_nigth;
    int number_werewolves;
    int number_vampires;
    int number_entitiese;
    coordinates size;
    char** array;
    entities* ent[700];
};