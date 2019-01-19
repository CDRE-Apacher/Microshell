#ifndef __UTIL_H
#define __UTIL_H

#ifdef WIN32
#pragma once
#endif

void append_char_to_string(char *dest, char src);

int set_working_directory(char *dest);
void get_working_directory(char *dest, int bufSize);

void get_user_name(char *dest, int bufSize);

void get_host_name(char *dest, int bufSize);

#endif