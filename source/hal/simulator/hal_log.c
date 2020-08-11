#include "hal_log.h"

#include <stdarg.h>

extern LOGCB SIMLogPrint;

void hal_log_printf(char* format, ...)
{
	static char logBuffer[512];
	va_list args;

	va_start(args, format);
	vsprintf(logBuffer, format, args);
	va_end(args);

	SIMLogPrint((uint8_t*)logBuffer);

	return 0;
}