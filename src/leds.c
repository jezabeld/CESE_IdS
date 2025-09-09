#include "leds.h"
#include "errores.h"

#define ALL_LEDS_OFF 0x0000
#define NULL_MASK ALL_LEDS_OFF
#define FIRST_BIT_MASK 0x0001
#define LED_TO_BIT_OFFSET 1

static uint16_t* puerto;

static bool isLedInRange(int led) {
    bool result = (led >= 1 && led <= 16);
    if (!result) {
        registrarWarning("LED fuera de rango");
    }
    return result;
}

static uint16_t ledToMask(int led) {
    if (!isLedInRange(led)) {
        return NULL_MASK;
    }
    return FIRST_BIT_MASK << (led - LED_TO_BIT_OFFSET);
}

void ledsInitDriver(uint16_t* puerto_virtual) {
    puerto = puerto_virtual;
    ledsTurnAllOff();
}

void ledsTurnLedOn(int led) {
    *puerto |= ledToMask(led);
}

void ledsTurnLedOff(int led) {
    *puerto &= ~ledToMask(led);
}

void ledsTurnAllOn(void) {
    *puerto = ~ALL_LEDS_OFF;
}

void ledsTurnAllOff(void) {
    *puerto = ALL_LEDS_OFF;
}

bool ledsGetState(int led) {
    return (*puerto & ledToMask(led)) != 0;
}
