#include "common.h"
#include "util.h"

/* appends a character to string */
void append_char_to_string(char * dest, char src)
{
	int len = strlen(dest);
	assert(len < 255 && "Max length of string");
	dest[len] = src;
	dest[len + 1] = '\0';
}

/* sets the current working directory */
int set_working_directory(char *dest)
{
	return chdir(dest);
}

/* gets the current working directory */
void get_working_directory(char * dest, int bufSize)
{
	getcwd(dest, bufSize);
}

/* gets the current user name */
void get_user_name(char * dest, int bufSize)
{
#ifdef WIN32
	strncpy(dest, getenv("USERNAME"), bufSize);
#else
	strncpy(dest, getenv("USER"), bufSize);
#endif
}

/* gets the current host name */
void get_host_name(char * dest, int bufSize)
{
#ifdef WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	gethostname(dest, bufSize);

#ifdef WIN32
	WSACleanup();
#endif
}