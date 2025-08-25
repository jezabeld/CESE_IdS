/************************************************************************************************
SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @brief Driver GPIO para microcontrolador
 *
 * Este archivo proporciona una capa de abstracción para GPIO que permite
 * crear y gestionar pines GPIO para operaciones de E/S digital.
 *
 * @author Jez - CESE-IdS
 * @version 1.0
 */

#ifndef GPIO_H
#define GPIO_H

/* === Headers files inclusions ================================================================ */
#include <stdint.h>
#include <stdbool.h>

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/** @brief Tipo de datos opaco para representar un GPIO
 *
 * Este tipo representa un manejador para un pin GPIO específico.
 * La estructura interna no es visible para el usuario.
 */
typedef struct gpio_s *gpio_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/** @brief Crea una nueva instancia de GPIO
 *
 * @param port Puerto del GPIO (0-255)
 * @param pin Número de pin dentro del puerto (0-255)
 * @return gpio_t Puntero a la instancia creada, NULL si falla
 */
gpio_t gpioCreate(uint8_t port, uint8_t pin);

/** @brief Configura el GPIO como entrada o salida
 *
 * @param gpio Instancia del GPIO a configurar
 * @param value true para salida, false para entrada
 */
void gpioSetOutput(gpio_t gpio, bool value);

/** @brief Establece el valor de salida del GPIO
 *
 * Solo se permite setear si el GPIO está configurado como salida.
 *
 * @param gpio Instancia del GPIO
 * @param value Valor a establecer (true = HIGH, false = LOW)
 * @return true si la operación fue exitosa, false si el GPIO no es salida
 */
bool gpioSetValue(gpio_t gpio, bool value);

/** @brief Obtiene el valor actual del GPIO
 *
 * Lee el valor del pin GPIO, tanto para entrada como salida.
 *
 * @param gpio Instancia del GPIO a leer
 * @return true si el pin está en HIGH, false si está en LOW
 */
bool gpioGetValue(gpio_t gpio);

/* === End of documentation ==================================================================== */

#endif /* GPIO_H */
