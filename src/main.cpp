#include <util/delay.h>
#include <avr/io.h>
#include <LiquidCrystal_I2C.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include <keys.h>//Se encargara de configurar datos del puntaje de los equipos

LiquidCrystal_I2C lcd1(0x3B,16,2);//LCD del tiempo y cuartos
LiquidCrystal_I2C lcd2(0x3D,16,2);//LCD del puntaje y equipo

volatile int tiempo=120,cont=0;
//Interrupcion interna para el conteo del tiempo de partida
void interrupt_TIMER1_Init(){
 cli(); //deshabilitar momentáneamente las interrupciones
 TCCR1B = 0b101; //preescalador 8
 TIMSK1 = 1; // habilitar interrupcion por desbordamiento
 sei(); //habilitar las interrupciones
 TCNT1 = 49911; //1 s // tiempo de la interrupcion
}
//Interrupcion interna por desbordamiento del timer 1
ISR(TIMER1_OVF_vect){ //INTERRUPCIONES //se hace el desplazamiento
 cont=cont+1;
 if(cont==64){
   tiempo--;
   cont=0;
 } 
 TCNT1 = 49911;
}


void setup() {
  //Inicializacion del LCD1
  lcd1.init();
  lcd1.backlight();
  lcd1.setCursor(1,0);
  lcd1.print("hola mundo");
  interrupt_TIMER1_Init();
  
  //Inicializacion del LCD2
  lcd2.init();
  lcd2.backlight();
  lcd2.setCursor(0,0);
  lcd2.print("Visitante");

  lcd2.setCursor(0,1);
  lcd2.print("Local");


}
 int cuarto =1;
void loop() {
  //Valor del tiempo a minutos y segundos
  if(tiempo==0){
    cuarto ++;
    tiempo=120;
    if (cuarto>=5){cuarto=1;}
  }
  //LCD1: actualizacion
  lcd1.setCursor(0,0);
  int minutos = tiempo/60;
  int segundos = tiempo - (minutos*60);
  lcd1.setCursor(0,0);
  lcd1.print("Tiempo");
  lcd1.setCursor(7,0);
  lcd1.print(minutos);
  lcd1.setCursor(8,0);
  lcd1.print(":");
  lcd1.setCursor(9,0);
  lcd1.print(segundos);
  lcd1.setCursor(4,1);
  lcd1.print(cuarto);
  lcd1.setCursor(6,1);
  lcd1.print("Cuarto");
  _delay_ms(200);
  lcd1.clear();

  //LCD2: actualizacion
  lcd2.setCursor(12,0);
  lcd2.print(contador_visitante);
  lcd2.setCursor(12,1);
  lcd2.print(contador_local);
  //Funcion de los botones para el manejo de las anotaciones.
  contadores();
  
}