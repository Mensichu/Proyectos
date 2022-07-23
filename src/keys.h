#include <avr/io.h>
#include "keypad.h"
#include "util/delay.h"

unsigned char val = '0';

int contador_visitante = 0;
int contador_local = 0;

void contadores()
{
KEYPAD_init();
//DDRD = 255;
//PORTB = 0B1111;
//while(1){
val = KEYPAD_read();
//LOCAL
if (val == '1') contador_local += 1;
else if (val == '2') contador_local += 2;
else if (val == '3') contador_local += 3;
else if (val == '4') PORTD = 4;
//VISITANTE
else if (val == '5') contador_visitante += 1;
else if (val == '6') contador_visitante += 2;
else if (val == '7') contador_visitante += 3;
else if (val == '8') PORTD = 8;
//}
val = 0;
_delay_ms(300);   

}