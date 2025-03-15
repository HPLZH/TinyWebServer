#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#ifdef _WIN32
#include "win32.h"
#else
#include "linux.h"
#endif

#include "mime.h"
#include "ext.h"
#include "httpcode.h"

extern char port[1024];
extern char root[1024];
extern SOCKET ListenSocket;
extern FILE* logFile;

typedef struct TaskArgs 
{
	SOCKET socket;
	SOCKADDR sockaddr;
	int addrlen;
} 
TARGS, *PTARGS;

// main.c

int main(int, char**);

// config.c

void readConfig(const char*);
int GetIniKeyString(
	const char* key, 
	FILE* fp, 
	char* buf
);
void trimCrLf(char* str);


// task.c

void task(TARGS);
void logRequest(
	TARGS targs, 
	const char* method, 
	const char* path
);
void logResponse(
	TARGS targs, 
	const char* response
);


// response.c

int response(
	char** mem,
	const char* status,
	const char* header,
	const char* content,
	size_t contentLength
);

int responseNoContent(
	char** mem,
	const char* status,
	const char* header
);

int BadRequest(char**);
int Forbidden(char**);
int NotFound(char**);
int MethodNotAllowed(char**);
int InternalServerError(char**);
int HttpCode(
	char** mem, 
	int code, 
	const char* header
);
const char* HttpCodeText(int code);


// header.c

#define HEADER_NO_CONTENT "\
Access-Control-Allow-Origin: *\r\n\
Connection: Keep-Alive\r\n\
Content-Type: text/plain\r\n\
Content-Length: 0\r\n\
Server : hplzh-TinyWebServer\r\n\
"

#define HEADER_405 "\
Access-Control-Allow-Origin: *\r\n\
Allow: GET, HEAD\r\n\
Connection: Keep-Alive\r\n\
Content-Type: text/plain\r\n\
Content-Length: 0\r\n\
Server : hplzh-TinyWebServer\r\n\
"

#define RESPONSE_500 "\
HTTP/1.1 500 Internal Server Error\r\n\
Access-Control-Allow-Origin: *\r\n\
Connection: Keep-Alive\r\n\
Content-Type: text/plain\r\n\
Content-Length: 0\r\n\
Server : hplzh-TinyWebServer\r\n\
"

#define RESPONSE_500_LEN 167

void header(
	char* buf,
	const char* contentType,
	size_t contentLength
);


// fileaccess.c

int fileCheck(char* buf, const char* path);
long fileLength(FILE* stream);

// mime.c

const char* mimeType(const char* fn);
long long extCode(const char* ext);


// url.c

void urlDecode(char url[], size_t);
