#include<sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include<dirent.h>
#include<error.h>

#define BUFFERSIZE 20
int main(){

char *args[80]; 
char buffer[BUFFERSIZE];
char *prompt = "OS";
char *a = ">";
printf("%s%s",prompt,a); 
fgets(buffer, BUFFERSIZE, stdin);  

char *tok; 
tok = strtok (buffer," ");


while(buffer != NULL){ 
   buffer[strlen(buffer)-1] = '\0';  
   pid_t pid;
   pid = fork();
   if(pid < 0){
      fprintf(stderr, "Fork failed");
      return 1;
   }
   else if(pid == 0){

       if(strcmp(buffer,"cd") == 0){
         tok = strtok(NULL,"\n");
         cd(tok);
       }
       printf("%s%s",prompt,a); 
       fgets(buffer, BUFFERSIZE, stdin);
   }
   else{
     wait(NULL);
   }
}
return 0;
}


int cd(char *pth){
   char path[1000];
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
