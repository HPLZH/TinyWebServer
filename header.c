#include "global.h"

void header(
	char *buf,
	const char *contentType,
	size_t contentLength)
{
	sprintf(buf, "\
Access-Control-Allow-Origin: *\r\n\
Connection: Keep-Alive\r\n\
Content-Type: %s\r\n\
Content-Length: %zd\r\n\
Server : hplzh-TinyWebServer\r\n\
",
			contentType,
			contentLength);
}
