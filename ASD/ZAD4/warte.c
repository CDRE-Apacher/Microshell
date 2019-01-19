#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

long double power(int n){
	if(n==0||n==1) return 1;
	else return n*power(n-1);
}

int main(int argc, char const *argv[]){
	long double eps,e,n,x1,x2;
	long double sum=1.0;
	cout<<"Input the precision of calculations (ex. 0.01)"<<endl;
	cout<<"Output precision is 20 digits!"<<endl;
	cin>>eps;
	int i=1;
	x1=1.0/i;
	i++;
	sum+=x1;
	x2=1.0/power(i);
	i++;
	sum+=x2;
	while(abs(x2-x1)>=eps){
		x1=x2;
		x2=1/power(i);
		i++;
		sum+=x2;
	}
	cout.precision(20);
	cout<<"The constant e = "<<sum<<endl;

return EXIT_SUCCESS;
}