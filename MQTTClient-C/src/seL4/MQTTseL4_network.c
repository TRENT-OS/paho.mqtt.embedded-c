#include "MQTTseL4.h"
#if defined(LWIP)
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "lwip/arch.h"
#endif

static int seL4_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
#if defined(LWIP)
    struct timeval interval = {timeout_ms / 1000, (timeout_ms % 1000) * 1000};
    if (interval.tv_sec < 0 || (interval.tv_sec == 0 && interval.tv_usec <= 0))
    {
        interval.tv_sec = 0;
        interval.tv_usec = 100;
    }

    setsockopt(n->my_socket,
                SOL_SOCKET,
                SO_RCVTIMEO,
                (char *)&interval,
                sizeof(struct timeval));

    int bytes = 0;
    while (bytes < len)
    {
        int rc = recv(n->my_socket, &buffer[bytes], (size_t)(len - bytes), 0);
        if (rc == -1)
        {
            bytes = -1;
            break;
        }
        else if (rc == 0)
        {
            bytes = 0;
            break;
        }
        else
            bytes += rc;
    }
    return bytes;
#else
#   error WE HAVE NO IMPLEMENTATION
#endif
}

static int seL4_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
#if defined(LWIP)
    struct timeval tv;

    tv.tv_sec = 0;  /* 30 Secs Timeout */
    tv.tv_usec = timeout_ms * 1000;// Not init'ing this can cause strange errors

    setsockopt(n->my_socket,
                SOL_SOCKET,
                SO_SNDTIMEO,
                (char *)&tv,
                sizeof(struct timeval));
    int	rc = write(n->my_socket, buffer, len);
    return rc;
#else
#   error WE HAVE NO IMPLEMENTATION
#endif
}

void NetworkInit(Network* n)
{
    n->my_socket    = 0;
    n->mqttread     = seL4_read;
    n->mqttwrite    = seL4_write;
}

int NetworkConnect(Network* n, char* addr, int port)
{
#if defined(LWIP)
    int type = SOCK_STREAM;
    struct sockaddr_in address;
    int rc = -1;
    struct addrinfo *result = NULL;
    struct addrinfo hints = {0, AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP,
                             0, NULL, NULL, NULL};

    if ((rc = getaddrinfo(addr, NULL, &hints, &result)) == 0)
    {
        struct addrinfo* res = result;

        /* prefer ip4 addresses */
        while (res)
        {
            if (res->ai_family == AF_INET)
            {
                result = res;
                break;
            }
            res = res->ai_next;
        }

        if (result->ai_family == AF_INET)
        {
            address.sin_port = htons(port);
            address.sin_family = AF_INET;
            address.sin_addr =
                ((struct sockaddr_in*)(result->ai_addr))->sin_addr;
        }
        else
        {
            rc = -1;
        }
        freeaddrinfo(result);
    }

    if (rc == 0)
    {
        n->my_socket = socket(AF_INET, type, 0);
        if (n->my_socket != -1)
        {
            rc = connect(n->my_socket,
                         (struct sockaddr*)&address,
                          sizeof(address));
        }
        else
        {
            rc = -1;
        }
    }
    return rc;
#else
#   error WE HAVE NO IMPLEMENTATION
#endif
}

void NetworkDisconnect(Network* n)
{
#if  defined(LWIP)
    close(n->my_socket);
#else
#   error WE HAVE NO IMPLEMENTATION
#endif
}
