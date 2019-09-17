#define PIN_RELAY 2 // Определяем пин, используемый для подключения реле

// В этой функции определяем первоначальные установки
void setup()
{
  pinMode(PIN_RELAY, OUTPUT); // Объявляем пин реле как выход
  digitalWrite(PIN_RELAY, HIGH); // Выключаем реле - посылаем высокий сигнал
}
void loop()
{
  digitalWrite(PIN_RELAY, LOW); // Включаем реле - посылаем низкий уровень сигнала
  delay(5000);
  digitalWrite(PIN_RELAY, HIGH); // Отключаем реле - посылаем высокий уровень сигнала
  delay(5000);
}
