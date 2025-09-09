#include "leds.h"

static uint16_t* puerto;

void ledsInitDriver(uint16_t* puerto_virtual) {
    puerto = puerto_virtual;
    *puerto = 0x0000; // Apagar todos los leds al iniciar
}

void ledsTurnLedOn(int led) { *puerto = (1 << 2); }
