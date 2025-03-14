#include "global.h"

#ifdef _WIN32
#define WSA_GET_ERROR WSAGetLastError()
#else
#define WSA_GET_ERROR errno
#endif

void task(TARGS args) 
{
	SOCKET s = args.socket;
	char buf[1024];
	int len;

	char* dp = NULL;
	char* rp = NULL;

	char* rdata = NULL;
	int rsize = 0;

	char* sdata = NULL;
	int ssize = 0;

	char method[64];
	char path[256];
	char ver[64];

	while (len = recv(s, buf, 1024, 0))
	{
		if (len == SOCKET_ERROR) 
		{
			printf("Error at recv(): %d\n", WSA_GET_ERROR);
			break;
		}

		if (rsize == 0) 
		{
			rp = realloc(rdata, (size_t)len + 1);
			if (rp == NULL) 
			{
				if (rdata)
				{
					free(rdata);
				}
				if (sdata)
				{
					free(sdata);
				}
				send(s, RESPONSE_500, RESPONSE_500_LEN, 0);
				closesocket(s);
				return;
			}
			else
			{
				rdata = rp;
			}
			memcpy(rdata, buf, len);
			rsize = len;
			rdata[rsize] = 0;
		}
		else
		{
			rp = realloc(rdata, rsize + len + 1);
			if (rp == NULL)
			{
				if (rdata) free(rdata);
				send(s, RESPONSE_500, RESPONSE_500_LEN, 0);
				closesocket(s);
				return;
			}
			else
				rdata = rp;
			memcpy(rdata + rsize, buf, len);
			rsize += len;
			rdata[rsize] = 0;
		}

		if (dp = strstr(rdata, "\r\n\r\n")) 
		{
			int m = sscanf(rdata, "%s %s %s", method, path, ver);
			if (m == 3) 
			{
				logRequest(args, method, path);
				memset(path + strlen(path), 0, 256 - strlen(path));
				int mr = 0;
				if (0 == strcmp(method, "GET")) 
				{
					mr = 1;
				}
				else if (0 == strcmp(method, "HEAD")) 
				{
					mr = 0;
				}
				else {
					ssize = MethodNotAllowed(&sdata);
					if (ssize == -1) 
					{
						if (rdata) free(rdata);
						if (sdata) free(sdata);
						send(s, RESPONSE_500, RESPONSE_500_LEN, 0);
						closesocket(s);
						return;
					}
					logResponse(args, HTTP_405);
					send(s, sdata, ssize, 0);
					free(sdata);
					ssize = 0;
					break;
				}
				int chcode = 0;
				const char* ppath = path;
				if (0 == strncmp(path, "/@/", 3)) 
				{
					ppath += 6;
					if (*ppath != '/') 
					{
						ppath = path;
					}
					else
					{
						char tmpbuf[4];
						memcpy(tmpbuf, path + 3, 3);
						tmpbuf[3] = 0;
						chcode = atoi(tmpbuf);
						if (chcode == 0) 
						{
							ppath = path;
						}
					}
				}
				int fcr = fileCheck(buf, ppath);
				FILE* fc = NULL;
				long fl = 0;
				if (fcr == 0) 
				{
					fc = fopen(buf, "rb");
					const char* ctype;
					if (fc == NULL) 
					{
						fcr = -500;
						ssize = InternalServerError(&sdata);
						if (ssize == -1) 
						{
							if (fc) 
							{
								fclose(fc);
							}
							if (rdata) 
							{
								free(rdata);
							}
							if (sdata) 
							{
								free(sdata);
							}
							send(s, RESPONSE_500, RESPONSE_500_LEN, 0);
							closesocket(s);
							return;
						}
						logResponse(args, HTTP_500);
					}
					else
					{
						ctype = mimeType(buf);
						header(buf, ctype, fl = fileLength(fc));
						if (chcode == 0)
						{
							ssize = responseNoContent(&sdata, HTTP_200, buf);
						}
						else
						{
							ssize = HttpCode(&sdata, chcode, buf);
						}
						if (ssize == -1) 
						{
							if (fc) 
							{
								fclose(fc);
							}
							if (rdata) 
							{
								free(rdata);
							}
							if (sdata) 
							{
								free(sdata);
							}
							send(s, RESPONSE_500, RESPONSE_500_LEN, 0);
							closesocket(s);
							return;
						}
						if (chcode == 0)
						{
							logResponse(args, HTTP_200);
						}
						else
						{
							logResponse(args, HttpCodeText(chcode));
						}
					}
				}
				else if (fcr == -403) 
				{
					ssize = Forbidden(&sdata);
					if (ssize == -1) 
					{
						if (fc) fclose(fc);
						if (rdata) free(rdata);
						if (sdata) free(sdata);
						send(s, RESPONSE_500, RESPONSE_500_LEN, 0);
						closesocket(s);
						return;
					}
					logResponse(args, HTTP_403);
				}
				else if (fcr == -404) 
				{
					ssize = NotFound(&sdata);
					if (ssize == -1) 
					{
						if (fc) fclose(fc);
						if (rdata) free(rdata);
						if (sdata) free(sdata);
						send(s, RESPONSE_500, RESPONSE_500_LEN, 0);
						closesocket(s);
						return;
					}
					logResponse(args, HTTP_404);
				}
				else {
					ssize = InternalServerError(&sdata);
					if (ssize == -1) 
					{
						if (fc) fclose(fc);
						if (rdata) free(rdata);
						if (sdata) free(sdata);
						send(s, RESPONSE_500, RESPONSE_500_LEN, 0);
						closesocket(s);
						return;
					}
					logResponse(args, HTTP_500);
				}
				send(s, sdata, ssize, 0);
				if (fcr == 0 && mr) 
				{
					size_t scount = 0;
					size_t slen = 0;
					while (slen = fread(buf, 1, 1024, fc))
					{
						send(s, buf, slen, 0);
						scount += slen;
						if (slen != 1024)
							break;
					}
					if (scount < fl) 
					{
						memset(buf, 0, 1024);
						while (scount < fl)
						{
							if (fl - scount < 1024) 
							{
								send(s, buf, fl - scount, 0);
								break;
							}
							else
							{
								send(s, buf, 1024, 0);
								scount += 1024;
							}
						}
					}
				}
				if (fc)
				{
					fclose(fc);
				}
				free(sdata);
				ssize = 0;
			}
			else
			{
				logRequest(args, "NULL", "Bad Request");
				ssize = BadRequest(&sdata);
				if (ssize == -1) 
				{
					if (rdata) free(rdata);
					if (sdata) free(sdata);
					send(s, RESPONSE_500, RESPONSE_500_LEN, 0);
					closesocket(s);
					return;
				}
				logResponse(args, HTTP_400);
				send(s, sdata, ssize, 0);
				free(sdata);
				ssize = 0;
				break;
			}

			memcpy(rdata, dp + 4, (rdata + rsize) - (dp + 4));
			rsize = (rdata + rsize) - (dp + 4);
			rdata[rsize] = 0;
		}
	}

	closesocket(s);
	free(rdata);
	rsize = 0;
}

