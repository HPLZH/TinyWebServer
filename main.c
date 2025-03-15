#include "global.h"

char port[1024];
char root[1024];
SOCKET ListenSocket;
FILE *logFile;

int main(int argc, char **argv)
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

    if (buf[0] == '-')
    {
        if (strcmp(buf, "-") == 0)
        {
            printf("Log disabled.\n");
            printf("Port: ");
            scanf("%s", port);
            printf("Root path: ");
            scanf("%s", root);
        }
        else if (strcmp(buf, "-v") == 0 ||
                 strcmp(buf, "-V") == 0 ||
                 strcmp(buf, "--version") == 0)
        {
            printf("hplzh - TinyWebServer\n1.1.0\n");
            return 0;
        }
        else if (strcmp(buf, "-h") == 0 ||
                 strcmp(buf, "-?") == 0 ||
                 strcmp(buf, "--help") == 0)
        {
            printf("\
Usage: webserver [config] | - | <option>\n\
\n\
  config \tStart the server with a config file.\n\
         \t[default: webserver.ini]\n\
\n\
  -      \tStart the server and input the args with stdin.\n\
\n\
  option:\n\
\n\
    --version\tDisplay the version of webserver.\n\
    -v, -V\n\
\n\
    --help\tDisplay the help message.\n\
    -h, -?\n\
\n\
\n\
About config file:\n\
\n\
  A config file is an INI file like this:\n\
\n\
    port=8080\n\
    root=./www/\n\
    log=webserver.log\n\
\n\
    port\tthe listening port of webserver\n\
        \t[default: 80]\n\
\n\
    root\tthe www root path of webserver\n\
        \t[default: Current directory (./)]\n\
\n\
    log \tthe path of log file.\n\
        \t[default: Empty (the function will be disabled)]\n\
\n\
");
            return 0;
        }
    }
    else
    {
        readConfig(buf);
        printf("Config file: %s\n", buf);
        printf("Port: %s\n", port);
        printf("Root path: %s\n", root);
    }

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
