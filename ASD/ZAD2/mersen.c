#include <iostream>
#include <cstdio>
#include <cmath>

#define SIZE 20
//2^20
//#define LIMIT 1048576

using namespace std;

int is_first(long n){
	for(long i=2;i<=sqrt(n);i++){
		if(n%i==0) return 0;
	}
	return 1;
}

int main(int argc, char ** argv[]){
	int T[SIZE];
	for(int i=0;i<=SIZE;i++){
		T[i]=1;
	}
	for(int i=2;i<=SIZE;i++){
		if(T[i]==1){
			for(int j=pow(i,2);j<=SIZE;j=j+i){
				T[j]=0;
			}
		}
	}
	for(int i=2;i<=SIZE;i++){
		if(T[i]==1){
			long mersen=pow(2,i)-1;
			if(is_first(mersen)==1){
				cout<<mersen<<endl;
			}
		}
	}
return 0;
}