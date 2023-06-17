
#define BUTTON_DOWN 16
#define BUTTON_LEFT 17
#define BUTTON_RIGHT 18
#define BUTTON_UP 21
#define BUTTON_BACK 19
#define BUTTON_ENTER 20
#define BUTTON_RESET 15
#define LED 7
void setup() {
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_ENTER, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);
  pinMode(BUTTON_BACK, INPUT_PULLUP);

  pinMode(LED, OUTPUT);
}

void loop() {
  if (!digitalRead(BUTTON_UP) || !digitalRead(BUTTON_DOWN) || !digitalRead(BUTTON_RIGHT) || !digitalRead(BUTTON_LEFT) || !digitalRead(BUTTON_ENTER) || !digitalRead(BUTTON_RESET) || !digitalRead(BUTTON_BACK)) {
    digitalWrite(LED, HIGH);
  }

  else {
    digitalWrite(LED, LOW);
  }
}
