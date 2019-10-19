// #include <Arduino.h>
#include <Servo.h>    // серво библиотека 
#include <NewPing.h>  // дальномер библиотека 

Servo servo;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PINOUT:
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEBUG_RIDER 0

#define PWM_PIN 8       // пин мотора который отвечает за скорость 
#define MOTORIN1_PIN 7      // пин мотора
#define MOTORIN2_PIN 6      // пин мотора1    
#define DIGITAL_SENS_PIN 40   // пин первого цифрового сенсора
#define ANALOG_SENS_PIN 54      // пин первого аналогово сенсора
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PING_PIN  10  // Пин с Arduino подключен к пинам trigger и echo на ультразвуковом датчике расстояния
#define MAX_DISTANCE 40 // Максимальное расстояние, которое мы контролируем (в сантиметрах). Максимальное расстояние подобных датчиков находится в диапазоне 400-500см.
NewPing sonar(PING_PIN, PING_PIN, MAX_DISTANCE); // Настройка пинов и максимального расстояния
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SERVO_PIN 12
#define ZERO_POS 90       //среднее положение сервы
#define MAX_SERVO_ANGLE 34    //максимальный yгол поворот(по умолчанию 40)

#define MIN_MOTOR_SPEED 165   // минимальная скорость 
#define MAX_MOTOR_SPEED 165   // максимальная скорость 

#define TOTAL_SENSORS 11        // всего сенсоров

#define SER_DEBUG_ENABLE 1 

int16_t sensor[TOTAL_SENSORS]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // масив сенсоров 
int16_t filtered_sensors[TOTAL_SENSORS]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // масив сенсоров с фильтром 
int16_t line_vector_val = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int16_t white_color_val = 70;  // значение черного цвета
int16_t black_color_val = 1000;  // значение белого цвета
int16_t sensor_a[TOTAL_SENSORS]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // массив с аналоговыми значениями
int16_t sensor_correction[TOTAL_SENSORS]={-3, -2, -56, -1, -2, -2, 0, -2, -2, -43, -1};  // массив со значениями коррекции датчиков, для выравнивания их значений между собой
//56,44,79,45,45,43,39,39,39,63,36,
int16_t light_correction = 0;   // поправка на освещенность

int16_t left_sens_val = 0;      // переменная для накопления значения левой ошибки
int16_t center_sens_val = 0;    // переменная для накопления значения ширины линии
int16_t right_sens_val = 0;     // переменная для накопления значения правой ошибки
int8_t convers_oper_flag = 0;   // флаг операции преобразования

int8_t lr_sum = 0; // сума l и r 

