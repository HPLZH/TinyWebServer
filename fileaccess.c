#include "global.h"

#ifndef R_OK
#define R_OK 4
#endif

#ifdef _WIN32
#define access _access
#endif

int fileCheck(
	char *buf,
	const char *path)
{
	char *pn;
	strcpy(buf, root);
	pn = buf + strlen(root);
	strcat(buf, path);
	urlDecode(pn, 1024 - strlen(root));
	if (pn = strchr(buf, '?'))
	{
		*pn = 0;
	}
	if (pn = strchr(buf, '#'))
	{
		*pn = 0;
	}
	if (strlen(buf) == 0)
	{
		return -404;
	}
	char *pls = strrchr(buf, '/');
	char *pld = strrchr(buf, '.');
	if (pld == NULL || (pls && pld < pls))
	{
		strcat(buf, "/");
	}
	if (buf[strlen(buf) - 1] == '/')
	{
		strcat(buf, "index.html");
	}
	if (access(buf, R_OK))
	{
		if (errno == ENOENT)
		{
			return -404;
		}
		else
		{
			return -403;
		}
	}
	else
	{
		return 0;
	}
}

long fileLength(FILE *stream)
{
	long file_size = -1;
	long cur_offset = ftell(stream); // 获取当前偏移位置
	if (cur_offset == -1)
	{
		printf("ftell failed :%s\n",
			   strerror(errno));
		return -1;
	}
	if (fseek(stream, 0, SEEK_END) != 0)
	{
		// 移动文件指针到文件末尾
		printf("fseek failed: %s\n",
			   strerror(errno));
		return -1;
	}
	file_size = ftell(stream); // 获取此时偏移值，即文件大小
	if (file_size == -1)
	{
		printf("ftell failed :%s\n",
			   strerror(errno));
	}
	if (fseek(stream, cur_offset, SEEK_SET) != 0)
	{ // 将文件指针恢复初始位置
		printf("fseek failed: %s\n",
			   strerror(errno));
		return -1;
	}
	return file_size;
}
