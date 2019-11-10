///////////////////////////////////////////// 
//        RemoteXY include library         // 
///////////////////////////////////////////// 

/* определение режима соединения и подключение библиотеки RemoteXY */ 
#define REMOTEXY_MODE__SOFTWARESERIAL 
#include <SoftwareSerial.h> 
#include <RemoteXY.h> 

/* настройки соединения */ 
#define REMOTEXY_SERIAL_RX 2 
#define REMOTEXY_SERIAL_TX 3 
#define REMOTEXY_SERIAL_SPEED 9600 

/* конфигурация интерфейса  */ 
unsigned char RemoteXY_CONF[] = 
  { 3,0,23,0,1,5,5,15,41,11
  ,43,43,1,2,0,6,5,27,11,5
  ,79,78,0,79,70,70,0 }; 
   
/* структура определяет все переменные вашего интерфейса управления */ 
struct { 

    /* input variable */
  signed char joystick_1_x; /* =-100..100 координата x положения джойстика */
  signed char joystick_1_y; /* =-100..100 координата y положения джойстика */
  unsigned char switch_1;/* =1 если переключатель включен и =0 если отключен */

    /* other variable */
  unsigned char connect_flag;  /* =1 if wire connected, else =0 */

} RemoteXY; 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 

/* определяем пины управления правым мотором */
#define PIN_MOTOR_RIGHT_UP 7
#define PIN_MOTOR_RIGHT_DN 6
#define PIN_MOTOR_RIGHT_SPEED 10

/* определяем пины управления левым мотором */
#define PIN_MOTOR_LEFT_UP 5
#define PIN_MOTOR_LEFT_DN 4
#define PIN_MOTOR_LEFT_SPEED 9

/* определяем пин управления светодиодом */
#define PIN_LED 13


/* определяем два массива с перечислением пинов для каждого мотора */
unsigned char RightMotor[3] = 
  {PIN_MOTOR_RIGHT_UP, PIN_MOTOR_RIGHT_DN, PIN_MOTOR_RIGHT_SPEED};
unsigned char LeftMotor[3] = 
  {PIN_MOTOR_LEFT_UP, PIN_MOTOR_LEFT_DN, PIN_MOTOR_LEFT_SPEED};

/*
   управление скоростью мотора
   motor - ссылка на массив пинов
   v - скорость мотора, может принимать значения от -100 до 100
*/
void Wheel (unsigned char * motor, int v)
{
  if (v>100) v=100;
  if (v<-100) v=-100;
  if (v>0) {
    digitalWrite(motor[0], HIGH); 
    digitalWrite(motor[1], LOW);
    analogWrite(motor[2], v*2.55);
  }
  else if (v<0) {
    digitalWrite(motor[0], LOW);
    digitalWrite(motor[1], HIGH);
    analogWrite(motor[2], (-v)*2.55);
  }
  else {
    digitalWrite(motor[0], LOW);
    digitalWrite(motor[1], LOW);
    analogWrite(motor[2], 0);
  }
}

void setup()
{
  /* инициализация пинов */
  pinMode (PIN_MOTOR_RIGHT_UP, OUTPUT);
  pinMode (PIN_MOTOR_RIGHT_DN, OUTPUT);
  pinMode (PIN_MOTOR_LEFT_UP, OUTPUT);
  pinMode (PIN_MOTOR_LEFT_DN, OUTPUT);
  pinMode (PIN_LED, OUTPUT);

  /* инициализация модуля RemoteXY */
  RemoteXY_Init ();

}

void loop()
{
  /* обработчик событий модуля RemoteXY */
  RemoteXY_Handler ();

  /* управляем пином светодиода */
  digitalWrite (PIN_LED, (RemoteXY.switch_1==0)?LOW:HIGH);

  /* управляем правым мотором */
  Wheel (RightMotor, RemoteXY.joystick_1_y + RemoteXY.joystick_1_x);
  /* управляем левым мотором */
  Wheel (LeftMotor, RemoteXY.joystick_1_y - RemoteXY.joystick_1_x);
}