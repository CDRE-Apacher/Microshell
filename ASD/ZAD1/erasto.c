#include <iostream>
#include <cstdio>
#include <cmath>

#define SIZE 100

using namespace std;

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
			cout<<i<<endl;
		}
	}
}