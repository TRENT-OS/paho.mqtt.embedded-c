#include "MQTTseL4.h"

void TimerInit(Timer* timer)
{
    return;
}

char TimerIsExpired(Timer* timer)
{
    return 0;
}

void TimerCountdownMS(Timer* timer, unsigned int timeout)
{
    return 0;
}


void TimerCountdown(Timer* timer, unsigned int timeout)
{
    return 0;
}

int TimerLeftMS(Timer* timer)
{
    return 0;
}

int seL4_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
    return 0;
}


int seL4_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
{
    return 0;
}

void NetworkInit(Network* n)
{
    n->my_socket = 0;
    n->mqttread = seL4_read;
    n->mqttwrite = seL4_write;
}

int NetworkConnect(Network* n, char* addr, int port)
{
    return 0;
}

void NetworkDisconnect(Network* n)
{
    return;
}
