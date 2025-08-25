/************************************************************************************************
SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @brief Brief description of the file
 *
 * Full file description
 *
 */

/* === Headers files inclusions =============================================================== */

#include "gpio.h"

/* === Macros definitions ====================================================================== */
#define LED_ROJO_PORT 0
#define LED_ROJO_PIN 1

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */
int main(void) {
  gpio_t led_rojo = gpioCreate(LED_ROJO_PORT, LED_ROJO_PIN);

  gpioSetOutput(led_rojo, true);
  gpioSetValue(led_rojo, true);

  return 0;
}
/* === End of documentation ==================================================================== */
