#include "logger.h"

#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>

#include <cstdarg>

//#ifdef _DEBUG
static HANDLE log_handle;
static char buffer[4096];

void init_logger(HANDLE handle)
{
	//AllocConsole();
	log_handle = handle;
}

void free_logger()
{
	CloseHandle(log_handle);
}

void LOG(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	size_t len = vsnprintf(buffer, sizeof(buffer), format, args);
	WriteFile(log_handle, buffer, len, NULL, NULL);
	FlushFileBuffers(log_handle);
	va_end(args);
}