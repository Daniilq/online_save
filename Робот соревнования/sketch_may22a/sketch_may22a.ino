#include <Servo.h>
Servo servo;
float Kp=4,Ki=0,Kd=0;
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
int sensor[11]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int initial_motor_speed=100;
int turn=150;
/*
В данном разделе переменных можно указать свои номера портов для подключения
драйвера двигателей
*/
#define pwm 8
#define MotP1 7
#define MotP2 6

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void setup()
{
  servo.attach(12);
  servo.write(turn); 
   pinMode(pwm,OUTPUT); //PWM Pin 1
   pinMode(MotP1,OUTPUT); //Right Motor Pin 1
   pinMode(MotP2,OUTPUT); //Right Motor Pin 2
   Serial.begin(9600); //Enable Serial Communications
}
void read_sensor_values()
{
   sensor[1] = digitalRead (A0);
   sensor[2] = digitalRead (A1);
   sensor[3] = digitalRead (A2);
   sensor[4] = digitalRead (A3);
   sensor[5] = digitalRead (A4);
   sensor[6] = digitalRead (A5);
   sensor[7] = digitalRead (A6);
   sensor[8] = digitalRead (A7);
   sensor[9] = digitalRead (A8);
   sensor[10] = digitalRead (A9);
   sensor[11] = digitalRead (A10); 

if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==1))
  error=-8;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==1)&&(sensor[11]==1))
  error=-7;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==1)&&(sensor[8]==1)&&(sensor[11]==1))
  error=-6;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==1)&&(sensor[8]==0)&&(sensor[11]==0))
  error=-5;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==1)&&(sensor[9]==1)&&(sensor[8]==0)&&(sensor[11]==0))
  error=-4;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==1)&&(sensor[8]==1)&&(sensor[9]==1)&&(sensor[8]==0)&&(sensor[11]==0))
  error=-3;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==1)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=-2;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==1)&&(sensor[7]==1)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=-1;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==1)&&(sensor[7]==1)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=0;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==1)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=1;
else if((sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==1)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=2;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=3;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=4;
else if((sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==1)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=5;
else if((sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=6;
else if((sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=7;
else if((sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
  error=8;
else if((sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)&&(sensor[5]==0)&&(sensor[6]==0)&&(sensor[7]==0)&&(sensor[8]==0)&&(sensor[9]==0)&&(sensor[8]==0)&&(sensor[11]==0))
if(error==-8) error=-9;
else 
   error=9;
}
void calculate_pid()
{
   P = error;
   I = I + previous_I;
   D = error-previous_error;
   PID_value = (Kp*P) + (Ki*I) + (Kd*D);
   previous_I=I;
   previous_error=error;
}
void motor_control()
{
  //следующие строки кода - заставят бота двигаться вперед
  digitalWrite(MotP1,LOW);
  digitalWrite(MotP2,HIGH);
}
void servo_control()
{
   int servo_turn_1 = turn-PID_value;
   int servo_turn_2 = turn+PID_value;
   
  constrain(servo_turn_1,0,180);  
  constrain(servo_turn_2,0,180);
  
servo.write(servo_turn_1);
servo.write(servo_turn_2);
   }
void loop ()
{
read_sensor_values();
calculate_pid();
motor_control();
servo_control();
}
