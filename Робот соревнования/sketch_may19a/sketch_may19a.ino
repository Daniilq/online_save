#include <Servo.h>

Servo servo;  // Создаем объект
const int DT1 = 0;
const int DT2 = 1;
const int DT3 = 2;
const int DT4 = 3;
const int DT5 = 4;
const int DT6 = 5;
const int DT7 = 6;
const int DT8 = 7;
const int DT9 = 8;
const int DT10 = 9;
const int DT11 = 10;

void setup() {
  servo.attach(12);   // Указываем объекту класса Servo, что серво присоединен к пину 9
  servo.write(90);   // Выставляем начальное положение 
  }

void loop() {
  int A = analogRead(DT1);
  int B = analogRead(DT11);
  
    if(A<500 && B>500)
  {
        
  servo.write(110);          
}

  else if(A>500 && B<500)
  {
        
  servo.write(60);          
}
  
 else
 {
    servo.write(90);
  }
  delay(1000);
}
