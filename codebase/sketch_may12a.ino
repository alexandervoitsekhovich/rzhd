#include <SPI.h>

enum { REG_LATCH = 8 };


void setup()
{
  /* Включаем UART и SPI */
  Serial.begin(9600);
  SPI.begin();
  /* Включаем защёлку */
  pinMode(REG_LATCH, OUTPUT);
  digitalWrite(REG_LATCH, HIGH);
}


void loop()
{
  static uint8_t last_input_states = 0;
  int cnt = 0;

  /* Выставим на защёлке сначала низкий, потом - высокий уровни.
   * Сдвиговый регистр запомнит уровни сигналов на входах и сможет
   * их нам потом отдать бит за битом.
   */
  digitalWrite(REG_LATCH, LOW);
  digitalWrite(REG_LATCH, HIGH);
  /* Читаем запомненные состояния входов. Ноль шлём просто потому,
   * что transfer() одновременно и шлёт, и принимает. Да и вообще,
   * MOSI не подключена (:
   */
  uint8_t states = SPI.transfer(0);

  /* Если состояние любого входа изменилось, расскажем по UART */
  if (states != last_input_states)
  {
    /* Старый добрый XOR даст нам битовую разницу между старым и новым состояниями. */
    uint8_t changed = states ^ last_input_states;
    last_input_states = states; // запоминаем текущие состояния

    for (int i = 0; i < 8; ++i)
    {
      if (changed & 1) // если состояние кнопки изменилось…
      {
        cnt++;
        Serial.print("#");
        Serial.print(i); // шлём номер кнопки
        Serial.print(" -> ");
        Serial.println(states & 1); // … и новое состояние
        Serial.println(cnt);
      }

      /* Сдвигаем биты вправо. Теперь первый бит
       * будет указывать состояние следующей кнопки.
       */
      changed >>= 1;
      states >>= 1;
    }
  }
}