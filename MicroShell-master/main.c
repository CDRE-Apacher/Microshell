#include "common.h"
#include "cmds.h"

int main_loop(int argc, char *argv[]);

char *userinput;

int currentInputIndex;

int main(int argc, char *argv[])
{
	currentInputIndex = -1;
	userinput = 0;

	printf("*************************\n");
	printf("* MicroShell v0.1       *\n");
	printf("*  by Maciej Ray Marcin *\n");
	printf("*************************\n");

	/* start the main loop */
	return main_loop(argc, argv);
}

int process_user_input(char ** tokenizedInput, int inputTokenCount)
{
	int i = 0;
	/* check table for built-in functions */
	for (i = 0; i < sizeof(builtInCmds) / sizeof(builtInCmds_t); i++) 
	{
		if (strcmp(tokenizedInput[0], builtInCmds[i].cmd) == 0)
		{
			int r;
			if((r = builtInCmds[i].func(tokenizedInput, inputTokenCount)) != 0)
			{
				printf("Command returned an error code: %d\n", r);
			}
			return r;
		}
	}
	/* If we're a child process */
	if(fork() == 0) 
	{
		/* Execute the command */
		exit(execvp(tokenizedInput[0], tokenizedInput)); 
	}
	/* If we're a parent process, */
	else
	{ 					
		int r = 0;
		/* wait for child to exit */
		wait(&r);			
		/* if return code is different than 0, let us know */
		if(r != 0)				
			printf("Program returned an error code: %d\n", r); 
		return r;
	}
}

int main_loop(int argc, char *argv[])
{
	static char cwd[1024];
	static char username[64];
	static char host[256];
	while (1)
	{
		/* get current working directory */
		get_working_directory(cwd, 1024); 	
		/* get current user name */
		get_user_name(username, 64);		
		/* get host name */
		get_host_name(host, 256);	 		

		char **tokenizedInput = 0;
		int inputTokenCount = 0;
		currentInputIndex = -1;

		printf(ANSI_COLOR_GREEN"%s@%s:"ANSI_COLOR_YELLOW"%s"ANSI_COLOR_RESET"> ", username, host, cwd);
		
		/* allocate a char array for user input */
		userinput = (char *)calloc(50, 1); 
		while (1)
		{
			currentInputIndex++;

			if (currentInputIndex != 0 && currentInputIndex % 50 == 0)
				/* resize the char array */
				userinput = (char *)realloc(userinput, currentInputIndex + 50); 

			/* get character */
			userinput[currentInputIndex] = fgetc(stdin); 	
			/* if user pressed enter, break */
			if (userinput[currentInputIndex] == '\n')		
			{
				break;
			}
		}
		/* split user input into tokens (code is in tokenizer.c) */
		tokenizedInput = tokenize_input(userinput, &inputTokenCount); 

#ifdef TOKEN_DEBUG
		printf("Printing tokens because TOKEN_DEBUG was defined:\n");
		int i = 0;
		for(i = 0; i < inputTokenCount; i++)
		{
			printf("Token %d: %s\n", i, tokenizedInput[i]);
		}
#endif

		/* process user input */
		process_user_input(tokenizedInput, inputTokenCount);
		/* free the char array to save memory */
		free(userinput); 
	}
	return 0;
}
