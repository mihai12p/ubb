#pragma once

#include "service.h"

#define ANSI_COLOR_RED(s)     "\x1b[31m" s "\x1b[0m"
#define ANSI_COLOR_GREEN(s)   "\x1b[32m" s "\x1b[0m"
#define ANSI_COLOR_YELLOW(s)  "\x1b[33m" s "\x1b[0m"
#define ANSI_COLOR_BLUE(s)    "\x1b[34m" s "\x1b[0m"
#define ANSI_COLOR_MAGENTA(s) "\x1b[35m" s "\x1b[0m"
#define ANSI_COLOR_CYAN(s)    "\x1b[36m" s "\x1b[0m"

void participanti_predefiniti(repository* repo); // adauga participanti in lista
int consola(repository* repo); // interfata generala cu utilizatorul
