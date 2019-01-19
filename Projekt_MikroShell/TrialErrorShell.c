
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
		int pid;
		char command[50];
		char *p, *a;
 		char path[1024];
		char host[200];	
		
#define NORM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"


int main()
{
	while(1)	
	{
	
		getcwd(path, sizeof(path));
		gethostname(host, sizeof(host));
		printf("\n");
		printf("%s",host);
		printf(" ");
		printf("%s",path);
		printf("$");
		fgets(command, sizeof(command),stdin);	
		if(strcmp(command,"exit\n")==0)	 
		{
			exit(EXIT_SUCCESS);	
		}
		else if(strcmp(command,"help\n")==0)
		{
			printf("%s***************************************************\n",GREEN);
			printf("%s** Autor: Witold Borowiak                        **\n",GREEN);
			printf("%s***************************************************\n",GREEN);
			printf("%s** Lista komend: exit, help                      **\n",GREEN);
			printf("%s***************************************************\n",GREEN);
			
		}
		else
		{	
				command[strlen(command)-1]='\0';
				p=strtok(command, " ");
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
 					source = fopen(args[1], "r");
					if(args[2]==NULL)
					{
						printf("Nie podano pliku docelowego");
					}	
					else
					{
 						target = fopen(args[2], "w");
 						char ch;
					 	while ((ch = fgetc(source)) != EOF){
      						fputc(ch, target);
      					}
      					fclose(source);
   						fclose(target);
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
