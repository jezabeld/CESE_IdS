/************************************************************************************************
SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @brief Implementación del driver GPIO
 *
 * Este archivo contiene la implementación de las funciones para el manejo
 * de GPIO definidas en gpio.h
 *
 * @author Jez - CESE-IdS
 * @version 1.0
 */

/* === Headers files inclusions
 * =============================================================== */

#include "gpio.h"
#include <stdlib.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/** @brief Estructura privada que representa un GPIO
 *
 * Esta estructura contiene toda la información necesaria para
 * manejar un pin GPIO específico.
 */
struct gpio_s {
  uint8_t port;   /**< Puerto del GPIO (0-255) */
  uint8_t pin;    /**< Número de pin dentro del puerto (0-255) */
  bool is_output; /**< true si está configurado como salida, false como entrada
                   */
  bool value;     /**< Valor actual del pin (true=HIGH, false=LOW) */
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */
gpio_t gpioCreate(uint8_t port, uint8_t pin) {
  gpio_t self = malloc(sizeof(struct gpio_s));
  if (self) {
    self->port = port;
    self->pin = pin;
    self->is_output = false;
    self->value = false;
  }
  return self;
}

void gpioSetOutput(gpio_t self, bool value) { self->is_output = value; }

bool gpioSetValue(gpio_t self, bool value) {
  if (self->is_output) {
    self->value = value;
    return true;
  }
  return false;
}

bool gpioGetValue(gpio_t self) { return self->value; }
/* === End of documentation ==================================================================== */
