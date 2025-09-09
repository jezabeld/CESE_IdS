#include "leds.h"

#define ALL_LEDS_OFF 0x0000
#define FIRST_BIT_MASK 0x0001
#define LED_TO_BIT_OFFSET 1

static uint16_t* puerto;

static uint16_t ledToMask(int led) {
    return 0x0001 << (led - LED_TO_BIT_OFFSET);
}

void ledsInitDriver(uint16_t* puerto_virtual) {
    puerto = puerto_virtual;
    *puerto = ALL_LEDS_OFF;
}

void ledsTurnLedOn(int led) {
    *puerto |= ledToMask(led);
}

void ledsTurnLedOff(int led) {
    *puerto &= ~ledToMask(led);
}
