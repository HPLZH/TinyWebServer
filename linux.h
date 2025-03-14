#pragma once

#include <unistd.h>
#include <iconv.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

typedef int SOCKET;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)

#define closesocket close;

// linuxmain.c

#define Main linux_main
int linux_main(void);


//linuxthread.c

void* linux_thread(void *p);

// linuxencoding.c

#define Utf8ToGbk LinuxUtf8ToGbk
void LinuxUtf8ToGbk(
    char *dst_str, 
    const char *src_str, 
    size_t, 
    size_t
);