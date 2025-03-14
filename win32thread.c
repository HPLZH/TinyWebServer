#include "global.h"

DWORD WINAPI win32_thread(PVOID p) 
{
	PTARGS arp = (PTARGS)p;
	TARGS arg = *arp;
	free(arp);
	task(arg);
	return 0;
}
