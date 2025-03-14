#include "global.h"

void *linux_thread(void *p)
{
    PTARGS arp = (PTARGS)p;
    TARGS arg = *arp;
    free(arp);
    task(arg);
    return NULL;
}
