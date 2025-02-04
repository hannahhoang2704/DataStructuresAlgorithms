/* fft.c -- straightforward recursive FFT implementation
 *
 * Look for the link http://www.engineeringproductivitytools.com/stuff/T0001/PT03.HTM
 * for details about the implementation
 *
 * Written by Jarkko Vuori 2013
 */

#include <complex>
#include <numeric>
#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>

#define RUN_TIMES 30

using namespace std;

typedef complex<double> cx;
// radix-2 in-place FFT, n must be 2^k (e.g. 2,4,6,...)
void fft(int n, cx x[]) {
	const cx J(0, 1);
	const double PI = 3.14159265359;
	// check the trivial case
	if (n == 1)
		return;

	// perform two sub-transforms
	int n2 = n/2; // size of sub-transform
	cx *xe = new cx[n2];
	cx *xo = new cx[n2];
	for (int i = 0; i < n2; i++) { // perform n/2 DIF 'butterflies'
		xe[i] = x[i] + x[i+n2];	                     // even subset
		xo[i] = (x[i] - x[i+n2])*exp(-J*(2*PI*i/n)); // odd subset
	}
	fft(n2, xe);
	fft(n2, xo);

	// construct the result vector
	for (int k = 0; k < n2; k++) {
		x[2*k]   = xe[k]; // even k
		x[2*k+1] = xo[k]; // odd k
	}

	delete[] xe;
	delete[] xo;
}


int main() {
	const int N = 8;
	cx input[N];
    vector<long long> time_container;
	// create the test input signal sequence
    for (int j= 0; j < RUN_TIMES; j++){
        for (int i = 0; i < N; i++)
            input[i] = cx(i, -i);  // linear ramp for real part, negative ramp for imaginary part
        chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
        fft(N, input);
        chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds> (end-start).count();
//        cout << "Time lapsed " << duration << "ns" <<endl;
        time_container.push_back(duration);
    }


    sort(time_container.begin(), time_container.end());
    time_container.erase(time_container.begin()+10, time_container.end());
    cout << "All duration is ";
    for(auto &duration: time_container){
        cout << duration << " ";
    }
    cout << endl;
    auto mean = reduce(time_container.begin(), time_container.end())/time_container.size();
    cout << "Average elapsed time: " << mean << " ns " << endl;
    auto accum = 0;
    for_each(time_container.begin(), time_container.end(), [&](long long &duration){
        accum += (duration-mean)*(duration-mean);
    });
    auto std_deviation = sqrt(accum/(time_container.size()-1));
    cout << "Standard deviaton is " << std_deviation << endl;
//	system("PAUSE");
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
