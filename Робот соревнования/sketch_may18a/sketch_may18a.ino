#include <Servo.h>

Servo servo;  // Создаем объект
int IN1 = 7;
int IN2 = 6;
int ENA = 8;

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
  Serial.begin(9600);   // Скорость работы порта
   servo.attach(12);   // Указываем объекту класса Servo, что серво присоединен к пину 9
  servo.write(90);   // Выставляем начальное положени
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(ENA, OUTPUT);
analogWrite(ENA, 0);
}

void loop(){

  int A = analogRead(DT5);  // Задаем переменную analogValue для считывания показаний  
  int B = analogRead(DT6);
  int C = analogRead(DT7); 
  Serial.println(B);              // Выводим значения
  delay(500);
  if(A<300 && B>300 && C<300)
  {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 200);
  servo.write(90); 
    }
    
 else if (A>300 && B>300 && C<300)
  
  {   
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 200);
  servo.write(0);

  }    
  
 else if (A<300 && B>300 && C>300)
  
  {   
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 200);
  servo.write(180);  
  }


}
