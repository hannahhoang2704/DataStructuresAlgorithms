/* dynlist.cpp -- Dynamic linked linear list */

#include <iostream>

#include "matrix.h"
//#include "NodeData.h"
using namespace std;

// Application
int main (void)  {
    Matrix matrix;
    matrix[1][1] = new Char('a');
    matrix[1][52] = new String("Zilog");
    matrix[43][1] = new Int(64);
    matrix[76][43] = new Int(46);
    matrix[91][75] = new Complex(-1, 2);
    matrix[91][99] = new Char('b');
    cout << matrix;
    cout << "Cell (1,52) has content " << *(matrix[1][52]);
    return EXIT_SUCCESS;
}
