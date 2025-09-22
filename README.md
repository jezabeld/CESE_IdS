[![validations](https://github.com/jezabeld/CESE_IdS/actions/workflows/validations.yml/badge.svg?branch=tsse_tp3)](https://github.com/jezabeld/CESE_IdS/actions/workflows/validations.yml)
# TSSE

## Trabajo practico 3: Unit Testing

Seleccionar una biblioteca (o componente) del software a desarrollar en el TP final de la
carrera de especialización / maestría y escribir un test unitario con ceedling que incluya por
lo menos 5 test cases. El archivo de test debe tener por lo menos 65 líneas de extensión
Se debe mantener bajo control de versión el código generado.
Entregar:
Repositorio con el archivo con las pruebas unitarias y el código de producción bajo prueba
(preferentemente en bitbucket o github).

### Componente seleccionado

El componente [**InputDrv**](./App/Drivers/InputDrv.h) es un driver de entrada que gestiona 4 botones digitales con debounce y un joystick analógico con filtrado EMA. El driver procesa datos de ADC a 100Hz mediante DMA, implementa una máquina de estados para generar eventos direccionales del joystick (UP/DOWN/LEFT/RIGHT) a 50Hz con funcionalidad de auto-repetición, y maneja interrupciones de botones con timers de debounce.

### Estrategias de Testing Utilizadas

Los tests unitarios implementan varias estrategias para aislar y verificar el comportamiento del componente:

- **Shims/Fakes**: Se crearon headers falsos en [`test/shims/`](./test/shims/) que exponen únicamente las funciones y tipos de datos mínimos necesarios para el testing. Esto evita incluir los archivos HAL originales que presentan una estructura de includes recursiva compleja e implicarían el mockeo de funciones innecesarias.

- **Mocks**: Se utilizan mocks automáticos generados por CMock para todas las dependencias HAL (HAL_ADC, HAL_TIM, HAL_GPIO, HAL_NVIC) y FreeRTOS (xQueueSend, xTimerStart, HAL_GetTick), permitiendo controlar completamente las respuestas de las funciones externas.

- **Callbacks personalizados**: Se implementan callbacks para capturar eventos enviados a las colas de FreeRTOS (`capture_queue_event` y `capture_queue_event_from_isr`) y verificar que se envían los eventos correctos con los IDs esperados.

- **Acceso directo a variables privadas**: Se expone el buffer DMA interno (`dmaBuffer`) mediante declaración externa para poder inyectar datos de prueba específicos y verificar el procesamiento del filtrado EMA.

### Tests Desarrollados

El archivo `test/test_InputDrv.c` contiene 27 tests unitarios que verifican el comportamiento del componente InputDrv:

#### Tests de inputInit (5 tests)
1. `test_inputInit_invalid_parameters_return_error_code` - Valida que inputInit retorna error con parámetros NULL
2. `test_inputInit_valid_parameters_return_success` - Verifica inicialización exitosa con parámetros válidos
3. `test_inputInit_adc_start_dma_fails_return_error` - Verifica fallas en la inicialización del ADC
4. `test_inputInit_tim_base_start_fails_return_error` - Verifica fallas en la inicialización del Timer

#### Tests de inputGetJoyAxis (5 tests)
5. `test_inputGetJoyAxis_null_pointer_returns_error` - Valida puntero NULL del joystick
6. `test_inputGetJoyAxis_invalid_axis_returns_error` - Verifica validación de valores de eje inválidos
7. `test_inputGetJoyAxis_x_axis_returns_success` - Prueba lectura solo del eje X
8. `test_inputGetJoyAxis_y_axis_returns_success` - Prueba lectura solo del eje Y
9. `test_inputGetJoyAxis_both_axes_returns_success` - Prueba lectura de ambos ejes

#### Tests de HAL_GPIO_EXTI_Callback (2 tests)
10. `test_HAL_GPIO_EXTI_Callback_all_buttons_start_debounce_timers` - Verifica inicio de timers de debounce para todos los botones
11. `test_HAL_GPIO_EXTI_Callback_unknown_pin_does_nothing` - Prueba comportamiento con pines desconocidos

#### Tests de callbacks de timers de botones (2 tests)
12. `test_button_timer_callbacks_button_not_pressed_only_enables_irq` - Verifica comportamiento cuando el botón no está presionado
13. `test_button_timer_callbacks_button_pressed_sends_event` - Prueba envío de eventos cuando el botón está presionado

#### Tests de HAL_ADC_ConvHalfCpltCallback (2 tests)
14. `test_HAL_ADC_ConvHalfCpltCallback_wrong_adc_instance_does_nothing` - Verifica que se ignoran callbacks de instancias ADC incorrectas
15. `test_HAL_ADC_ConvHalfCpltCallback_processes_first_half_buffer` - Verifica el proceso de la primera mitad del buffer DMA con filtrado EMA

#### Tests de HAL_ADC_ConvCpltCallback (11 tests)
16. `test_HAL_ADC_ConvCpltCallback_wrong_adc_instance_does_nothing` - Verifica que se ignoran callbacks de instancias ADC incorrectas
17. `test_HAL_ADC_ConvCpltCallback_processes_second_half_buffer` - Verifica el proceso de la segunda mitad del buffer DMA
18. `test_HAL_ADC_ConvCpltCallback_center_position_no_events` - Verifica que la posición central no genera eventos
19. `test_HAL_ADC_ConvCpltCallback_joystick_right_generates_right_event` - Verifica la generación de evento RIGHT al mover joystick a la derecha
20. `test_HAL_ADC_ConvCpltCallback_joystick_left_generates_left_event` - Verifica la generación de evento LEFT al mover joystick a la izquierda
21. `test_HAL_ADC_ConvCpltCallback_joystick_up_generates_up_event` - Verifica la generación de evento UP al mover joystick hacia arriba
22. `test_HAL_ADC_ConvCpltCallback_joystick_down_generates_down_event` - Verifica la generación de evento DOWN al mover joystick hacia abajo
23. `test_HAL_ADC_ConvCpltCallback_joystick_repeat_events_after_delay` - Prueba mecanismo de eventos repetidos con delay
24. `test_HAL_ADC_ConvCpltCallback_active_to_center_transition` - Prueba transición de estado ACTIVE a CENTER
25. `test_HAL_ADC_ConvCpltCallback_repeat_to_center_transition` - Prueba transición de estado REPEAT a CENTER
26. `test_HAL_ADC_ConvCpltCallback_active_to_active_direction_change` - Prueba cambio de dirección en estado ACTIVE
27. `test_HAL_ADC_ConvCpltCallback_repeat_to_active_direction_change` - Prueba cambio de dirección desde estado REPEAT a ACTIVE

### Reporte de covertura

[📊 Coverage HTML](https://jezabeld.github.io/CESE_IdS/pr-5/coverage.html)
