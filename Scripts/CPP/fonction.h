#ifndef FONCTION_H
#define FONCTION_H
#include <complex>
using namespace std;

float BS(float r,float sigma, float t,float W,float S0=1);

complex<float> phi_BS(float r,float sigma, float t,complex<float> u, float S0=1);

complex<float> psi(float r,complex<float> phi,float alpha, float v,float T);

float VG(float r,float t, float X,float theta,float nu,float sigma, float S0=1);

complex<float> phi_VG(float r,float nu,float theta,float T,float sigma, complex<float> u,float S0=1);

complex<float> x_j_trapeze(float eta,float b,float v,float alpha,float k,float psi);

complex<float> x_j_simpson(float eta,float b,float v,float alpha,float k,float psi,int j);
#endif // FONCTION_H
