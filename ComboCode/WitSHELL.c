#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
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
		printf("%s%s@%s",GREEN,getenv("USER"),host);
		printf("%s%s%s",BLUE,path,NORM);
		printf("$");
		fgets(command, sizeof(command),stdin);	
		if(strcmp(command,"exit\n")==0)	 
		{
			exit(EXIT_SUCCESS);	
		}
		else if(strcmp(command,"help\n")==0)
		{
			printf("%s***************************************************\n",GREEN);
			printf("%s** %sAutor: Witold Borowiak%s                        **\n",GREEN,CYAN,GREEN);
			printf("%s***************************************************\n",GREEN);
			printf("%s** Lista komend: exit, help, cp, touch, cd       **\n",GREEN);
			printf("%s***************************************************\n",GREEN);
			printf("%s\n",NORM);
			
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
					printf("%sBlad: %sNie podano pliku zrodlowego%s\n",RED,YELLOW,NORM);
				}
				else
				{
					if( access( args[1], F_OK ) != -1 ) {
 						source = fopen(args[1], "r");
						if(args[2]==NULL)
						{
							printf("%sBlad: %sNie podano pliku docelowego%s\n",RED,YELLOW,NORM);
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
 							printf("%sBlad: %sNie zrodlowy nie istnieje%s\n",RED,YELLOW,NORM);
						}
 				}
			}
			else if(strcmp(a,"touch")==0)
			{
				if(args[1]==NULL)
				{
					printf("%sBlad: %sNie podano nazwy pliku%s\n",RED,YELLOW,NORM);
				}
				else
				{
					FILE *target;
					target=fopen(args[1], "w");
					fclose(target);

				}
				
			}
			else if(strcmp(a,"whoami")==0)
			{
				printf("%s\n", getenv("USER"));
			}
			else if(strcmp(a,"cd")==0)
			{
				if(args[1]==NULL)
				{
					chdir("/home");
				}
				else
				{
					DIR* dir = opendir(args[1]);
					if (dir)
					{
					chdir(args[1]);	
    				closedir(dir);
					}
					else 
					{
						printf("%sBlad: %sKatalog nie istnieje%s\n",RED,YELLOW,NORM);
					}
					
				}
			}
			else
			{
				printf("%sOperacja wykonana poza microshellem%s\n",MAGENTA,NORM);
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
