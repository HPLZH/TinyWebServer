#include "global.h"

char port[1024];
char root[1024];
SOCKET ListenSocket;
FILE* logFile;

int main(int argc, char** argv) 
{
	char buf[1024];
	if (argc > 1)
	{
		strcpy(buf, argv[1]);
	}
	else
	{
		strcpy(buf, "webserver.ini");
	}
	printf("Config file: %s\n", buf);
	readConfig(buf);
	printf("Port: %s\n", port);
	printf("Root path: %s\n", root);
	return Main();
}

// #copy "config.c"
// #copy "fileaccess.c"
// #copy "header.c"
// #copy "mime.c"
// #copy "response.c"
// #copy "task.c"
// #copy "url.c"

#ifdef _WIN32
// #copy "win32encoding.c"
// #copy "win32main.c"
// #copy "win32thread.c"
#else
// #copy "linuxencoding.c"
// #copy "linuxmain.c"
// #copy "linuxthread.c"
#endif
