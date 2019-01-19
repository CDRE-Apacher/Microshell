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



int main()
{
	printf("*********************************\n");
	printf("MADE BY PATRYK GAŁKA\n");
	printf("*********************************\n");
	while(1)	
	{
	
		getcwd(path, sizeof(path));
		gethostname(host, sizeof(host));
		printf("\n");
		printf(host);
		printf(" ");
		printf(path);
		printf(" >");
		fgets(command, sizeof(command),stdin);
		if(strcmp(command,"exit\n")==0)	 
		{
			exit(EXIT_SUCCESS);	
		}else
		{	
			pid = fork(); 	
			if(pid>0) wait(NULL);
			if(pid==0)
			{	
				command[strlen(command)-1]=0;
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
				execvp(a, args);
			}
		}
				
	}

	return EXIT_SUCCESS;
}
