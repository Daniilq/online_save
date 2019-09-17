/* 
   -- Дом вайфай -- 
    
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
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_CLOUD

#include <RemoteXY.h> 

// настройки соединения  
#define REMOTEXY_SERIAL Serial 
#define REMOTEXY_SERIAL_SPEED 115200 
#define REMOTEXY_WIFI_SSID "TP-LINK_0D6E" 
#define REMOTEXY_WIFI_PASSWORD "1978oksana" 
#define REMOTEXY_CLOUD_SERVER "cloud.remotexy.com" 
#define REMOTEXY_CLOUD_PORT 6376 
#define REMOTEXY_CLOUD_TOKEN "eb191d13e4c3004fec14b70b1a73d55c" 


// конфигурация интерфейса   
#pragma pack(push, 1) 
uint8_t RemoteXY_CONF[] = 
  { 255,1,0,0,0,66,0,8,13,1,
  2,1,5,10,53,16,2,26,31,31,
  79,78,0,79,70,70,0,130,1,-2,
  27,68,3,17,129,0,4,3,56,6,
  24,208,157,208,176,209,129,209,130,208,
  190,208,187,209,140,208,189,208,176,209,
  143,32,208,187,208,176,208,188,208,191,
  208,176,0 }; 
   
// структура определяет все переменные вашего интерфейса управления  
struct { 

    // input variable
  uint8_t Rele; // =1 если переключатель включен и =0 если отключен 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY; 
#pragma pack(pop) 

///////////////////////////////////////////// 
//           END RemoteXY include          // 
///////////////////////////////////////////// 

#define PIN_RELE 9


void setup()  
{ 
  RemoteXY_Init ();  
   
  pinMode (PIN_RELE, OUTPUT);
   
  // TODO you setup code 
   
} 

void loop()  
{  
  RemoteXY_Handler (); 
   
  digitalWrite(PIN_RELE, (RemoteXY.Rele==0)?LOW:HIGH);
   
  // TODO you loop code 
  // используйте структуру RemoteXY для передачи данных 


}
