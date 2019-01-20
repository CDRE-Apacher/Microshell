#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
		
#define C_NRM  "\x1B[0m"
#define C_RED  "\x1B[31m"
#define C_GRN  "\x1B[32m"
#define C_YLW  "\x1B[33m"
#define C_BLU  "\x1B[34m"
#define C_MAG  "\x1B[35m"
#define C_CYA  "\x1B[36m"
#define C_WHT  "\x1B[37m"

	int pid;
	char cmd_line_input[50];
	char *p, *a;
 	char current_path[1024];
	static char host[200];	
	static char username[64];

void get_username(char * dest, int bufSize){
	strncpy(dest, getenv("USER"), bufSize);
}

void print_prompt(char * host, char * username, char * current_path){
	printf("\n%s%s %s%s %s%s:$>%s",C_GRN, host, C_BLU, username, C_RED, current_path, C_NRM);
}
//////////////////////////////////// VERY WIP /////////////////////////////////////////
//THIS CD:
/*
	*token not used here
	*prompt is split into: *prompt | *a
	*pth is passed when calling the function

	if(strcmp(buffer,"cd") == 0){
        tok = strtok(NULL,"\n");
        cd(tok);
    }
*/

int cd(char *pth){
   	char path[1024];
   	strcpy(path,pth);

  	static char *prompt = "OS";
  	static char *a = ">";
   	char *token;

   	char cwd[256]; 
   	getcwd(cwd,sizeof(cwd));

   	strcat(cwd,"/"); 
   	strcat(cwd,path);
   	chdir(cwd);    

   	printf("%s-%s%s",prompt,path,a);
   	return 0;
}
//END OF THIS CD
////////////////////////////////////////////////////////////////////////////////////////

void print_help(){
	printf("%s*****************************************************\n",C_CYA);
	printf("MICROSHELL BY: MAREK GULAWSKI\n");
	printf("LICENSED UNDER: %sCREATIVE COMMONS:cc by-nc-sa 4.0%s\n",C_RED,C_CYA);
	printf("AVAILABLE COMMANDS:\n");
	printf("~help - prints this window\n");
	printf("~cd <relative path> - changes the current directory using relative path\n");
	printf("~cp <source file> <destination file> - copies the contesnts of the source file to the destination file\n");
	printf("OTHER COMMANDS ARE SUPPORTED BUT EXECUTED OUTSIDE OF THIS MICROSHELL%s",C_NRM);
}

int main()
{
	while(1)	
	{
	
		getcwd(current_path, sizeof(current_path));
		gethostname(host, sizeof(host));
		get_username(username, 64);

		/*printf("\n");
		printf("%s",host);
		printf(" ");
		printf("%s",current_path);
		printf("$");*/

		print_prompt(host, username, current_path);

		fgets(cmd_line_input, sizeof(cmd_line_input),stdin);	

		if(strcmp(cmd_line_input,"exit\n")==0){
			exit(EXIT_SUCCESS);	
		}

		/*
		else if(strcmp(cmd_line_input,"help\n")==0)
		{
			printf("%s***************************************************\n",GREEN);
			printf("%s** Autor: Witold Borowiak                        **\n",GREEN);
			printf("%s***************************************************\n",GREEN);
			printf("%s** Lista komend: exit, help, cp a b ,            **\n",GREEN);
			printf("%s***************************************************\n",GREEN);
			printf("%s",NORM);
		*/
		else if(strcmp(cmd_line_input,"help\n")==0){
			print_help();
		}
		else{	
				cmd_line_input[strlen(cmd_line_input)-1]='\0';
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
			if (strcmp(a,"cp")==0)
			{
				FILE *source, *target;
				if(args[1]==NULL)
				{
					printf("Nie podano pliku zrodlowego");
				}
				else
				{
					if( access( args[1], F_OK ) != -1 ) {
 						source = fopen(args[1], "r");
						if(args[2]==NULL)
						{
							printf("Nie podano pliku docelowego");
						}	
						else
						{
 							target = fopen(args[2], "w");
 							char temp;
					 		while ((temp = fgetc(source)) != EOF){
      							fputc(temp, target);
      						}
      						fclose(source);
   							fclose(target);
 						}
 					}
 					else
 						{
 							printf("Nie zrodlowy nie istnieje");
						}
 				}
			}
			else
			{
				pid = fork(); 	
				if(pid>0) wait(NULL);
				if(pid==0)
				{
					execvp(a, args);
				}
			}
		}				
	}
return EXIT_SUCCESS;
}
