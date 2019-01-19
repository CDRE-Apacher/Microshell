#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    int licz_arg;
    char kom[52], *arg[52];
    do{
        printf(">");
        gets(kom);
        arg[0] = strtok(kom, " ");
        for(licz_arg = 1; arg[licz_arg-1] != NULL; licz_arg++){
            arg[licz_arg] = strtok(NULL, " ");
        }
		if (strcmp(kom, "exit") == 0)
        {
        printf("Exit\n");
        exit(EXIT_SUCCESS);
        }
        if (fork()==0)
            execvp(arg[0], arg);
        wait();
    } while(1);

    return 0;
}