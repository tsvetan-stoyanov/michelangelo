#define GREEN_LED_PIN 3
#define RED_LED_PIN 4
#define MAINTENANCE_BTN_PIN 2
#define PHOTO_PIN A0
#define MIN_PHOTO_RESISTANCE 50
#define MAINTENANCE_BLINK_INTERVAL 500;

boolean maintenance;
long redLedOnEnd;
boolean redLedOn;

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(MAINTENANCE_BTN_PIN, INPUT);
}

void loop() {
  checkMaintenance();
  if (!maintenance) {
    processLight();
  }
  delay(200);
}

void checkMaintenance() {
  boolean btnPressed = digitalRead(MAINTENANCE_BTN_PIN);
  if (!btnPressed && !maintenance) {
    return;
  }
  
  if (btnPressed) {
    maintenance = !maintenance;
    redLedOn = maintenance;
    if (maintenance) {
      digitalWrite(GREEN_LED_PIN, LOW);
    }
  }
  switchMaintenanceLight();
}

void switchMaintenanceLight() {
  if (maintenance) {
    long time = millis();
    if (time > redLedOnEnd) {
      redLedOnEnd = time + MAINTENANCE_BLINK_INTERVAL;
      redLedOn = !redLedOn;
      digitalWrite(RED_LED_PIN, redLedOn);
    }
  }
}

void processLight() {
  boolean placeOccupied = analogRead(PHOTO_PIN) <= MIN_PHOTO_RESISTANCE;
  digitalWrite(RED_LED_PIN, placeOccupied);
  digitalWrite(GREEN_LED_PIN, !placeOccupied);
}
