## TSSE


## Trabajo practico 1: TDD

### Driver de LEDs: Requisitos

- Maneja 16 leds de dos estados (encendido y apagado).
- Se puede prender y apagar un led sin afectar a los otros.
- Se pueden prender y apagar todos los led’s en una sola operación.
- Se puede recuperar el estado actual de un led.
- Los led’s están mapeados en una palabra de 16 bits en memoria en una dirección a determinar.
- Para encender el led se debe escribir un “1” en el bit y para apagarlo se debe escribir un “0”.
- El led 1 corresponde al lsb y el led 16 al msb.
- El reset de hardware no define un estado conocido de los led’s, estos deben ser apagados por software.

### Pruebas

1. Prender un led y verificar que no cambia el resto.
2. Prender un led y apagarlo.
3. Prender más de un led, apagar uno y verificar que el resto siguen sin cambio.
4. Prender un led y apagarlo en ambos extremos (led 1 y led 16).
5. Iniciar el driver y revisar que todos los leds estén apagados.
6. Prender todos los leds.
7. Prender y apagar todos los leds.
8. Prender algunos leds más de una vez y verificar que siguen prendidos.
9. Apagar algunos leds más de una vez y verificar que siguen apagados.
10. Prender algunos leds, después prender todos y comprobar que todos los leds quedan encendidos.
11. Prender todos, apagar algunos, luego apagar todos y comprobar que todos los leds quedan apagados.
12. Consultar el estado de un led encendido y comprobar que es correcto.
13. Consultar el estado de un led apagado y comprobar que es correcto.
14. Intentar manipular un led fuera de rango y comprobar que se genera un error.
