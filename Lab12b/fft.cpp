/* fft.c -- straightforward recursive FFT implementation
 *
 * Look for the link http://www.engineeringproductivitytools.com/stuff/T0001/PT03.HTM
 * for details about the implementation
 *
 * Written by Jarkko Vuori 2013
 */

#include <complex>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cmath>
#include <iomanip>

#include "measure.h"
#include "fft_func.h"
#define MIN_N 2048
//#define MAX_N 4096
#define MAX_N 262144

int main() {
    chrono::time_point<chrono::high_resolution_clock> start_program = chrono::high_resolution_clock::now();
    double mean_unopt, stdev_unopt, mean_unopt_br, stdev_unopt_br, mean_single, stdev_single, mean_single_br, \
    stdev_single_br, mean_parallel, stdev_parallel, mean_parallel_br, stdev_parallel_br;
    ofstream csvFile("/Users/HannahHoang/DataStructure/Lab12b/fft_measurements.csv");
    if (!csvFile) {
        cerr << "Error opening file for writing." << endl;
        return 1;
    }
    csvFile << "N,Unopt,Unopt_stdev,Unopt_br,Unopt_br_stdev,Single,Single_br,Single_br_stdev,Parallel,Parallel_stdev,Parallel_br,Parallel_br_stdev" << endl;
    cout << setw(7) << right << " N "
         << setw(12) << right << "Unopt" << setw(17) << right << "Unopt_br"
         << setw(12) << right << "Single" << setw(16) << right << "Single_br"
         << setw(14) << right << "Parallel" << setw(14) << right << "Paral_br"<< endl;
    for(int N = MIN_N; N <= MAX_N; N*=2){
        cout << setw(7) << right <<  N << ": ";

        FFTTestbed *unopt = new FFTTestbed(fft_unopt, N);
        unopt->measure(mean_unopt, stdev_unopt);
        cout << setw(6) << right << (int)mean_unopt << "(+/- " << (int)stdev_unopt * 2 << ")ms";

        FFTTestbed *unopt_br = new FFTTestbed(fft_unopt_br, N);
        unopt_br->measure(mean_unopt_br, stdev_unopt_br);
        cout << setw(6) << right << (int)mean_unopt_br << "(+/- " << (int)stdev_unopt_br * 2 << ")ms";

        FFTTestbed *single = new FFTTestbed(fft_single, N);
        single->measure(mean_single, stdev_single);
        cout << setw(6) << right << (int)mean_single << "(+/- " << (int)stdev_single * 2 << ")ms";

        FFTTestbed *single_br = new FFTTestbed(fft_single_br, N);
        single_br->measure(mean_single_br, stdev_single_br);
        cout << setw(6) << right << (int)mean_single_br << "(+/- " << (int)stdev_single_br * 2 << ")ms";

        FFTTestbed *parallel = new FFTTestbed(fft_parallel, N);
        parallel->measure(mean_parallel, stdev_parallel);
        cout << setw(6) << right << (int)mean_parallel << "(+/- " << (int)stdev_parallel * 2 << ")ms";

        FFTTestbed *parallel_br = new FFTTestbed(fft_parallel_br, N);
        parallel_br->measure(mean_parallel_br, stdev_parallel_br);
        cout << setw(4) << right << (int)mean_parallel_br << "(+/- " << (int)stdev_parallel_br * 2 << ")ms";
        cout << endl;
        csvFile << N << ","
                << mean_unopt << "," << stdev_unopt * 2 << ","
                << mean_unopt_br << "," << stdev_unopt_br * 2 << ","
                << mean_single << ","
                << mean_single_br << "," << stdev_single_br * 2 << ","
                << mean_parallel << "," << stdev_parallel * 2 << ","
                << mean_parallel_br << "," << stdev_parallel_br * 2 << endl;
    }
    csvFile.close();
    chrono::time_point<chrono::high_resolution_clock> end_program = chrono::high_resolution_clock::now();
    auto duration_program = chrono::duration_cast<chrono::seconds> (end_program-start_program).count();
    cout << "Measurement took " << duration_program << "s" << endl;

	return EXIT_SUCCESS;
}

/*
valid output:
(28,-28)
(5.65685,13.6569)
(4.13891e-013,8)
(-2.34315,5.65685)
(-4,4)
(-5.65685,2.34315)
(-8,4.13447e-013)
(-13.6569,-5.65685)
Press any key to continue . . .*/
