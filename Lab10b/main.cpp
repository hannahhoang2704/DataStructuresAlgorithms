#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <iterator>
#include <algorithm>
#include <ctime>

using namespace std;

struct field_reader: ctype<char> { // specify '\n' as the only separator
    field_reader(): ctype<char>(get_table()) {}
    static ctype_base::mask const *get_table() {
        static vector<ctype_base::mask>
        rc(table_size, ctype_base::mask());
        rc['\n'] = ctype_base::space;
        return &rc[0];
    }
};

class Athlete{
public:
    explicit Athlete(const string& name, int nr = 0, int time = 0): name(name), nr(nr), time(time){};

    void ReadName(string & athlete_name) {
        name = athlete_name;
    };

    void ReadTime() {
        cout << "Give time for " << name << "? ";
        cin >> time;
    }

    bool Better(Athlete & another_athlete){
        return time < another_athlete.time;
    };

    friend ostream & operator<<(ostream &out, const Athlete& athlete){
        out << athlete.nr << " " << athlete.name << "\t" << athlete.time << endl;
        return out;
    }
private:
    int time;
    string name;
    int nr;
};


int main(void) {
    ifstream myfile("/Users/HannahHoang/DataStructure/Lab10b/athletes.txt", ios::in);
    if (!myfile)  cerr << "Error opening file: " << strerror(errno) << endl;
    myfile.imbue(locale(locale(), new field_reader()));// use our own separator list
    istream_iterator<string> iit(myfile);
    istream_iterator<string> iiteof;
    int nr = 0;
    vector<Athlete> athlete_list;

    transform(iit, iiteof, back_inserter(athlete_list), [&nr](const string& name) {
        return Athlete(name, ++nr);
    });

    random_device rd;
    mt19937 g(rd());
    shuffle(athlete_list.begin(), athlete_list.end(), g);
    for_each(athlete_list.begin(), athlete_list.end(), mem_fn(&Athlete::ReadTime));
    sort(athlete_list.begin(), athlete_list.end(), [](Athlete& athlete1, Athlete & athlete2){
        return athlete1.Better(athlete2);
    });

    cout << "Final results are:" << endl;
    for_each(athlete_list.begin(), athlete_list.end(), [](const Athlete& athlete) {
        cout << athlete << endl;
    });

    return EXIT_SUCCESS;
}
