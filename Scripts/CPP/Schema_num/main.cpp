#include <iostream>
#include <math.h>


using namespace std;

class expo{
public:
	float operator()(float x){return exp(-x);};
};
class tot{
public:
	double operator()(double x){return exp(-(x*x));};
};
class sinu{
public:
	double operator()(double x){return sin(x);};
};

class poly{
public:
	double operator()(double x){return x*x;};
};

template<typename Function>
double trapeze(Function f, double a, double b, int n){
	double step=(b-a)/n;
	double area=step/2*(f(a)+f(b));
	for(int i=1; i<n; i++){
		area+=step*f(a+i*step);
	}
	return area;
}

template<typename Function>
double simpson(Function f,double a, double b, int n){
	double step=(b-a)/n;
	double area=(f(a)+f(b));
	for(int i=1; i<n; i++){
		if(i%2)area+=4*f(a+i*step);
		else area+=2*f(a+i*step);
	}
	area*=step/3;
	return area;
}

template<typename Function>
double romberg(Function f,double a,double b, int n){
	double *R=new double[n*n]; // où R[i+n*j] correspond à R(i,j)
	for(int i=0;i<n;i++){
	   R[i]=trapeze(f,a,b,pow(2,i));} //On initialise
    for(int i=1;i<n;i++){
		for(int j=1;j<=i;j++){
				R[i+n*j]=(pow(4,j)*R[i+n*(j-1)]-R[i-1+n*(j-1)])/(pow(4,j)-1);
			}	
		}
	double result=R[(n-1)+n*(n-1)];
	delete[]R;
	return result;
}



int main(){
	expo f;
	tot g;
	sinu s;
	double Pi=3.14159265358979;
	double a=0;
	double b=10000;
	poly p;
	for(int i=1; i<=10; i++){
		cout<<"Iteration "<<i<<endl;
		cout<<"Trapeze : "<<endl; 
		cout<<abs(trapeze(f,a,b,1000*i))<<endl;
		cout<<"Simpson : "<<endl;
		cout<<abs(simpson(f,a,b,1000*i))<<endl;
		cout<<"Romberg : "<<endl;
		cout<<romberg(f,a,b,15) <<endl;
	}
	while(true){}
	return 0;
}