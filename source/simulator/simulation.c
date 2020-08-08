
#include "simulation.h"

#include <stdarg.h>
#include <stdio.h>

/* TODO Add Simulation Log Implementation into a proper directory */
static LOGCB SIMLogPrint;
void SIM_RegisterLOGCallback(LOGCB logCB)
{
	SIMLogPrint = logCB;
}
int Boot_Log(char* format, ...)
{
	static char logBuffer[512];
	va_list args;

	va_start(args, format);
	vsprintf(logBuffer, format, args);
	va_end(args);

	SIMLogPrint((uint8_t*)logBuffer);

	return 0;
}
