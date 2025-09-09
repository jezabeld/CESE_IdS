#include <stdbool.h>
#include <stdint.h>

void ledsInitDriver(uint16_t* puerto_virtual);

void ledsTurnLedOn(int led);

void ledsTurnLedOff(int led);

void ledsTurnAllOn(void);

void ledsTurnAllOff(void);

bool ledsGetState(int led);
