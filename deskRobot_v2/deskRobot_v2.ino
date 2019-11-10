#define LEFT_SENSOR_PIN  2 //левый датчик 
#define RIGHT_SENSOR_PIN 3 // правый датчик 

#define LEFT_MOTOR_A_PIN 4 // IN1
#define LEFT_MOTOR_B_PIN 5 // IN2
#define LEFT_MOTOR_PWM_PIN 6 // ENA

#define RIGHT_MOTOR_A_PIN 8 // IN3
#define RIGHT_MOTOR_B_PIN 9 // IN 4
#define RIGHT_MOTOR_PWM_PIN 10 // ENB

#define MAX_SPEED 100 // максимальная скорость робота 

#define BRAKE_K 8 // Коэффициент, задающий во сколько раз нужно затормозить одно из колёс для поворота

bool left_sensor_state = 0; // значение левого сенсора 
bool right_sensor_state = 0; // значение правого сенсора 

void setup(){
    pinMode(LEFT_SENSOR_PIN, INPUT);
    pinMode(RIGHT_SENSOR_PIN, INPUT);

    pinMode(LEFT_MOTOR_A_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_B_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_PWM_PIN, OUTPUT);

    pinMode(RIGHT_MOTOR_A_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_B_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_PWM_PIN, OUTPUT);

    runForward(); // сразу едем прямо 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////ПЕРЕДВИЖЕНИЕ МАШИНЫ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void runStop(){				// СТОП
    digitalWrite(LEFT_MOTOR_A_PIN, LOW);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, LOW);

    digitalWrite(RIGHT_MOTOR_A_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, LOW); 
}
void runForward(){				// ВПЕРЕД
	digitalWrite(LEFT_MOTOR_A_PIN, LOW);
    digitalWrite(LEFT_MOTOR_B_PIN, HIGH);
    analogWrite(LEFT_MOTOR_PWM_PIN, MAX_SPEED);

    digitalWrite(RIGHT_MOTOR_A_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_B_PIN, HIGH);
    analogWrite(RIGHT_MOTOR_PWM_PIN, MAX_SPEED);    
}
void runLeft(){				// ЛЕВО
	digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, MAX_SPEED / BRAKE_K);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, MAX_SPEED);       	
}
void runRight(){				// ПРАВО
    digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, MAX_SPEED);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, MAX_SPEED / BRAKE_K);   	
}
void runBack(){				// НАЗАД
    digitalWrite(LEFT_MOTOR_A_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_B_PIN, LOW);
    analogWrite(LEFT_MOTOR_PWM_PIN, MAX_SPEED);

    digitalWrite(RIGHT_MOTOR_A_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
    analogWrite(RIGHT_MOTOR_PWM_PIN, MAX_SPEED);
}
void traffic(){
    bool left_sensor_state = 0; // значение левого сенсора 
    bool right_sensor_state = 0; // значение правого сенсора

	left_sensor_state = digitalRead(LEFT_SENSOR_PIN);
    right_sensor_state = digitalRead(RIGHT_SENSOR_PIN);

    if((left_sensor_state == 0) && (right_sensor_state == 1)){ // если правый датчик съехал со стола, едем направо 
    	runStop();
        delay(100);
        runBack();
        delay(350);
    	runRight();
        delay(400);
    	// return;
    }
    else if((left_sensor_state == 1) && (right_sensor_state == 0)){ // если левый датчик съехал со стола едем налево 
        runStop();
        delay(100);
    	runBack();
        delay(350);
    	runLeft();
        delay(400);
    }
    else if((left_sensor_state == 1) && (right_sensor_state == 1)){ // если оба датчика, то едем назад, а потом разворачиваемся 
        runStop();
        delay(100);
    	runBack();
        delay(350);
    	runRight();
        delay(400);
    }    	
    // if((left_sensor_state == 0) && (right_sensor_state == 0))
    else {  // если оба датчика на столе едем прямо 
    	runForward();
    }

}
void loop(){
	traffic();
}


// // Моторы подключаются к клеммам M1+,M1-,M2+,M2-  
// // Motor shield использует четыре контакта 6,5,7,4 для управления моторами

// #define LEFT_MOTOR_A_PIN         4
// #define LEFT_MOTOR_B_PIN         5
// #define LEFT_MOTOR_PWM_PIN       6

// #define RIGHT_MOTOR_A_PIN        8 
// #define RIGHT_MOTOR_B_PIN        9
// #define RIGHT_MOTOR_PWM_PIN     10

// #define LEFT_SENSOR_PIN  2
// #define RIGHT_SENSOR_PIN 3

// // Скорость, с которой мы движемся вперёд (0-255)
// #define SPEED     75

// // Коэффициент, задающий во сколько раз нужно затормозить
// // одно из колёс для поворота
// #define BRAKE_K         8

// #define STATE_FORWARD    0  
// #define STATE_RIGHT      1
// #define STATE_LEFT       2

// int state = STATE_FORWARD;

// void runForward() 
// {
//     state = STATE_FORWARD;

//     // Для регулировки скорости `SPEED` может принимать значения от 0 до 255,
//     // чем болше, тем быстрее. 
//     analogWrite(LEFT_MOTOR_A_PIN, SPEED);
//     analogWrite(RIGHT_MOTOR_A_PIN, SPEED);

//     // Если в LEFT_MOTOR_B_PIN или RIGHT_MOTOR_B_PIN пишем HIGH, мотор будет двигать соответствующее колесо
//     // вперёд, если LOW - назад.
//     digitalWrite(LEFT_MOTOR_B_PIN, HIGH);
//     digitalWrite(RIGHT_MOTOR_B_PIN, HIGH);
// }

// void steerRight() 
// {
//     state = STATE_RIGHT;

//     // Замедляем правое колесо относительно левого, чтобы начать поворот
//     analogWrite(RIGHT_MOTOR_A_PIN, SPEED / BRAKE_K);
//     analogWrite(LEFT_MOTOR_A_PIN, SPEED);

//     digitalWrite(LEFT_MOTOR_B_PIN, LOW);
//     digitalWrite(LEFT_MOTOR_PWM_PIN     , HIGH);
//     digitalWrite(RIGHT_MOTOR_PWM_PIN, HIGH);
//     digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
//     delay(600);
// }

// void steerLeft() 
// {
//     state = STATE_LEFT;

//     analogWrite(LEFT_MOTOR_A_PIN, SPEED / BRAKE_K);
//     analogWrite(RIGHT_MOTOR_A_PIN, SPEED);

//     digitalWrite(LEFT_MOTOR_B_PIN, LOW);
//     digitalWrite(LEFT_MOTOR_PWM_PIN     , HIGH);
//     digitalWrite(RIGHT_MOTOR_PWM_PIN, HIGH);
//     digitalWrite(RIGHT_MOTOR_B_PIN, LOW);
//     delay(600);
// }



// void setup() 
// {
//     // Настраивает выводы платы 4,5,6,7 на вывод сигналов 
//     for(int i = 4; i <= 7; i++)
//         pinMode(i, OUTPUT);

//     // Сразу едем вперёд
//     runForward();
// } 

// void loop() 
// { 
//   // Наш робот ездит по белому полю с чёрным треком. В обратном случае не нужно
//     // инвертировать значения с датчиков
//     boolean left = digitalRead(LEFT_SENSOR_PIN);
//     boolean right = digitalRead(RIGHT_SENSOR_PIN);

//     // В какое состояние нужно перейти?
//     int targetState;

//     if (left && right) {
//         // под сенсорами всё белое или всё чёрное
//         // едем вперёд
//         targetState = STATE_FORWARD;
//     }
    
//     else if (left) {
//         // левый сенсор упёрся в трек
//         // поворачиваем налево
//         targetState = STATE_RIGHT;
// }
//     else {
//         targetState = STATE_LEFT;
//     }

//     if (state == targetState) {
//         // мы уже делаём всё что нужно,
//         // делаем измерения заново
//         return;
//     }
    
// switch (targetState) {
//         case STATE_FORWARD:
//             runForward();
//             break;

//         case STATE_RIGHT:
//             steerRight();
//             break;
       
//         case STATE_LEFT:
//             steerLeft();
//             break;
//     }  
// }
