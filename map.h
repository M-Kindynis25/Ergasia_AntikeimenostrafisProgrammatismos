/* map.h */
using namespace std;

class map {
  public:
    map(int in_x, int in_y);
    ~map();
    friend ostream& operator<<(ostream& left, const map& right);
  private:
    int day_night;
    coordinates size;
    char **array;
};