void logRequest(TARGS targs, const char* method, const char* path) 
{
	time_t curt = time(NULL);
	struct tm* p;
	IN_ADDR addr;
	memcpy(&addr, targs.sockaddr.sa_data + 2, sizeof(addr));
	p = localtime(&curt);

	printf("[%04d-%02d-%02d %02d:%02d:%02d] IP %-16s %-8s  %s\n",
		1900 + p->tm_year,
		1 + p->tm_mon,
		p->tm_mday,
		p->tm_hour,
		p->tm_min,
		p->tm_sec,
		inet_ntoa(addr),
		method,
		path);

	if (logFile) 
	{
		fprintf(logFile, "[%04d-%02d-%02d %02d:%02d:%02d] IP %-16s %-8s  %s\n",
			1900 + p->tm_year,
			1 + p->tm_mon,
			p->tm_mday,
			p->tm_hour,
			p->tm_min,
			p->tm_sec,
			inet_ntoa(addr),
			method,
			path);
		fflush(logFile);
	}
}

void logResponse(TARGS targs, const char* response) 
{
	time_t curt = time(NULL);
	struct tm* p;
	IN_ADDR addr;
	memcpy(&addr, targs.sockaddr.sa_data + 2, sizeof(addr));
	p = localtime(&curt);

	printf("[%04d-%02d-%02d %02d:%02d:%02d] IP %-16s RESPONSE  %s\n",
		1900 + p->tm_year,
		1 + p->tm_mon,
		p->tm_mday,
		p->tm_hour,
		p->tm_min,
		p->tm_sec,
		inet_ntoa(addr),
		response);
	if (logFile) 
	{
		fprintf(logFile, "[%04d-%02d-%02d %02d:%02d:%02d] IP %-16s RESPONSE  %s\n",
			1900 + p->tm_year,
			1 + p->tm_mon,
			p->tm_mday,
			p->tm_hour,
			p->tm_min,
			p->tm_sec,
			inet_ntoa(addr),
			response);
		fflush(logFile);
	}

}
