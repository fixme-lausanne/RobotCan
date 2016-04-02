// Robot Can
// Author: Aymeric Bringard <nemen@fixme.ch>
// Data: 27.03.2016


#define SWITCH_LEFT_PIN 4
#define SWITCH_RIGHT_PIN 5

#define BUZZER_PIN 10

#define LED_LEFT_PIN 11
#define LED_RIGHT_PIN 12


bool switchLeftStatus, switchRightStatus;
unsigned long normalPrevMs = 0,
              winkyEyePrevMs = 0,
              angryPrevMs = 0;
int normalInterval = 10000,
    winkyEyeInterval = 6000,
    angryInterval = 5000;


bool getSwitchLeftStatus() {
  return digitalRead(SWITCH_LEFT_PIN);
}
bool getSwitchRightStatus() {
  return digitalRead(SWITCH_RIGHT_PIN);
}

void normalBehaviour(unsigned long currentMillis) {

  digitalWrite(LED_LEFT_PIN, HIGH);
  digitalWrite(LED_RIGHT_PIN, HIGH);

  if(currentMillis - normalPrevMs > normalInterval) {
    normalPrevMs = currentMillis;

    digitalWrite(LED_LEFT_PIN, LOW);
    digitalWrite(LED_RIGHT_PIN, LOW);
    tone(BUZZER_PIN, 500, 10);
    delay(50);
    digitalWrite(LED_LEFT_PIN, HIGH);
    digitalWrite(LED_RIGHT_PIN, HIGH);
    delay(200);
    digitalWrite(LED_LEFT_PIN, LOW);
    digitalWrite(LED_RIGHT_PIN, LOW);
    tone(BUZZER_PIN, 500, 10);
    delay(50);
    digitalWrite(LED_LEFT_PIN, HIGH);
    digitalWrite(LED_RIGHT_PIN, HIGH);
  }
}
void winkEyeBehaviour(unsigned long currentMillis, bool left) {
  digitalWrite(LED_LEFT_PIN, HIGH);
  digitalWrite(LED_RIGHT_PIN, HIGH);

  if(currentMillis - winkyEyePrevMs > winkyEyeInterval) {
    winkyEyePrevMs = currentMillis;

    int pin = (left ? LED_RIGHT_PIN : LED_LEFT_PIN);

    digitalWrite(pin, LOW);
    delay(1000);
    digitalWrite(pin, HIGH);
  }
}
void angryBehaviour(unsigned long currentMillis) {

  if(currentMillis - angryPrevMs > angryInterval) {
    angryPrevMs = currentMillis;

    for(int i = 0; i < 10; ++i) {
      digitalWrite(LED_LEFT_PIN, HIGH);
      digitalWrite(LED_RIGHT_PIN, HIGH);
      tone(BUZZER_PIN, 265, 20);
      delay(50);
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(LED_RIGHT_PIN, LOW);
      tone(BUZZER_PIN, 405, 20);
      delay(50);
    }
  }

}

void setup() {
  Serial.begin(9600);

  pinMode(SWITCH_LEFT_PIN, INPUT);
  pinMode(SWITCH_LEFT_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
}

void loop() {

  unsigned long currentMillis = millis();

  switchLeftStatus = getSwitchLeftStatus();
  switchRightStatus = getSwitchRightStatus();

  Serial.print("L: ");
  Serial.print(switchLeftStatus);
  Serial.print(" - R: ");
  Serial.println(switchRightStatus);

  if (switchLeftStatus == HIGH && switchRightStatus == HIGH) {
    // Serial.println("ANGRY!!!");
    angryBehaviour(currentMillis);
  } else {
    // Serial.println("normal");
    normalBehaviour(currentMillis);
  }
}
