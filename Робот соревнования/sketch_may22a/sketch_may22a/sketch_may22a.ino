#include <Servo.h>
Servo servo;
const int DT4 = 3;
const int DT5 = 4;
const int DT6 = 5;
const int DT7 = 6;
const int DT8 = 7;
void setup() {
servo.attach(12);
servo.write(90);
}

void loop() {
  int A = analogRead(DT5);  // Задаем переменную analogValue для считывания показаний  
  int B = analogRead(DT6);
  int C = analogRead(DT7);
  if(A<200 && B>200 && C<200)
  {
servo.write(180);
  }
  else
  {
    servo.write(90);
    }

}
