#include <iostream>
#include "measurement.h"

using namespace std;
// change the following to the path where you have mea.dat file
const static char *filename = "/Users/HannahHoang/DataStructure/Lab2/mea.dat";

int main(int argc, char *argv[]) {
    Measurements m1, m2;
    if (m1.read(filename)) {
        m1.print();
        m2 = m1;
        m2.inc(0.1);
        cout << "Mean m1 is " << m1.mean() << endl;
        cout << "Mean m2 is " << m2.mean() << endl;
    }
    else
        cout << "Can't open the file '" << filename << "'" << endl;
    return 0;
}