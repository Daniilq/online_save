#include "Stepper.h"
#include "IRremote.h"

//------------------ИК ПРИЕМНИК------------------//
int receiver = 10; // Сигнальный вывод ИК-приемника на Arduino Digital Pin 6
IRrecv irrecv(receiver);    // создать переменную 'irrecv'
decode_results results;     // создать переменную 'decode_results'
//------------------ИК ПРИЕМНИК------------------//
//------------------ДВИГАТЕЛЬ------------------//
#define STEPS  32   // Количество шагов на оборот внутреннего вала
int  Steps2Take;
Stepper small_stepper(STEPS, 5, 7, 6, 8);// In1, In2, In3, In4 в последовательности 1-3-2-4
//------------------ДВИГАТЕЛЬ------------------//
//------------------РЕЛЕ------------------//
#define PIN_RELAY 9
//------------------РЕЛЕ------------------//
 
void setup()
{ 
//------------------ИК ПРИЕМНИК------------------//  
    Serial.begin(9600); // Выставляем скорость COM порта
    irrecv.enableIRIn(); // запускаем прием
//------------------ИК ПРИЕМНИК------------------//  
//------------------РЕЛЕ------------------//
      digitalWrite(PIN_RELAY, HIGH); // Выключаем реле - посылаем высокий сигнал
    pinMode(PIN_RELAY, OUTPUT); // Объявляем пин реле как выход
//------------------РЕЛЕ------------------//
}
 
void loop()
{
if (irrecv.decode(&results)) // получили ли мы ИК сигнал?
 
  {
    switch(results.value)
 
    {
//------------------ДВИГАТЕЛЬ------------------//
      case 0xFF18E7: // нажата кнопка 1
                      small_stepper.setSpeed(600); //Max seems to be 700
                      Steps2Take  =  -9240;  // Rotate CW
                      small_stepper.step(Steps2Take);
                      delay(1500); 
                      digitalWrite(5,LOW);
                      digitalWrite(6,LOW);
                      digitalWrite(7,LOW);
                      digitalWrite(8,LOW);
                      break;
 
      case 0x5F12E8C4: // канал вверх
                      small_stepper.setSpeed(700); //Max seems to be 700
                      Steps2Take  =  -9240;  // Rotate CW
                      small_stepper.step(Steps2Take);
                      delay(2000); 
                      digitalWrite(5,LOW);
                      digitalWrite(6,LOW);
                      digitalWrite(7,LOW);
                      digitalWrite(8,LOW);
                      break;
             
 
      case 0xFF4AB5: // нажата кнопка 4
                      small_stepper.setSpeed(600);
                      Steps2Take  =  9240;  // Rotate CCW
                      small_stepper.step(Steps2Take);
                      delay(1500); 
                      digitalWrite(5,LOW);
                      digitalWrite(6,LOW);
                      digitalWrite(7,LOW);
                      digitalWrite(8,LOW);
                      break;
                      
      case 0x189D7928: // канал вниз
                      small_stepper.setSpeed(700);
                      Steps2Take  =  9240;  // Rotate CCW
                      small_stepper.step(Steps2Take);
                      delay(2000); 
                      digitalWrite(5,LOW);
                      digitalWrite(6,LOW);
                      digitalWrite(7,LOW);
                      digitalWrite(8,LOW);
                      break;
//------------------ДВИГАТЕЛЬ------------------//  
//------------------РЕЛЕ------------------//
      case 0xFF6897: 
                      digitalWrite(PIN_RELAY, LOW);
                      break;
      case 0xFFB04F: 
                      digitalWrite(PIN_RELAY, HIGH);
                      break;

//------------------РЕЛЕ------------------//                    
    }
    
    Serial.println(results.value, HEX); // Отправляем полученную данную в консоль 
    Serial.println( results.value); // печатаем данные   
    irrecv.resume(); // принимаем следующую команду
  }  
 
 
}
