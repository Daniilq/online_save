#include "IRremote.h"
//------------------ИК ПРИЕМНИК------------------//
IRrecv irrecv(7); // указываем вывод, к которому подключен приемник
decode_results results;
//------------------ИК ПРИЕМНИК------------------//
//------------------РЕЛЕ------------------//
#define PIN_RELAY 9
//------------------РЕЛЕ------------------//
//------------------ДВИГАТЕЛЬ------------------//
int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;
const int dl = 1;
//------------------ДВИГАТЕЛЬ------------------//
void setup() {
    Serial.begin(9600); // Выставляем скорость COM порта
    irrecv.enableIRIn(); // запускаем прием
    digitalWrite(PIN_RELAY, HIGH); // Выключаем реле - посылаем высокий сигнал
    pinMode(PIN_RELAY, OUTPUT); // Объявляем пин реле как выход
    
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}
//--------ДВИГАТЕЛЬ--------
void open_r()
{ 
  digitalWrite( in1, LOW );
    digitalWrite( in2, LOW );
      digitalWrite( in3, HIGH );
        digitalWrite( in4, HIGH );
  delay(dl);

  digitalWrite( in1, LOW );
     digitalWrite( in2, LOW );
      digitalWrite( in3, HIGH );
        digitalWrite( in4, LOW );
  delay(dl);

  digitalWrite( in1, LOW );
    digitalWrite( in2, HIGH );
     digitalWrite( in3, HIGH );
      digitalWrite( in4, LOW );


  digitalWrite( in1, HIGH );
    digitalWrite( in2, HIGH );
      digitalWrite( in3, LOW );
       digitalWrite( in4, LOW );
  delay(dl);

  digitalWrite( in1, HIGH );
   digitalWrite( in2, LOW );
     digitalWrite( in3, LOW );
       digitalWrite( in4, LOW );
  delay(dl);

  digitalWrite( in1, HIGH );
    digitalWrite( in2, LOW );
     digitalWrite( in3, LOW );
       digitalWrite( in4, HIGH );
  delay(dl);

  digitalWrite( in1, LOW );
    digitalWrite( in2, LOW );
      digitalWrite( in3, LOW );
        digitalWrite( in4, HIGH );
  delay(dl);
}

void close_r(){
   
  digitalWrite( in1, HIGH ); 
    digitalWrite( in2, LOW ); 
      digitalWrite( in3, LOW ); 
        digitalWrite( in4, LOW );
  delay(dl);

  digitalWrite( in1, HIGH ); 
    digitalWrite( in2, HIGH ); 
      digitalWrite( in3, LOW ); 
        digitalWrite( in4, LOW );
  delay(dl);

  digitalWrite( in1, LOW ); 
     digitalWrite( in2, HIGH ); 
      digitalWrite( in3, LOW ); 
        digitalWrite( in4, LOW );
  delay(dl);

  digitalWrite( in1, LOW ); 
    digitalWrite( in2, HIGH ); 
      digitalWrite( in3, HIGH ); 
       digitalWrite( in4, LOW );
  delay(dl);

  digitalWrite( in1, LOW ); 
    digitalWrite( in2, LOW ); 
      digitalWrite( in3, HIGH ); 
        digitalWrite( in4, LOW );
  delay(dl);

  digitalWrite( in1, LOW ); 
     digitalWrite( in2, LOW ); 
      digitalWrite( in3, HIGH ); 
         digitalWrite( in4, HIGH );
  delay(dl);

  digitalWrite( in1, LOW ); 
    digitalWrite( in2, LOW ); 
      digitalWrite( in3, LOW ); 
        digitalWrite( in4, HIGH );
  delay(dl);

  digitalWrite( in1, HIGH ); 
    digitalWrite( in2, LOW ); 
      digitalWrite( in3, LOW ); 
        digitalWrite( in4, HIGH );
  delay(dl);
}
//--------ДВИГАТЕЛЬ-------- 

void loop() {
  if ( irrecv.decode( &results )) {
  switch ( results.value ) 
  {
   case 16724175: //1
   open_r();
   break;
   
     
   case 16716015: //4
   close_r();
   break;
    }
    Serial.println(results.value, HEX); // Отправляем полученную данную в консоль 
    Serial.println( results.value); // печатаем данные   
    irrecv.resume(); // принимаем следующую команду
}
}
