#include <stdio.h>
#include "MQTTseL4.h"

static UartIoGuest uart;
static UartHdlc uartHdlc;

static int seL4_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
    return 0;
}

static int seL4_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
    return 0;
}

void NetworkInit(Network* n)
{
    n->mqttread     = seL4_read;
    n->mqttwrite    = seL4_write;

    UartIoGuestInit(&n->uart, true, NULL);
    UartHdlcInit(&n->uartHdlc, &n->uart.implementation);
}

int NetworkConnect(Network* n, char* addr, int port)
{
    return UartHdlcOpen(&n->uartHdlc);
}

void NetworkDisconnect(Network* n)
{
    UartHdlcClose(&n->uartHdlc);
}
