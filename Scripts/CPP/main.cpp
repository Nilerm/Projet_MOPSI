#include <iostream>
#include <math.h>


using namespace std;

class expo{
public:
	float operator()(float x){return exp(-x);};
};
class tot{
public:
	float operator()(float x){return exp(-(x*x));};
};
class sinu{
public:
	float operator()(float x){return sin(x);};
};

class poly{
public:
	float operator()(float x){return x*x;};
};

template<typename Function>
double trapeze(Function f, float a, float b, int n){
	double step=(b-a)/n;
	double area=step/2*(f(a)+f(b));
	for(int i=1; i<n; i++){
		area+=step*f(a+i*step);
	}
	return area;
}

template<typename Function>
double simpson(Function f,float a, float b, int n){
	double step=(b-a)/n;
	double area=(f(a)+f(b));
	for(int i=1; i<n; i++){
		if(i%2)area+=4*f(a+i*step);
		else area+=2*f(a+i*step);
	}
	area*=step/3;
	return area;
}


int main(){
	expo f;
	tot g;
	sinu s;
	double Pi=3.14159265358979;
	poly p;
	for(int i=1; i<=50; i++){
		cout<<"Iteration "<<i<<endl;
		cout<<"Trapeze : "<<endl; 
		cout<<abs(trapeze(s,-Pi,Pi,1000*i))<<endl;
		cout<<"Simpson : "<<endl;
		cout<<abs(simpson(s,-Pi,Pi,1000*i))<<endl;
	}
	return 0;
}