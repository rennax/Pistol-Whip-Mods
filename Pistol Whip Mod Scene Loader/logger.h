#ifndef LOGGING_H
#define LOGGING_H

#include <windows.h>

void init_logger(HANDLE handle);
void free_logger();
void LOG(const char* format, ...);


#endif