int16_t lineCheck(int _sens_type = 0){
  left_sens_val = 0;
  center_sens_val = 0;
  right_sens_val = 0;
  convers_oper_flag = 0;
  white_color_val = 1023;  // значение черного цвета
  black_color_val = 0;     // значение белого цвета
  for(int i=0; i<TOTAL_SENSORS; i++){
      // sensor_a[i] = analogRead(ANALOG_SENS_PIN + i);
      sensor_a[i] = analogRead(ANALOG_SENS_PIN + i) + sensor_correction[i];
      if(sensor_a[i] < white_color_val){white_color_val = sensor_a[i];}  // определяем белый
      if(sensor_a[i] > black_color_val){black_color_val = sensor_a[i];}  // определяем черный
      // Serial.print(String(sensor_a[i]) + ",");
  }
  // Serial.print("   ");
  // Serial.print("b ");
  // Serial.print(black_color_val);  
  // Serial.print("  ");
  // Serial.print("w ");
  // Serial.print(white_color_val);
  // Serial.print("   coef [");
  // Serial.print(float(black_color_val) / float(white_color_val));
  // Serial.print("]  ");


  for(int i=0; i<TOTAL_SENSORS; i++){  //
      if((sensor_a[i] >= (black_color_val - ((black_color_val - white_color_val) / 4))) && (sensor_a[i] >= (white_color_val * 2))){
        sensor[i] = 1;
      }
      else{
        sensor[i] = 0;
      }

      // if(sensor_a[i] >= (white_color_val * 3)){
      //  sensor[i] = 1;
      // }
      // else{
      //  sensor[i] = 0;
      // }

      // Serial.print(String(sensor[i]));
  }
  
  line_vector_val = errorAnalizer();

  // Serial.print("Error   ");
  // Serial.print(line_vector_val);
  // if(line_vector_val > 0 && line_vector_val <= 11){Serial.println(" >");}
  // else if(line_vector_val < 0 && line_vector_val >= -11 ){Serial.println(" <");}
  // else if(line_vector_val == 0){Serial.println(" | ");}
  return line_vector_val;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int16_t watch_track_val = 0; 

int16_t left_black = 0;
int16_t right_black = 0;
int16_t left_white = 0;
int16_t right_white = 0;

int32_t errorAnalizer(){
  left_black = 0;
  right_black = 0;
  left_white = 0;
  right_white = 0;
  
  int32_t _line_vector_val_SS = 0;
  sensorFiltrator();
  for(int i=0; i<TOTAL_SENSORS; i++){
    if((filtered_sensors[i] == 0) && (left_black == 0)){left_white ++;}
    else if(filtered_sensors[i] != 0){left_black ++;}
    if((filtered_sensors[(TOTAL_SENSORS - 1) - i] == 0) && (right_black == 0)){right_white ++;}
    else if(filtered_sensors[(TOTAL_SENSORS - 1) - i] != 0){right_black ++;}
  } 

  _line_vector_val_SS = left_white - right_white;
  watch_track_val = left_white + right_white;
  // Serial.println(" "); 
  // Serial.print("watch_track_val   ");
  // Serial.println(watch_track_val);
  // Serial.print("   ");
  // Serial.print(_line_vector_val_SS);
  // Serial.print("   ");

  // Serial.print("l,r,lb,rb = ");
  // Serial.print("   l ");
  // Serial.print(left_white);
  // Serial.print("   r ");
  // Serial.print(right_white);
  // Serial.print("   lb ");
  // Serial.print(left_black);
  // Serial.print("   rb ");
  // Serial.print(right_black);
  // Serial.print("   lr sum ");
  lr_sum = left_white + right_white;
  // Serial.println(lr_sum);

  return _line_vector_val_SS;
}

int16_t shturman(){
  int16_t traffic_light_value = 0;
  
  if(Serial1.available()){
    traffic_light_value = Serial1.read();
  }
  
  return(traffic_light_value);
}

void roadTraffic(){
  if(traffic_light_value == 0){ // красный 
    digitalWrite(MOTORIN1_PIN, LOW);
    digitalWrite(MOTORIN2_PIN, LOW);
    analogWrite(PWM_PIN, LOW);
    // servo.write(ZERO_POS);
  }
  else if(traffic_light_value == 1){
    digitalWrite(MOTORIN1_PIN, LOW);
    digitalWrite(MOTORIN2_PIN, LOW);
    analogWrite(PWM_PIN, LOW);
    // servo.write(ZERO_POS);
  }
  else if(traffic_light_value == 2){
    generalDriver();
  }
  else if(traffic_light_value == 3){
    generalDriver();
  }
  else if(traffic_light_value == 4){
    digitalWrite(MOTORIN1_PIN, LOW);
    digitalWrite(MOTORIN2_PIN, LOW);
    analogWrite(PWM_PIN, LOW);
    // servo.write(ZERO_POS); 
  }
  else if(traffic_light_value == 5){
    digitalWrite(MOTORIN1_PIN, LOW);
    digitalWrite(MOTORIN2_PIN, LOW);
    analogWrite(PWM_PIN, LOW);
    delay(500);
    // servo.write(ZERO_POS); 
  }
  else if(traffic_light_value == 6){
    digitalWrite(MOTORIN1_PIN, LOW);
    digitalWrite(MOTORIN2_PIN, LOW);
    analogWrite(PWM_PIN, LOW);
    delay(500);
    // servo.write(ZERO_POS); 
  }
}

inline void sensorFiltrator(){
  // Serial.print(" F ");
  for(int i=0; i<TOTAL_SENSORS; i++){
    filtered_sensors[i] = sensor[i];
    // Serial.print(filtered_sensors[i]);
  }
  // Serial.println("   ");
}

uint8_t distanceF(){
  delay(30); // Задержка в 30 миллисекунд между генерацией волн. 29 миллисекунд – минимально допустимая задержка.
  unsigned int _echo_time = sonar.ping(); // Генерация сигнала, получение времени в микросекундах (_echo_time).
  int _dist = _echo_time / US_ROUNDTRIP_CM;

  // Serial.print("Distance: ");
  // Serial.print(_dist); // Преобразование времени в расстояние и отображение результата (0 соответствует выходу за допустимый диапазон)
  // Serial.println("cm");
  return _dist;
}


int16_t latch_vozvrata = 0; 
inline void vozvratNaTrasy(){

}

inline void voditelWithoutPID(){

  int16_t _line_veexp = line_vector_val;
  int16_t _line_veexp_2 = line_vector_val;

  // if(_line_veexp < -11){_line_veexp = -11;}
  // else if(_line_veexp > 11){_line_veexp = 11;}

  int16_t _required_servo_pos = map(_line_veexp, 11, -11, ZERO_POS + MAX_SERVO_ANGLE, ZERO_POS - MAX_SERVO_ANGLE);
  if(watch_track_val !=22 && lr_sum >= 7){servo.write(_required_servo_pos);}


  int16_t _required_motor_speed;
  if(line_vector_val >= 0){_required_motor_speed = map(_line_veexp_2, 5, 11, MAX_MOTOR_SPEED, MIN_MOTOR_SPEED);}
  else{_required_motor_speed = map(_line_veexp_2, -5, -11, MAX_MOTOR_SPEED, MIN_MOTOR_SPEED);}
  if(_line_veexp_2 > -5 && _line_veexp_2 < 5){_required_motor_speed = MAX_MOTOR_SPEED;}

  _required_motor_speed = MAX_MOTOR_SPEED;

  digitalWrite(MOTORIN1_PIN, HIGH);
  digitalWrite(MOTORIN2_PIN, LOW);
  if(watch_track_val != 22){
    if(_required_motor_speed == 255){digitalWrite(PWM_PIN, HIGH);}
    else{analogWrite(PWM_PIN, _required_motor_speed);}    
  }
  else{
    uint8_t _dist = distanceF();
    if(_dist >= 0){ // Если видим препятствие - стоим 
      digitalWrite(PWM_PIN, LOW);
      // servo.write(ZERO_POS);
    }
    else{  // возврат на трассу 
      vozvratNaTrasy();
    }
  }

  // Serial.print("   ");
  // Serial.print(_required_servo_pos);
  // Serial.print("   ");
  // Serial.println(_required_motor_speed);
}

inline void generalDriver(){
  lineCheck();
  if(line_vector_val > 0 && line_vector_val <= 11){latch_vozvrata = 1;}
  else if(line_vector_val < 0 && line_vector_val <= -11 ){latch_vozvrata = -1;}
  voditelWithoutPID();
}
void setup(){
  pinMode(PWM_PIN, OUTPUT);
  pinMode(MOTORIN1_PIN, OUTPUT);
  pinMode(MOTORIN2_PIN, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(115200);

  servo.attach(SERVO_PIN);
  delay(50);
  servo.write(ZERO_POS);
}

void loop(){
// uint32_t rttyu = millis();;

// roadTraffic();
roadTraffic();
// delay(500);
// Serial.print("time   ");
// Serial.println(millis() - rttyu);
}


// PID
  /*//////////////////////////////////////////////////////////////////////////////////////////////////

  int32_t avgSpeed = 150; // средняя скорость моторов
  int32_t kP = 10; // коэффициент пропорциональной обратной связи
  int32_t kD = 5;  // коэффициент дифференциальной обратной связи
  int32_t kI = 5;  // коэффициент интегральной обратной связи

  int32_t correction;
  int32_t err;

  int32_t err_arr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int32_t err_p = -1;

  prevErr = bot_position();

  int32_t pidRegulator()
  {
  err = bot_position();
  err_p = (err_p + 1) % 10;
  err_arr[err_p] = err;

  P = err * KP;
  D = (err_arr[err_p] - err_arr[(err_p+11) % 10])*KD;
  int err_sum = 0;
  for (int i = 0; i < 10; i++) err_sum += err_arr[i];
  I = err_sum/10*KI;

  correction = P + I + D;
  return correction;

  // motor1.move(avgSpeed*(1+correction));
  // motor2.move(avgSpeed*(1-correction));

  delay(2);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////*/
 