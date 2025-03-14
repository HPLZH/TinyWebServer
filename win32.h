#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <io.h>

#pragma comment(lib,"Ws2_32.lib" )

extern SOCKET ListenSocket;

// win32main.c

#define Main win32_main
int win32_main(void);

// win32thread.c

DWORD WINAPI win32_thread(PVOID p);


// win32encoding.c

#define Utf8ToGbk Win32Utf8ToGbk
void Win32Utf8ToGbk(char* dst, const char* src_str, size_t, size_t);
