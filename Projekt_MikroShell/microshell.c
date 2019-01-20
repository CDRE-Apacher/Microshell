#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

//DEFINING BOOLEAN
typedef int bool;
#define TRUE 1;
#define FALSE 0;

void get_username(){
	strncpy(dest, getenv("USER"), bufSize);
}



int main(int argc, char const *argv[])
{
	return main_loop(argc, argv);
}

int main_loop(angc, argv){
	static char cwd[1024];
	static char username[64];
	static char host[256];
	while (1)
	{
		//get current working directory 
		getcwd(cwd, 1024); 	
		//get current user name 
		get_user_name(username, 64);		
		//get host name 
		gethostname(host, 256);
	}
}
