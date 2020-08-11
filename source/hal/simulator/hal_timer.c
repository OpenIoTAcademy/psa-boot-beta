#include "hal_timer.h"

#include <Windows.h>

void hal_timer_sleep(uint32_t sleep_time_in_ms)
{
    Sleep(sleep_time_in_ms);
}
