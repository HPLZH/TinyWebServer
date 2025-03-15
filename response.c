#include "global.h"

#define VER_LEN 8
#define SPACE_LEN 1
#define CRLF_LEN 2

int response(
    char **mem,
    const char *status,
    const char *header,
    const char *content,
    size_t contentLength)
{
    size_t hlength =
        VER_LEN + SPACE_LEN +
        strlen(status) + CRLF_LEN +
        strlen(header) + CRLF_LEN;

    *mem = malloc(hlength + contentLength + 1);
    {
        if (*mem == NULL)
            return -1;
    }
    sprintf(*mem, "HTTP/1.1 %s\r\n%s\r\n", status, header);
    memcpy(*mem + hlength, content, contentLength);
    return hlength + contentLength;
}

int responseNoContent(
    char **mem,
    const char *status,
    const char *header)
{
    size_t hlength =
        VER_LEN + SPACE_LEN +
        strlen(status) + CRLF_LEN +
        strlen(header) + CRLF_LEN;

    *mem = malloc(hlength + 1);
    {
        if (mem == NULL)
            return -1;
    }
    sprintf(*mem, "HTTP/1.1 %s\r\n%s\r\n", status, header);
    return hlength;
}

int BadRequest(
    char **mem)
{
    return responseNoContent(mem,
                             HTTP_400, HEADER_NO_CONTENT);
}

int Forbidden(
    char **mem)
{
    return responseNoContent(mem,
                             HTTP_403, HEADER_NO_CONTENT);
}

int NotFound(
    char **mem)
{
    return responseNoContent(mem,
                             HTTP_404, HEADER_NO_CONTENT);
}

int MethodNotAllowed(
    char **mem)
{
    return responseNoContent(mem,
                             HTTP_405, HEADER_405);
}

int InternalServerError(
    char **mem)
{
    return responseNoContent(mem,
                             HTTP_500, HEADER_NO_CONTENT);
}

int HttpCode(char **mem, int code, const char *header)
{
    return responseNoContent(mem, HttpCodeText(code), header);
}

const char *HttpCodeText(int code)
{
    switch (code)
    {
    case 100:
    {
        return HTTP_100;
    }
    case 101:
    {
        return HTTP_101;
    }
    case 102:
    {
        return HTTP_102;
    }
    case 103:
    {
        return HTTP_103;
    }
    case 200:
    {
        return HTTP_200;
    }
    case 201:
    {
        return HTTP_201;
    }
    case 202:
    {
        return HTTP_202;
    }
    case 203:
    {
        return HTTP_203;
    }
    case 204:
    {
        return HTTP_204;
    }
    case 205:
    {
        return HTTP_205;
    }
    case 206:
    {
        return HTTP_206;
    }
    case 207:
    {
        return HTTP_207;
    }
    case 208:
    {
        return HTTP_208;
    }
    case 226:
    {
        return HTTP_226;
    }
    case 300:
    {
        return HTTP_300;
    }
    case 301:
    {
        return HTTP_301;
    }
    case 302:
    {
        return HTTP_302;
    }
    case 303:
    {
        return HTTP_303;
    }
    case 304:
    {
        return HTTP_304;
    }
    case 307:
    {
        return HTTP_307;
    }
    case 308:
    {
        return HTTP_308;
    }
    case 400:
    {
        return HTTP_400;
    }
    case 401:
    {
        return HTTP_401;
    }
    case 402:
    {
        return HTTP_402;
    }
    case 403:
    {
        return HTTP_403;
    }
    case 404:
    {
        return HTTP_404;
    }
    case 405:
    {
        return HTTP_405;
    }
    case 406:
    {
        return HTTP_406;
    }
    case 407:
    {
        return HTTP_407;
    }
    case 408:
    {
        return HTTP_408;
    }
    case 409:
    {
        return HTTP_409;
    }
    case 410:
    {
        return HTTP_410;
    }
    case 411:
    {
        return HTTP_411;
    }
    case 412:
    {
        return HTTP_412;
    }
    case 413:
    {
        return HTTP_413;
    }
    case 414:
    {
        return HTTP_414;
    }
    case 415:
    {
        return HTTP_415;
    }
    case 416:
    {
        return HTTP_416;
    }
    case 417:
    {
        return HTTP_417;
    }
    case 418:
    {
        return HTTP_418;
    }
    case 421:
    {
        return HTTP_421;
    }
    case 422:
    {
        return HTTP_422;
    }
    case 423:
    {
        return HTTP_423;
    }
    case 424:
    {
        return HTTP_424;
    }
    case 425:
    {
        return HTTP_425;
    }
    case 426:
    {
        return HTTP_426;
    }
    case 428:
    {
        return HTTP_428;
    }
    case 429:
    {
        return HTTP_429;
    }
    case 431:
    {
        return HTTP_431;
    }
    case 451:
    {
        return HTTP_451;
    }
    case 500:
    {
        return HTTP_500;
    }
    case 501:
    {
        return HTTP_501;
    }
    case 502:
    {
        return HTTP_502;
    }
    case 503:
    {
        return HTTP_503;
    }
    case 504:
    {
        return HTTP_504;
    }
    case 505:
    {
        return HTTP_505;
    }
    case 506:
    {
        return HTTP_506;
    }
    case 507:
    {
        return HTTP_507;
    }
    case 508:
    {
        return HTTP_508;
    }
    case 510:
    {
        return HTTP_510;
    }
    case 511:
    {
        return HTTP_511;
    }
    default:
    {
        return HTTP_200;
    }
    }
}