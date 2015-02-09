#define PIN_COUNT  6

typedef struct {
  byte pin;
  int code;
  boolean pressed;
}
InputPin;

InputPin inputPins[PIN_COUNT];
int pins[] = {A0, A1, A2, A3, A4, A5};
int keyCodes[] = {KEY_LEFT_ARROW, KEY_RIGHT_ARROW, KEY_UP_ARROW, KEY_DOWN_ARROW, 32, KEY_RETURN};

void setup() {
  //Serial.begin(9600);
  for (int i = 0; i < PIN_COUNT; i++) {
    inputPins[i].pin = pins[i];
    inputPins[i].code = keyCodes[i];
    pinMode(inputPins[i].pin, INPUT);
    digitalWrite(inputPins[i].pin, LOW);
  }
  Keyboard.begin();
}

void loop() {
  for (int i = 0; i < PIN_COUNT; i++) {
      boolean pressed = !digitalRead(inputPins[i].pin);
      if (pressed && !inputPins[i].pressed) {
        Keyboard.press(inputPins[i].code);
      } else if (!pressed && inputPins[i].pressed){
        Keyboard.release(inputPins[i].code);
      }
      inputPins[i].pressed = pressed;
  }
  delay(1);
}
