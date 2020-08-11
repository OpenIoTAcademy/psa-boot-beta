
#ifndef __SIMULATION_H
#define __SIMULATION_H

#include <stdint.h>

typedef void(*LOGCB)(uint8_t*);

void SIM_RegisterLOGCallback(LOGCB logCB);

extern int main(void);

#endif