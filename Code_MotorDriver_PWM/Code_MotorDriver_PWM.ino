/*******************************************************************************
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTY AND SUPPORT
 * IS APPLICABLE TO THIS SOFTWARE IN ANY FORM. CYTRON TECHNOLOGIES SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 ********************************************************************************
 * DESCRIPTION:
 *
 * This example shows how to drive 2 motors using 4 PWM pins (2 for each motor)
 * with 2-channel motor driver.
 * 
 * 
 * CONNECTIONS:
 * 
 * Arduino D12  - Motor Driver PWM 1A Input
 * Arduino D13  - Motor Driver PWM 1B Input
 * Arduino D14  - Motor Driver PWM 2A Input
 * Arduino D27 - Motor Driver PWM 2B Input
 * Arduino GND - Motor Driver GND
 *
 *
 * AUTHOR   : Kong Wai Weng
 * COMPANY  : Cytron Technologies Sdn Bhd
 * WEBSITE  : www.cytron.io
 * EMAIL    : support@cytron.io
 *
 *******************************************************************************/

 #include "CytronMotorDriver.h"


// Configure the motor driver.
CytronMD motor1(PWM_PWM, 12,13);   // PWM 1A = Pin 12, PWM 1B = Pin 13.
CytronMD motor2(PWM_PWM, 14, 27);  // PWM 2A = Pin 14, PWM 2B = Pin 27.


// The setup routine runs once when you press reset.
void setup() {
  
}


// The loop routine runs over and over again forever.
void loop() {
  motor1.setSpeed(128);   // Motor 1 runs forward at 50% speed.
  motor2.setSpeed(128);  // Motor 2 runs forward at 50% speed.
  delay(5000);
  
  motor1.setSpeed(-128);   // Motor 1 runs backward at 50% speed.
  motor2.setSpeed(-128);  // Motor 2 runs backward at 50% speed.
  delay(5000);

  motor1.setSpeed(0);     // Motor 1 stops.
  motor2.setSpeed(0);     // Motor 2 stops.
  delay(1000);

  motor1.setSpeed(255);  // Motor 1 runs forward at full speed.
  motor2.setSpeed(255);   // Motor 2 runs forward at full speed.
  delay(5000);
  
  motor1.setSpeed(-255);  // Motor 1 runs backward at full speed.
  motor2.setSpeed(-255);   // Motor 2 runs backward at full speed.
  delay(5000);

  motor1.setSpeed(0);     // Motor 1 stops.
  motor2.setSpeed(0);     // Motor 2 stops.
  delay(1000);
}