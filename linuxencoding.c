#include "global.h"

void LinuxUtf8ToGbk(char *dst_str, const char *src_str, size_t inLen, size_t outLen)
{
    iconv_t cd;
    size_t inL = inLen;
    size_t outL = outLen;
    char buf[1024] = {0};
    char obuf[1024] = {0};
    strcpy(buf, src_str);
    char *pib = buf;
    char *pob = obuf;
    char **pin = &pib;
    char **pout = &pob;

    cd = iconv_open("gbk", "utf8");
    if (cd == 0)
    {
        return;
    }
    if (iconv(cd, pin, &inL, pout, &outL) == -1)
    {
        return;
    }
    strncpy(dst_str, obuf, outL);
    iconv_close(cd);
    *pout = 0;

    return;
}
