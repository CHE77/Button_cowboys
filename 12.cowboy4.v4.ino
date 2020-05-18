#define BUZZER_PIN   6  // пин с пищалкой, другой контакт пищалки - к земле
#define PLAYER_COUNT 4   // количество игроков-ковбоев
// вместо перечисления всех пинов по-одному, мы объявляем пару
// списков: один с номерами пинов с кнопками, другой — со
// светодиодами. Списки также называют массивами (англ. array)
int buttonPins[PLAYER_COUNT] = {3, 8, 9, 12};// кнопки к этим пинам. другой контакт кнопки на землю
int ledPins[PLAYER_COUNT] = {5, 7, 10, 11}// светодиоды к этим пинам. другой контакт светодиода через резистор к земле
int winCount[PLAYER_COUNT] = {0, 0, 0 , 0}; // масс
int signalLed = 13; // Signal LED of game start, другой контакт светодиода через резистор к земле
int randomTimer = 0;
int gameStatus = 0;// standby
uint32_t lastRoundMillis = 0 ;


void setup()
{
  Serial.begin(9800);
  pinMode(BUZZER_PIN, OUTPUT);
  for (int player = 0; player < PLAYER_COUNT ; ++player) {
    // при помощи квадратных скобок получают значение в массиве
    // под указанным в них номером. Нумерация начинается с нуля
    pinMode(ledPins[player], OUTPUT);
    pinMode(buttonPins[player], INPUT_PULLUP);
  }
 
  int randomTimer = random(3000, 6000);
  uint32_t lastRoundMillis = millis() ;

  Serial.print("setup done");
}



void loop()
{
  // даём сигнал «пли!», выждав случайное время от 2 до 7 сек
  // delay(random(2000, 5000));
  // noTone(BUZZER_PIN) ;


  for (int player = 0; ; player = (player + 1) % PLAYER_COUNT) {


    // если игрок номер «player» нажал кнопку...
    if (!digitalRead(buttonPins[player])) {
      // ...включаем его светодиод и сигнал в зависимости от того правильно ли он нажал или нет

      switch (gameStatus) {

        case 0:// фальстарт
          Serial.print("Игрок номер ");
          Serial.print(4 - player);
          Serial.println(" - сделал фальстарт! ");
          winCount[player] = winCount[player] - 1;
          Serial.print("У него - ");
          Serial.print(winCount[player]);
          Serial.println(" побед! ");
          Serial.println("");
          tone(BUZZER_PIN, 1000, 250); // 3 килогерца, 250 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(250);
          tone(BUZZER_PIN, 2000, 250); // 3 килогерца, 250 миллисекунд;
          digitalWrite(ledPins[player], LOW);
          delay(250);
          tone(BUZZER_PIN, 1000, 250); // 3 килогерца, 250 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(250);
          tone(BUZZER_PIN, 2000, 250); // 3 килогерца, 250 миллисекунд;
          digitalWrite(ledPins[player], LOW);
          delay(250);
          tone(BUZZER_PIN, 1000, 250); // 3 килогерца, 250 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(250);

          digitalWrite(signalLed, LOW);
          digitalWrite(ledPins[player], LOW);
          break;

        case 1:// произошло правильное нажатие
          digitalWrite(ledPins[player], HIGH);
          tone(BUZZER_PIN, 4000, 1000);
          Serial.print("Игрок номер ");
          Serial.print(4 - player);
          Serial.println(" - Выиграл! ");
          winCount[player] = winCount[player] + 1;
          Serial.print("У него - ");
          Serial.print(winCount[player]);
          Serial.println(" побед! ");
          Serial.println("");
          if (winCount[player] == 5) {// игрок выйграл турнир, все ему мигают своими светодиодами
            for (int playerLooser = 0; ; playerLooser = (playerLooser + 1) % PLAYER_COUNT) {
              digitalWrite(ledPins[playerLooser], HIGH);
              delay(100);
              digitalWrite(ledPins[playerLooser], LOW);
              digitalWrite(ledPins[player], HIGH);
              delay(100);
            }
          }
          delay(1000);
          digitalWrite(signalLed, LOW);
          digitalWrite(ledPins[player], LOW);
          break;

        case 2:
          Serial.print("Игрок номер ");
          Serial.print(4 - player);
          Serial.println(" - Проиграл! ");
          winCount[player] = winCount[player] - 1;
          Serial.print("У него - ");
          Serial.print(winCount[player]);
          Serial.println(" побед! ");
          Serial.println("");
          tone(BUZZER_PIN, 1000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(250);
          tone(BUZZER_PIN, 2000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], LOW);
          delay(250);
          tone(BUZZER_PIN, 1000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(250);
          tone(BUZZER_PIN, 2000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], LOW);
          delay(250);
          tone(BUZZER_PIN, 1000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(250);
          tone(BUZZER_PIN, 1000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], LOW);
          delay(250);
          tone(BUZZER_PIN, 600, 1000); // 0.6 килогерц, 1000 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(1000);
          digitalWrite(signalLed, LOW);
          digitalWrite(ledPins[player], LOW);
          break;

        case 3:
          Serial.print("Игрок номер ");
          Serial.print(4 - player);
          Serial.println(" - Проиграл! ");
          winCount[player] = winCount[player] - 1;
          Serial.print("У него - ");
          Serial.print(winCount[player]);
          Serial.println(" побед! ");
          Serial.println("");
          tone(BUZZER_PIN, 1000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(250);
          tone(BUZZER_PIN, 2000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], LOW);
          delay(250);
          tone(BUZZER_PIN, 1000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(250);
          tone(BUZZER_PIN, 2000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], LOW);
          delay(250);
          tone(BUZZER_PIN, 1000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(250);
          tone(BUZZER_PIN, 1000, 250); // 1 килогерц, 250 миллисекунд;
          digitalWrite(ledPins[player], LOW);
          delay(250);
          tone(BUZZER_PIN, 600, 1000); // 0.6 килогерц, 1000 миллисекунд;
          digitalWrite(ledPins[player], HIGH);
          delay(1000);
          digitalWrite(signalLed, LOW);
          digitalWrite(ledPins[player], LOW);
          break;
      }
      gameStatus = 0;
                Serial.println("");
                Serial.println("Новый раунд!");
      break; // Есть победитель! Выходим (англ. break) из цикла
    }

  if (millis() - lastRoundMillis > randomTimer) {// end of standby, new round
    gameStatus = random(1, 4);
    switch (gameStatus) {

      case 0:

      case 1:
        tone(BUZZER_PIN, 3000, 250); // 3 килогерца, 250 миллисекунд;
        digitalWrite(signalLed, HIGH);
        break;

      case 2:
        digitalWrite(signalLed, HIGH);
        break;

      case 3:
        tone(BUZZER_PIN, 3000, 250); // 3 килогерца, 250 миллисекунд;
        break;
    }
    lastRoundMillis = millis();
    randomTimer = random(3000, 6000);

  }// end new round
  
  if (millis() - lastRoundMillis > 500) digitalWrite(signalLed, LOW);// гасим сигнальный светодид

  }// end for


}
