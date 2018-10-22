#if !defined(__MQTT_SEL4_)
#define __MQTT_SEL4_

#include <stdint.h>
#include "uart_hdlc.h"
#include "uart_io_guest.h"

typedef struct Timer
{
    void*           impl;
    uint64_t 	    startNS;
    unsigned        timeSpanMS;
}
Timer;

void TimerInit(Timer*);
char TimerIsExpired(Timer*);
void TimerCountdownMS(Timer*, unsigned int);
void TimerCountdown(Timer*, unsigned int);
int TimerLeftMS(Timer*);

typedef struct Network
{
    UartIoGuest uart;
    UartHdlc    uartHdlc;
    int (*mqttread) (struct Network*, unsigned char*, int, int);
    int (*mqttwrite) (struct Network*, unsigned char*, int, int);
}
Network;

void NetworkInit(Network*);
int NetworkConnect(Network*, char*, int);
void NetworkDisconnect(Network*);

#endif
