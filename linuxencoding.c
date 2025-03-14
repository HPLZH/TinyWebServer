#include "global.h"

void LinuxUtf8ToGbk(char *dst_str, const char *src_str, size_t inLen, size_t outLen)
{
    iconv_t cd;
    char buf[1024];
    strcpy(buf, src_str);
    char **pin = (char **)(&buf);
    char **pout = &dst_str;

    cd = iconv_open("gbk", "utf8");
    if (cd == 0)
        return;
    if (iconv(cd, pin, &inLen, pout, &outLen) == -1)
        return;
    iconv_close(cd);
    *pout = '\0';

    return;
}
