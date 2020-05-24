/*
El Real Time Clock(RTC) es el periférico que almacena la hora del sistema.
Mientras la Placa Madre tenga pila, éste llevará la hora y es lo que permite conservar la hora
luego de que la PC se apague y se le quite la energía. El RTC permite leer y configurar la el año,
el mes, el día, la hora, los minutos y los segundos por separado.También permite configurar una 
alarma de la misma forma.Para no consumir tantas direcciones de E / S, se accede de manera diferida.
En el registro de E / S 70h, se elige lo que se quiere leer / escribir y en el registro 71h se hace la lectura.

Por ejemplo, para obtener el los segundos, habría que ejecutar las siguientes líneas :
    mov al, 0 
    out 70h, al
    in ax, 71h

*/
#include <clock.h>
#include <utils.h>

uint8_t getDecimalTimeInfo(uint8_t info){
    return BSDToInt(getBSDTimeInfo(info));
}
