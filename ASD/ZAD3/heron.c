#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

//#define EPS 0.01f

int main(int argc, char * argv[]){
	float c,x1,x2,eps;
	cout<<"Input number to calculate the square root of: "<<endl;
	cin>>c;
	cout<<"Input the precision of calculation (ex. 0.01): "<<endl;
	cin>>eps;
	x1=c;
	x2=0.5*(x1+c/x1);
	while(abs(x2-x1)>=eps){
		x1=x2;
		x2=0.5*(x1+c/x1);
	}
	cout<<"Root of "<<c<<" = "<<x2<<endl;
return 0;
}