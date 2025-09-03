/*
  Robo ESP32 + Maker Line — 5x DIGITAL outputs version (PD only)
  - Simpler & fast: uses Kp and Kd, BASE speed.
*/

#include "CytronMotorDriver.h"

CytronMD motorL(PWM_PWM, 12, 13);
CytronMD motorR(PWM_PWM, 14, 27);

const int S0 = 36, S1 = 39, S2 = 34, S3 = 35, S4 = 32;
int pins[5] = { S0, S1, S2, S3, S4 };
int weights[5] = { -2000, -1000, 0, 1000, 2000 };
bool INVERT = true;

int BASE = 180;
float Kp = 0.18, Kd = 1.0;

int lastPos = 0;
unsigned long lastT = 0;
float lastErr = 0;

void drive(int L, int R) {
  L = L < -255 ? -255 : (L > 255 ? 255 : L);
  R = R < -255 ? -255 : (R > 255 ? 255 : R);
  motorL.setSpeed(L);
  motorR.setSpeed(R);
}
int readBit(int i) {
  int v = digitalRead(pins[i]);
  if (INVERT) v = !v;
  return v ? 1 : 0;
}
int linePosition() {
  long num = 0, den = 0;
  for (int i = 0; i < 5; i++) {
    int s = readBit(i);
    num += (long)s * weights[i];
    den += s;
  }
  if (den == 0) return lastPos;
  int pos = (int)(num / den);
  lastPos = pos;
  return pos;
}

void setup() {
  Serial.begin(115200);
  pinMode(S0, INPUT_PULLUP);
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);
  pinMode(S4, INPUT_PULLUP);
  lastT = millis();
}
void loop() {
  unsigned long now = millis();
  float dt = (now - lastT) / 1000.0f;
  if (dt <= 0) dt = 0.01f;
  lastT = now;
  float err = (float)linePosition();
  float d = (err - lastErr) / dt;
  lastErr = err;
  float turn = Kp * err + Kd * d;
  drive(BASE + (int)turn, BASE - (int)turn);
}
