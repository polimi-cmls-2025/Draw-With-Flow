#include <math.h>
#include <stdio.h>

#define A_X A5
#define A_Y A4
#define A_Z A3

const int pulsePin = 13;
const int validMinBPM = 60;
const int validMaxBPM = 130;

int val_x, val_y, val_z;
int prev_val_x = 0, prev_val_y = 0, prev_val_z = 0;
unsigned long prev_time = 0;

volatile int beatCount = 0;
unsigned long beatTimes[4];
int latestBPM = -1;
int lastValidBPM = -1;

void setup() {
  pinMode(A_X, INPUT);
  pinMode(A_Y, INPUT);
  pinMode(A_Z, INPUT);
  pinMode(pulsePin, INPUT);
  Serial.begin(9600);
}

void loop() {
  static bool lastState = LOW;
  static unsigned long lastDebounceTime = 0;
  static const unsigned long debounceDelay = 10;

  bool currentState = digitalRead(pulsePin);
  if (currentState == HIGH && lastState == LOW && (millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    handleBeat();
  }
  lastState = currentState;

  val_x = val_y = val_z = 0;
  for (int i = 0; i < 10; i++) {
    val_x += analogRead(A_X);
    val_y += analogRead(A_Y);
    val_z += analogRead(A_Z);
    delay(2);
  }
  val_x /= 10;
  val_y /= 10;
  val_z /= 10;

  unsigned long current_time = millis();
  unsigned long delta_time = current_time - prev_time;

  int delta_x = val_x - prev_val_x;
  int delta_y = val_y - prev_val_y;
  int delta_z = val_z - prev_val_z;

  float speed_x = 0, speed_y = 0, speed_z = 0;
  if (delta_time > 0) {
    speed_x = abs(delta_x) / (float)delta_time;
    speed_y = abs(delta_y) / (float)delta_time;
    speed_z = abs(delta_z) / (float)delta_time;
  }

  float norm_x = constrain(speed_x / 4.0, 0.0, 1.0);
  float norm_y = constrain(speed_y / 4.0, 0.0, 1.0);
  float norm_z = constrain(speed_z / 4.0, 0.0, 1.0);

  float speed_avg_norm = (norm_x + norm_y + norm_z) / 3.0;

  prev_val_x = val_x;
  prev_val_y = val_y;
  prev_val_z = val_z;
  prev_time = current_time;

  static unsigned long lastSendTime = 0;
  if (millis() - lastSendTime > 100) {
    lastSendTime = millis();
    int bpmToSend = (latestBPM != -1) ? latestBPM : lastValidBPM;
    Serial.print("BPM:");
    Serial.println(bpmToSend);
  }

  static unsigned long lastSpeedSendTime = 0;
  if (millis() - lastSpeedSendTime > 2500) {
    lastSpeedSendTime = millis();
    Serial.print("SPEED_X_NORM:");
    Serial.println(norm_x, 4);
    Serial.print("SPEED_Y_NORM:");
    Serial.println(norm_y, 4);
    Serial.print("SPEED_Z_NORM:");
    Serial.println(norm_z, 4);
    Serial.print("SPEED_AVG_NORM:");
    Serial.println(speed_avg_norm, 4);
  }

  delay(50);
}

void handleBeat() {
  unsigned long currentTime = millis();
  beatTimes[beatCount % 4] = currentTime;
  beatCount++;

  if (beatCount >= 4) {
    unsigned long delta = beatTimes[(beatCount - 1) % 4] - beatTimes[(beatCount - 4) % 4];
    if (delta > 0) {
      float bpm = 60000.0 * 3 / delta;
      if (bpm >= validMinBPM && bpm <= validMaxBPM) {
        latestBPM = (int)bpm;
        lastValidBPM = latestBPM;
      } else {
        latestBPM = -1;
      }
    }
  }
}




