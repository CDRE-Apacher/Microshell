#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

		
		
#define NORM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"

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
	printf("\n%s %s %s:$>", host, username, current_path);
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




		fgets(cmd_line_input, sizeof(cmd_line_input),stdin);	


		if(strcmp(cmd_line_input,"exit\n")==0)	 
		{
			exit(EXIT_SUCCESS);	
		}
		else if(strcmp(cmd_line_input,"help\n")==0)
		{
			printf("%s***************************************************\n",GREEN);
			printf("%s** Autor: Witold Borowiak                        **\n",GREEN);
			printf("%s***************************************************\n",GREEN);
			printf("%s** Lista komend: exit, help, cp a b ,            **\n",GREEN);
			printf("%s***************************************************\n",GREEN);
			printf("%s",NORM);
			
		}
		else
		{	
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
