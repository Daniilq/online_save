#include <NewPing.h>

#define PING_PIN  12  // Пин с Arduino подключен к пинам trigger и echo на ультразвуковом датчике расстояния

#define MAX_DISTANCE 50 // Максимальное расстояние, которое мы контролируем (в сантиметрах). Максимальное расстояние подобных датчиков находится в диапазоне 400-500см.

NewPing sonar(PING_PIN, PING_PIN, MAX_DISTANCE); // Настройка пинов и максимального расстояния

void setup() {

Serial.begin(115200); // Открытие серийного протокола с частотой передачи данных 115200 бит/сек.

}

void loop() {
int32_t rttyu = micros();

  // delay(50); // Задержка в 50 миллисекунд между генерацией волн. 29 миллисекунд – минимально допустимая задержка.

  unsigned int uS = sonar.ping(); // Генерация сигнала, получение времени в микросекундах (uS).

  Serial.print("Ping: ");

  Serial.print(uS / US_ROUNDTRIP_CM); // Преобразование времени в расстояние и отображение результата (0 соответствует выходу за допустимый диапазон)

Serial.println("cm");

Serial.println(micros() - rttyu);
} 

