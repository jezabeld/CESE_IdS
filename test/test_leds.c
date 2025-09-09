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
#include "leds.h"
#include "mock_errores.h"
#include "unity.h"
#include <stdbool.h>

static uint16_t puerto_virtual = 0xFFFF; // mock de HW - puerto tiene que ser determinable (segun reqs)

void setUp(void) {
    ledsInitDriver(&puerto_virtual);
}
void tearDown(void) {
}

// * 5. Iniciar el driver y revisar que todos los leds estén apagados.
void test_al_iniciar_todos_leds_apagados(void) {
    // esta prueba requiere que el puerto este definido e inicializado
    uint16_t puerto_virtual = 0xFFFF;

    ledsInitDriver(&puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// 1. Prender un led y verificar que no cambia el resto.
void test_prender_led_verificar_el_resto_no_cambia(void) {

    // definir el nombre de la funcion que enciende un led, numeracion de los leds
    ledsTurnLedOn(3);
    // si numero los leds del 1 al 16 como dicen los reqs, el led 3 corresponde al bit 0,1,[2]
    TEST_ASSERT_EQUAL_HEX16(1 << 2, puerto_virtual);
    // esta funcion solo testea que el bit 2 este prendido, pero no chequea los demas bits
    // TEST_ASSERT_BIT_HIGH(puerto_virtual, 2);
}
//  * 2. Prender un led y apagarlo.
void test_prender_un_led_cualquiera_y_apagarlo(void) {

    ledsTurnLedOn(3);
    ledsTurnLedOff(3);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

//  * 3. Prender más de un led, apagar uno y verificar que el resto siguen sin cambio.
void test_prender_mas_de_un_led_apagar_uno_verificar_resto(void) {

    ledsTurnLedOn(3);
    ledsTurnLedOn(5);
    ledsTurnLedOff(3);
    TEST_ASSERT_EQUAL_HEX16(1 << 4, puerto_virtual);
}

// * 14. Intentar manipular un led fuera de rango y comprobar que se genera un error.
void test_prender_led_fuera_de_rango_genera_error(void) {
    registrarMsgError_ExpectAnyArgs();
    ledsTurnLedOn(17);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

    registrarMsgError_ExpectAnyArgs();
    ledsTurnLedOn(0);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}
void test_apagar_led_fuera_de_rango_genera_error(void) {
    registrarMsgError_ExpectAnyArgs();
    ledsTurnLedOff(17);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

    registrarMsgError_ExpectAnyArgs();
    ledsTurnLedOff(0);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// * 6. Prender todos los leds.
void test_prender_todos_los_leds(void) {

    ledsTurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puerto_virtual);
}

// * 7. Prender y apagar todos los leds.
void test_prender_y_apagar_todos_los_leds(void) {
    ledsTurnAllOn();
    ledsTurnAllOff();
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// * 12. Consultar el estado de un led encendido y comprobar que es correcto.
void test_consultar_estado_led_encendido(void) {

    ledsTurnLedOn(3);
    bool estado = ledsGetState(3);
    TEST_ASSERT_EQUAL_UINT8(1, estado);
}

// * 13. Consultar el estado de un led apagado y comprobar que es correcto.
void test_consultar_estado_led_apagado(void) {
    ledsTurnAllOn();
    ledsTurnLedOff(3);
    bool estado = ledsGetState(3);
    TEST_ASSERT_EQUAL_UINT8(0, estado);
}

void test_consultar_led_fuera_de_rango_genera_error(void) {
    registrarMsgError_ExpectAnyArgs();
    (void)ledsGetState(17);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

    registrarMsgError_ExpectAnyArgs();
    (void)ledsGetState(0);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// * 4. Prender un led y apagarlo en ambos extremos (led 1 y led 16).
void test_prender_y_apagar_leds_extremos(void) {

    ledsTurnLedOn(1);
    TEST_ASSERT_EQUAL_HEX16(1 << 0, puerto_virtual);
    ledsTurnLedOff(1);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);

    ledsTurnLedOn(16);
    TEST_ASSERT_EQUAL_HEX16(1 << 15, puerto_virtual);
    ledsTurnLedOff(16);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

//  * 8. Prender algunos leds más de una vez y verificar que siguen prendidos.
void test_prender_algunos_leds_mas_de_una_vez_verificar_que_siguen_prendidos(void) {

    ledsTurnLedOn(6);
    ledsTurnLedOn(6);
    TEST_ASSERT_EQUAL_HEX16(1 << 5, puerto_virtual);
}

// * 9. Apagar algunos leds más de una vez y verificar que siguen apagados.
void test_apagar_algunos_leds_mas_de_una_vez_verificar_que_siguen_apagados(void) {

    ledsTurnLedOn(6);
    ledsTurnLedOff(6);
    ledsTurnLedOff(6);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// * 10. Prender algunos leds, después prender todos y comprobar que todos los leds quedan encendidos.
void test_prender_algunos_leds_despues_prender_todos_comprobar_todos_encendidos(void) {

    ledsTurnLedOn(3);
    ledsTurnLedOn(5);
    ledsTurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puerto_virtual);
}
// * 11. Prender todos, apagar algunos, luego apagar todos y comprobar que todos los leds quedan apagados.
void test_prender_todos_apagar_algunos_luego_apagar_todos_comprobar_todos_apagados(void) {

    ledsTurnAllOn();
    ledsTurnLedOff(3);
    ledsTurnLedOff(5);
    ledsTurnAllOff();
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}
