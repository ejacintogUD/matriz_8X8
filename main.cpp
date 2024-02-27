/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ThisThread.h"
#include "Thread.h"
#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

BusOut Colums(D13,D12,D10,D15,D14,PA_11, PA_12,D11);
BusOut Rows(D9,D8, D7, D6, D4,D5, D2, D3 ); 

const char columnas[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
const char filas[90]    = { 0xFF,	 0xFF,	 0x18,	 0x18,	 0x18,	 0x18,	 0xFF,	 0xFF,	0x00,
                            0xFF,	 0xFF,	 0xC3,	 0xC3,	 0xC3,	 0xC3,	 0xFF,	 0xFF,	0x00,
                            0x00,	 0xFF,	 0xFF,	 0x03,	 0x03,	 0x03,	 0x03,	 0x00,	0x00,
                            0x1F,	 0x7F,	 0xEC,	 0xCC,	 0xCC,	 0xEC,	 0x7F,	 0x1F,	0x00,
                            0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	 0x00,	0x00,
                            0xFF,	 0xFF,	 0x60,	 0x30,	 0x30,	 0x60,	 0xFF,	 0xFF,	0x00,
                            0xFC,	 0xFE,	 0x03,	 0x03,	 0x03,	 0x03,	 0xFE,	 0xFC,	0x00,
                            0xFF,	 0xFF,	 0x70,	 0x38,	 0x1C,	 0x0E,	 0xFF,	 0xFF,	0x00,
                            0xFF,	 0xFF,	 0xC3,	 0xC3,	 0xC3,	 0xE7,	 0x7E,	 0x3C,	0x00,
                            0xFF,	 0xFF,	 0xC3,	 0xC3,	 0xC3,	 0xC3,	 0xFF,	 0xFF,	0x00};

Thread hilo_visualiza;
Thread hilo_corre;

void visualiza (void);
void corre (void);

static int i=0, j=0;


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    hilo_visualiza.start(visualiza);
    hilo_corre.start(corre);
    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}

void corre (void)
{
    while (true)
    {
    j++;
    if (j==82) j=0;

    ThisThread::sleep_for(100ms);
    }

}


void visualiza (void)
{
    static int i;

    while(true)
    {
        Colums = ~columnas[i];
        Rows = ~filas[i+j];
        i++;
        if (i==8) i=0;
        ThisThread::sleep_for(2ms);
    }
}
