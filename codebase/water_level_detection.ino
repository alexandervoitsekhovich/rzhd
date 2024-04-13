constexpr auto LIQUID_SENSOR_PIN = 11; //задаем пин для подключения датчика 




void setup() {
  pinMode(LIQUID_SENSOR_PIN, INPUT); // настраиваем пин датчика на получение информации
  Serial.begin(9600); 

}

void loop() {
  int liquid_level = digitalRead(LIQUID_SENSOR_PIN); // считываем значение с датчика и записываем его в переменную
  Serial.println(liquid_level) //в будущем тут будет отправление значения на сервер, сейчас выведем в COM-порт значение для наглядности
  delay(15000); // период замеров - 15 секунд
}
