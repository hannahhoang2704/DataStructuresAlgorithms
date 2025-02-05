//
// Created by Hanh Hoang on 5.2.2025.
//

#ifndef LAB12B_FFT_FUNC_H
#define LAB12B_FFT_FUNC_H

#include <complex>
#include <future>

using namespace std;
typedef complex<double> cx;
const cx J(0, 1);
const double PI = 3.14159265359;

//UNOPT
// radix-2 in-place FFT, n must be 2^k (e.g. 2,4,6,...)
void fft_unopt(int n, cx x[]) {
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
    fft_unopt(n2, xe);
    fft_unopt(n2, xo);

    // construct the result vector
    for (int k = 0; k < n2; k++) {
        x[2*k]   = xe[k]; // even k
        x[2*k+1] = xo[k]; // odd k
    }

    delete[] xe;
    delete[] xo;
}

//UNOPT_BR
void fft_unopt_br(int n, cx x[]) {
    // check the trivial case
    if (n == 1)
        return;

    // perform two sub-transforms
    int n2 = n/2; // size of sub-transform

    for (int i = 0; i < n2; i++) { // perform n/2 DIF 'butterflies'
        cx even = x[i] + x[i+n2];	                     // even subset
        cx odd = (x[i] - x[i+n2])*exp(-J*(2*PI*i/n)); // odd subset
        x[i] = even;
        x[i+n2] = odd;
    }
    fft_unopt_br(n2, x);
    fft_unopt_br(n2, x+n2);

    // construct the result vector
    for (int k = 0; k < n2; k++) {
        cx temp = x[k];
        x[k]   = x[k+n2]; // even k
        x[k+n2] = temp; // odd k
    }
}

//SINGLE
void fft_single(int n, cx x[]) {
    mutex fft_mutex;
    // check the trivial case
    if (n == 1)
        return;

    // perform two sub-transforms
    int n2 = n/2; // size of sub-transform
    fft_mutex.lock();
    cx *xe = new cx[n2];
    cx *xo = new cx[n2];
    for (int i = 0; i < n2; i++) { // perform n/2 DIF 'butterflies'
        xe[i] = x[i] + x[i+n2];	                     // even subset
        xo[i] = (x[i] - x[i+n2])*exp(-J*(2*PI*i/n)); // odd subset
    }
    fft_unopt(n2, xe);
    fft_unopt(n2, xo);

    // construct the result vector
    for (int k = 0; k < n2; k++) {
        x[2*k]   = xe[k]; // even k
        x[2*k+1] = xo[k]; // odd k
    }

    delete[] xe;
    delete[] xo;
    fft_mutex.unlock();
}


//SINGLE_BR
void fft_single_br(int n, cx x[]) {
    mutex fft_mutex;
    // check the trivial case
    if (n == 1)
        return;

    // perform two sub-transforms
    int n2 = n/2; // size of sub-transform
    fft_mutex.lock();
    for (int i = 0; i < n2; i++) { // perform n/2 DIF 'butterflies'
        cx even = x[i] + x[i+n2];	                     // even subset
        cx odd = (x[i] - x[i+n2])*exp(-J*(2*PI*i/n)); // odd subset
        x[i] = even;
        x[i+n2] = odd;
    }
    fft_unopt_br(n2, x);
    fft_unopt_br(n2, x+n2);

    // construct the result vector
    for (int k = 0; k < n2; k++) {
        cx temp = x[k];
        x[k]   = x[k+n2]; // even k
        x[k+n2] = temp; // odd k
    }
    fft_mutex.unlock();
}

//PARALLEL
void fft_parallel(int n, cx x[]) {
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
    auto future_even = std::async(std::launch::async, fft_unopt, n2, xe);
    fft_unopt(n2, xo);
    future_even.get();

    // construct the result vector
    for (int k = 0; k < n2; k++) {
        x[2*k]   = xe[k]; // even k
        x[2*k+1] = xo[k]; // odd k
    }

    delete[] xe;
    delete[] xo;
}

//PARALLEL_BR
void fft_parallel_br(int n, cx x[]) {
    // check the trivial case
    if (n == 1)
        return;

    // perform two sub-transforms
    int n2 = n/2; // size of sub-transform

    for (int i = 0; i < n2; i++) { // perform n/2 DIF 'butterflies'
        cx even = x[i] + x[i+n2];	                     // even subset
        cx odd = (x[i] - x[i+n2])*exp(-J*(2*PI*i/n)); // odd subset
        x[i] = even;
        x[i+n2] = odd;
    }
    auto future_even = async(launch::async, fft_unopt_br, n2, x);
    fft_unopt_br(n2, x+n2);
    future_even.get();
    // construct the result vector
    for (int k = 0; k < n2; k++) {
        cx temp = x[k];
        x[k]   = x[k+n2]; // even k
        x[k+n2] = temp; // odd k
    }
}

#endif //LAB12B_FFT_FUNC_H
