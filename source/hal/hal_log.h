
#ifndef __HAL_LOG_H
#define __HAL_LOG_H

#include "boot_types.h"

#ifdef LOG_PRINTF
#undef LOG_PRINTF
#endif

#define LOG_PRINTF hal_log_printf

void hal_log_printf(char* format, ...);

#endif