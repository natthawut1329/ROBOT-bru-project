/*
  Robo ESP32 + Maker Line — 5x DIGITAL outputs version (PID/PD compatible)
  - Line sensor provides 5 digital signals (0/1) instead of analog.
  - Many sensors output LOW on black, HIGH on white. If yours is opposite,
    set INVERT=true below.
  - Weighted average uses s_i in {0,1} -> coarser, but works well with PD/PID.
*/

#include "CytronMotorDriver.h"

CytronMD motorL(PWM_PWM, 12, 13);
CytronMD motorR(PWM_PWM, 14, 27);

// ---- 5x DIGITAL line sensor pins ----
const int S0=36;  // ADC-capable pins are fine for digital too
const int S1=39;
const int S2=34;
const int S3=35;
const int S4=32;
int pins[5]={S0,S1,S2,S3,S4};

// position weights: left -> -2000 ... center -> 0 ... right -> +2000
int weights[5]={-2000,-1000,0,1000,2000};

// sensor polarity
bool INVERT = true;       // true if sensor outputs LOW on black (common case)

// base speed & gains
int BASE = 170;
float Kp = 0.16, Ki = 0.0, Kd = 1.0;

// state
float integ=0, lastErr=0;
unsigned long lastT=0;
int lastPos=0;  // remember last known position when all sensors see white

void drive(int L,int R){
  L = L<-255?-255:(L>255?255:L);
  R = R<-255?-255:(R>255?255:R);
  motorL.setSpeed(L); motorR.setSpeed(R);
}

int readBit(int i){
  int v = digitalRead(pins[i]);
  // map to "on line" = 1, "off line" = 0
  if(INVERT) v = !v;         // if LOW on black -> invert so black=1
  return v ? 1 : 0;
}

int linePosition(){
  long num=0, den=0;
  for(int i=0;i<5;i++){
    int s = readBit(i);      // s in {0,1}
    num += (long)s * weights[i];
    den += s;
  }
  if(den==0){
    // lost line -> return last position (helps recovery)
    return lastPos;
  }
  int pos = (int)(num/den);  // -2000..2000
  lastPos = pos;
  return pos;
}

void setup(){
  Serial.begin(115200);
  // declare digital inputs
  pinMode(S0, INPUT_PULLUP);
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);
  pinMode(S4, INPUT_PULLUP);

  // simple spin test
  drive(150,150); delay(300);
  drive(-150,-150); delay(300);
  drive(0,0); delay(200);

  lastT = millis();
}

void loop(){
  unsigned long now=millis();
  float dt=(now-lastT)/1000.0f; if(dt<=0) dt=0.01f; lastT=now;

  int   err = linePosition();
  float dErr= (err - lastErr)/dt;
  integ += err*dt;
  lastErr = err;

  // choose PD or PID
  float turn = Kp*err + Kd*dErr + Ki*integ;

  int L = BASE + (int)turn;
  int R = BASE - (int)turn;
  drive(L,R);
}
