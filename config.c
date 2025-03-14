#include "global.h"

int GetIniKeyString(
	const char *key, 
	FILE *fp, 
	char *buf
)
{
	char *wTmp;
	char sLine[1024];

	if (NULL == fp)
	{
		return -1;
	}
	int fsr = fseek(fp, 0, SEEK_SET);
	while (NULL != fgets(sLine, 1024, fp))
	{
		if (0 == strncmp("//", sLine, 2))
		{
			continue;
		}
		if ('#' == sLine[0])
		{
			continue;
		}
		wTmp = strchr(sLine, '=');
		if (NULL != wTmp)
		{
			if (0 == strncmp(key, sLine, strlen(key)))
			{
				sLine[strlen(sLine) - 1] = '\0';
				while (*(wTmp + 1) == ' ')
				{
					wTmp++;
				}
				strcpy(buf, wTmp + 1);
				return 0;
			}
		}
	}
	return -1;
}

void readConfig(const char *file)
{
	char buf[1024];
	buf[0] = 0;
	logFile = NULL;
	FILE *conf = fopen(file, "r");
	if (0 != GetIniKeyString("port", conf, port))
	{
		strcpy(port, "80");
	}
	if (0 != GetIniKeyString("root", conf, root))
	{
		strcpy(root, ".");
	}
	if (0 != GetIniKeyString("log", conf, buf))
	{
		buf[0] = 0;
	}
	trimCrLf(port);
	trimCrLf(root);
	trimCrLf(buf);
	if (strlen(buf))
	{
		logFile = fopen(buf, "a");
		if (logFile == NULL)
		{
			printf("Log file open failed: %s\n", strerror(errno));
		}
		else
		{
			printf("Log enabled.\n");
		}
	}
	else
	{
		printf("Log disabled.\n");
	}
	fclose(conf);
}

void trimCrLf(char *str)
{
	char *cp = str;
	while (*cp)
	{
		if (*cp == '\r' || *cp == '\n')
		{
			*cp = 0;
			return;
		}
		else
		{
			cp++;
		}
	}
}
