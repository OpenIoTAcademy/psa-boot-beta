
#include "simulation.h"

/* Remove the include */
#include <windows.h> // only runs on Windows

extern int Boot_Log(char* format, ...);

int main(void) {

	Sleep(100);

	Boot_Log("Hello World!");

	int cnt = 0;
	while (1) {
		Sleep(1000);
		Boot_Log("I am alive!");
	}

	return 0;
}
