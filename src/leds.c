#include "leds.h"

void ledsInitDriver(uint16_t * puerto_virtual){
	*puerto_virtual = 0x0000; // Apagar todos los leds al iniciar
}