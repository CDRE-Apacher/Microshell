/*
MICROSHELL PROJECT MAREK GULAWSKI
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
//#include <errno>

//DEFINING BOOLEAN
typedef int bool;
#define TRUE 1;
#define FALSE 0;

void get_username(char * dest, int bufSize){
	strncpy(dest, getenv("USER"), bufSize);
}

//Add some flavor colors
void print_prompt(char * host, char * username, char * current_path){
	printf("\n%s %s %s:$>", host, username, current_path);
}

int pid;
char cmd_line_input[50];
char *p, *a;
char current_path[1024];
static char host[200];
static char username[64];

int main()
{
	//ADD info about program
	while(1)	
	{
		//Get Current Working Directory
		getcwd(current_path, sizeof(current_path));
		//Get Host Name
		gethostname(host, sizeof(host));
		//Get User Name
		get_username(username, 64);
/*
		printf("\n");
		printf(host);
		printf(" ");
		printf(current_path);
		printf(" >");
*/
		//Print Prompt
		print_prompt(host, username, current_path);

		//Command Line Input
		fgets(cmd_line_input, sizeof(cmd_line_input),stdin);
			//Tokenize
		cmd_line_input[strlen(cmd_line_input)-1]=0;
				p=strtok(cmd_line_input, " ");
				int i=0;
				char *args[50];
				while(p!=NULL)
				{
					args[i]=p;
					i++;
					p=strtok(NULL, " ");
				}
				a=args[0];
				args[i]=NULL;

				/*
				if(strcmp(a[0],"exit")==0){}
				*/

		//Check If Command Is One Of The Following
		if(strcmp(cmd_line_input[0],"exit\n")==0){
			exit(EXIT_SUCCESS);	
		}else{	
			pid = fork(); 	
			if(pid>0) wait(NULL);
			if(pid==0)
			{	
				/*cmd_line_input[strlen(cmd_line_input)-1]=0;
				p=strtok(cmd_line_input, " ");
				int i=0;
				char *args[50];
				while(p!=NULL)
				{
					args[i]=p;
					i++;
					p=strtok(NULL, " ");
				}
				a=args[0];
				args[i]=NULL;*/
				execvp(a, args);
			}
		}			
	}
	return EXIT_SUCCESS;
}
