#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/* ================= LCD ================= */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ================= PIN MAP ================= */
#define IN1        D7
#define IN2        D8
#define RELAY_PIN  D6      // ACTIVE HIGH
#define VIB_PIN    D5
#define BTN_PIN    D3
#define LED_OK     D0
#define LED_FAULT  D4
// #define BUZZER     D9  // Removed

/* ================= TIMING ================= */
const unsigned long RESET_TIME = 5000; // 5 sec recovery

/* ================= STATES ================= */
bool motorOn = false;
bool faultActive = false;

unsigned long faultStartTime = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(VIB_PIN, INPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_OK, OUTPUT);
  pinMode(LED_FAULT, OUTPUT);

  // SAFE START
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_OK, LOW);
  digitalWrite(LED_FAULT, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Motor System");
  lcd.setCursor(0, 1);
  lcd.print("Ready");
  delay(2000);
  lcd.clear();

  // ===== SERIAL FOR MATLAB =====
  Serial.begin(9600);
}

void loop() {

  /* -------- BUTTON TOGGLE -------- */
  if (digitalRead(BTN_PIN) == LOW && !faultActive) {
    delay(250);
    motorOn = !motorOn;
  }

  /* -------- VIBRATION DETECT -------- */
  if (motorOn && digitalRead(VIB_PIN) == HIGH && !faultActive) {
    faultActive = true;
    faultStartTime = millis();
  }

  /* -------- FAULT HANDLING -------- */
  if (faultActive) {
    faultMode();

    unsigned long elapsed = millis() - faultStartTime;

    // Recover after 5 seconds
    if (elapsed >= RESET_TIME) {
      faultActive = false;
    }

    // ===== SERIAL OUTPUT FOR MATLAB =====
    Serial.println(digitalRead(VIB_PIN));
    return;
  }

  /* -------- NORMAL OPERATION -------- */
  if (motorOn) {
    normalMode();
  } else {
    motorStop();
  }

  // ===== SERIAL OUTPUT FOR MATLAB =====
  Serial.println(digitalRead(VIB_PIN));
}

/* ================= FUNCTIONS ================= */

void normalMode() {
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(LED_OK, HIGH);
  digitalWrite(LED_FAULT, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Motor: RUNNING ");
  lcd.setCursor(0, 1);
  lcd.print("Status: OK     ");
}

void faultMode() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_OK, LOW);
  digitalWrite(LED_FAULT, HIGH);

  lcd.setCursor(0, 0);
  lcd.print("!!! VIBRATION !!!");
  lcd.setCursor(0, 1);
  lcd.print("Recovery Wait  ");
}

void motorStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_OK, LOW);
  digitalWrite(LED_FAULT, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Motor: OFF     ");
