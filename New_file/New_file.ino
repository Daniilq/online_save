/*
   -- BluetoothRider --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.3.5 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.3.1 or later version;
     - for iOS 1.3.5 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// настройки соединения 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,4,0,0,0,73,0,8,16,0,
  1,5,66,14,22,22,16,24,226,150,
  178,0,1,5,66,38,22,22,16,24,
  226,150,188,0,1,5,3,31,22,22,
  16,24,226,151,128,0,1,5,29,31,
  22,22,16,24,226,150,182,0,129,0,
  12,6,72,10,121,66,108,117,101,116,
  111,111,116,104,82,105,100,101,114,0 };
  
// структура определяет все переменные вашего интерфейса управления 
struct {

    // input variable
  uint8_t button_1; // =1 если кнопка нажата, иначе =0 ВПЕРЕД
  uint8_t button_2; // =1 если кнопка нажата, иначе =0 НАЗАД
  uint8_t button_3; // =1 если кнопка нажата, иначе =0 НАЛЕВО
  uint8_t button_4; // =1 если кнопка нажата, иначе =0 НАПРАВО

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_1 13
#define PIN_BUTTON_2 12
#define PIN_BUTTON_3 11
#define PIN_BUTTON_4 7

#define LEFT_MOTOR_PWM_PIN 10 // ENA
#define LEFT_MOTOR_A_PIN 8 // IN1
#define LEFT_MOTOR_B_PIN 9 // IN2

#define RIGHT_MOTOR_PWM_PIN 6 // ENB
#define RIGHT_MOTOR_A_PIN 5 // IN3
#define RIGHT_MOTOR_B_PIN 4 // IN 4

#define BRAKE_K 100

#define SPEED 200

void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_BUTTON_1, OUTPUT);
  pinMode (PIN_BUTTON_2, OUTPUT);
  pinMode (PIN_BUTTON_3, OUTPUT);
  pinMode (PIN_BUTTON_4, OUTPUT);
  
  pinMode(LEFT_MOTOR_A_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_B_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_PWM_PIN, OUTPUT);

  pinMode(RIGHT_MOTOR_A_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_B_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM_PIN, OUTPUT);
  
  // TODO you setup code
}


void runForward(){        // ВПЕРЕД
  digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_B_PIN, LOW);
  analogWrite(LEFT_MOTOR_PWM_PIN, SPEED);

  digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
  analogWrite(RIGHT_MOTOR_PWM_PIN, SPEED);    
}

void runStop(){       // СТОП
  digitalWrite(LEFT_MOTOR_A_PIN, LOW);
  digitalWrite(LEFT_MOTOR_B_PIN, LOW);
  analogWrite(LEFT_MOTOR_PWM_PIN, LOW);

  digitalWrite(RIGHT_MOTOR_A_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
  analogWrite(RIGHT_MOTOR_PWM_PIN, LOW); 
}

void runBack(){       // НАЗАД
  digitalWrite(LEFT_MOTOR_A_PIN, LOW);
  digitalWrite(LEFT_MOTOR_B_PIN, HIGH);
  analogWrite(LEFT_MOTOR_PWM_PIN, SPEED);

  digitalWrite(RIGHT_MOTOR_A_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_B_PIN, HIGH);
  analogWrite(RIGHT_MOTOR_PWM_PIN, SPEED);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void leftForward(){       // ЛЕВО + ВПЕРЕД
  digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, 150);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, 255);        
}

void left(){       // ЛЕВО
  digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, LOW);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, SPEED);        
}

void leftBack(){       // ЛЕВО + НАЗАД
  digitalWrite(LEFT_MOTOR_A_PIN, LOW);
    digitalWrite(LEFT_MOTOR_B_PIN, HIGH);
    analogWrite(LEFT_MOTOR_PWM_PIN, 150);

    digitalWrite(RIGHT_MOTOR_A_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_B_PIN, HIGH);
    analogWrite(RIGHT_MOTOR_PWM_PIN, 255);        
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RightForward(){        // ПРАВО + ВПЕРЕД
    digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, 255);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, 125);    
}
void Right(){        // ПРАВО
    digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, SPEED);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, LOW);    
}
void RightBack(){        // ПРАВО + НАЗАД
    digitalWrite(LEFT_MOTOR_A_PIN, LOW);
    digitalWrite(LEFT_MOTOR_B_PIN, HIGH);
    analogWrite(LEFT_MOTOR_PWM_PIN, 255);

    digitalWrite(RIGHT_MOTOR_A_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_B_PIN, HIGH);
    analogWrite(RIGHT_MOTOR_PWM_PIN, 125);    
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void machineControl(){
//     if(RemoteXY.button_1 == 1){runForward();} // ВПЕРЕД
//     else if(RemoteXY.button_2 == 1){runBack();} // НАЗАД
//     else if(RemoteXY.button_3 == 1){left();} // ЛЕВО 
//     else if(RemoteXY.button_4 == 1){Right();} // ПРАВО

//     else if(RemoteXY.button_1 == 1 && RemoteXY.button_3 == 1){leftForward();} // ЛЕВО + ВПЕРЕД
//     else if(RemoteXY.button_2 ==1 && RemoteXY.button_3 ==1){leftBack();} // ЛЕВО + НАЗАД 
    
//     else if(RemoteXY.button_1 == 1 && RemoteXY.button_4 == 1){RightForward();} // ПРАВО + ВПЕРЕД
//     else if(RemoteXY.button_2 == 1 && RemoteXY.button_4 == 1){RightBack();} // ПРАВО + НАЗАД
    
//     else{runStop();}
// }

void loop() { 
  RemoteXY_Handler ();
    if(RemoteXY.button_1 == 1){runForward();} // ВПЕРЕД
    else if(RemoteXY.button_2 == 1){runBack();} // НАЗАД
    else if(RemoteXY.button_3 == 1){left();} // ЛЕВО 
    else if(RemoteXY.button_4 == 1){Right();} // ПРАВО

    else if((RemoteXY.button_1 == 1) && (RemoteXY.button_3 == 1)){leftForward();} // ЛЕВО + ВПЕРЕД
    else if((RemoteXY.button_2 ==1) && (RemoteXY.button_3 ==1)){leftBack();} // ЛЕВО + НАЗАД 
    
    else if((RemoteXY.button_1 == 1) && (RemoteXY.button_4 == 1)){RightForward();} // ПРАВО + ВПЕРЕД
    else if((RemoteXY.button_2 == 1) && (RemoteXY.button_4 == 1)){RightBack();} // ПРАВО + НАЗАД
    
    else{runStop();}
  // if(RemoteXY.button_1 == 1){runForward();}
  // else if(RemoteXY.button_2 == 1){runBack();}
  // else{runStop();}
}