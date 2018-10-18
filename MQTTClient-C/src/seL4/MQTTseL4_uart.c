#include <stdio.h>
#include "MQTTseL4.h"
#include "uart_hdlc.h"
#include "uart_io_guest.h"

static UartIoGuest uart;

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
    n->my_socket    = 0;
    n->mqttread     = seL4_read;
    n->mqttwrite    = seL4_write;

    UartIoGuestInit(&uart, true, NULL);
    UartHdlcInit(&uart.implementation);
}

int NetworkConnect(Network* n, char* addr, int port)
{
    return UartHdlcOpen();
}

void NetworkDisconnect(Network* n)
{
    UartHdlcClose();
}
