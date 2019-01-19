#ifndef __COMMON_H
#define __COMMON_H

#ifdef WIN32
#pragma once
#include "targetver.h"
#endif

typedef enum {
	rfalse,
	rtrue
} rbool;

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#ifdef WIN32
#include <Windows.h>
#include <direct.h>
#include <winsock.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h>
#endif

#ifdef WIN32
#define ANSI_COLOR_RED     ""
#define ANSI_COLOR_GREEN   ""
#define ANSI_COLOR_YELLOW  ""
#define ANSI_COLOR_BLUE    ""
#define ANSI_COLOR_MAGENTA ""
#define ANSI_COLOR_CYAN    ""
#define ANSI_COLOR_RESET   ""
#else
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#endif

#include "util.h"
#include "tokenizer.h"

#endif
