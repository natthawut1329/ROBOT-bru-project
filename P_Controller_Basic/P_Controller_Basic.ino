/*
  P Controller (พื้นฐาน เข้าใจง่าย) — Robo ESP32 + Maker Line (3 เซ็นเซอร์แบบ Digital)
  เหมาะสำหรับอธิบายนักเรียนระดับมัธยม
*/

#include "CytronMotorDriver.h"

CytronMD motorL(PWM_PWM, 12, 13);
CytronMD motorR(PWM_PWM, 14, 27);

// --- ขาเซ็นเซอร์แบบ Digital (3 ตัว) ---
const int SL = 39;  // ซ้าย
const int SC = 34;  // กลาง
const int SR = 35;  // ขวา

bool INVERT = true;  // ถ้า LOW=ดำ ให้ true เพื่อให้ดำ=1, ขาว=0

// --- พารามิเตอร์ควบคุม ---
int BASE = 150;  // ความเร็วพื้นฐาน 0..255
int Kp = 60;     // ค่าขยาย P (เช่น 40..90)

void drive(int L, int R) {
  if (L > 255) L = 255;
  if (L < -255) L = -255;
  if (R > 255) R = 255;
  if (R < -255) R = -255;
  motorL.setSpeed(L);
  motorR.setSpeed(R);
}

// อ่านเซ็นเซอร์แล้วคืนค่า 0/1 (ดำ=1, ขาว=0)
int readBit(int pin) {
  int v = digitalRead(pin);
  if (INVERT) v = !v;
  return v ? 1 : 0;
}

// ให้ error = -1, 0, +1 อย่างง่าย
int readError() {
  int L = readBit(SL);
  int C = readBit(SC);
  int R = readBit(SR);

  if (C == 1) return 0;             // กลางเจอเส้น → วิ่งตรง
  if (L == 1 && R == 0) return -1;  // เอียงซ้าย → เลี้ยวซ้าย
  if (R == 1 && L == 0) return +1;  // เอียงขวา → เลี้ยวขวา
  if (L == 1 && R == 1) return 0;   // ทางแยก/มุมกว้าง → วิ่งตรง

  return +1;  // ไม่เจอเส้นเลย → หมุนหาขวา
}

void setup() {
  Serial.begin(115200);
  pinMode(SL, INPUT_PULLUP);
  pinMode(SC, INPUT_PULLUP);
  pinMode(SR, INPUT_PULLUP);
}

void loop() {
  int error = readError();  // -1, 0, +1
  int turn = Kp * error;    // -Kp, 0, +Kp

  int left = BASE + turn;
  int right = BASE - turn;
  drive(left, right);

  // แสดงผลใน Serial Monitor (ช่วยสอนนักเรียน)
  Serial.print("LCR=");
  Serial.print(readBit(SL));
  Serial.print(readBit(SC));
  Serial.print(readBit(SR));
  Serial.print("  error=");
  Serial.print(error);
  Serial.print("  turn=");
  Serial.print(turn);
  Serial.print("  L/R=");
  Serial.print(left);
  Serial.print("/");
  Serial.println(right);

  delay(10);
}
