#include "global.h"

void Win32Utf8ToGbk(char* dst, const char* src_str, size_t s1, size_t s2)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t wszGBK[1024];
	memset(wszGBK, 0, sizeof(wszGBK));
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char szGBK[1024];
	memset(szGBK, 0, sizeof(szGBK));
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	strcpy(dst, szGBK);
}
