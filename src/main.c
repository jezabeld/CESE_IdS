/************************************************************************************************
SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file main.c
 * @brief Programa principal
 *
 * @author Jez - CESE-IdS
 * @version 1.0
 */

/* === Headers files inclusions =============================================================== */

#include "gpio.h"

/* === Macros definitions ====================================================================== */

/** @brief Puerto del LED rojo */
#define LED_ROJO_PORT 0

/** @brief Pin del LED rojo */
#define LED_ROJO_PIN 1

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

/** @brief Función principal del programa
 *
 * Demuestra el uso básico del driver GPIO creando una instancia
 * para un LED, configurándolo como salida y encendiéndolo.
 *
 * @return 0 si la ejecución fue exitosa
 */
int main(void) {
  gpio_t led_rojo = gpioCreate(LED_ROJO_PORT, LED_ROJO_PIN);

  gpioSetOutput(led_rojo, true);
  gpioSetValue(led_rojo, true);

  return 0;
}
/* === End of documentation ==================================================================== */
