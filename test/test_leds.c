/*
 * 1. Prender un led y verificar que no cambia el resto.
 * 2. Prender un led y apagarlo.
 * 3. Prender más de un led, apagar uno y verificar que el resto siguen sin cambio.
 * 4. Prender un led y apagarlo en ambos extremos (led 1 y led 16).
 * 5. Iniciar el driver y revisar que todos los leds estén apagados.
 * 6. Prender todos los leds.
 * 7. Prender y apagar todos los leds.
 * 8. Prender algunos leds más de una vez y verificar que siguen prendidos.
 * 9. Apagar algunos leds más de una vez y verificar que siguen apagados.
 * 10. Prender algunos leds, después prender todos y comprobar que todos los leds quedan encendidos.
 * 11. Prender todos, apagar algunos, luego apagar todos y comprobar que todos los leds quedan apagados.
 * 12. Consultar el estado de un led encendido y comprobar que es correcto.
 * 13. Consultar el estado de un led apagado y comprobar que es correcto.
 * 14. Intentar manipular un led fuera de rango y comprobar que se genera un error.
*/
#include "unity.h"
#include "leds.h"

void setUp(void){ // si no las creamos nosotros se crean automaticamente por ceedling vacias

}
void tearDown(void){

}
// * 5. Iniciar el driver y revisar que todos los leds estén apagados.
void test_al_iniciar_todos_leds_apagados(void){
	uint16_t puerto_virtual = 0xFFFF; // mock de HW

	ledsInitDriver(&puerto_virtual);
	TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}