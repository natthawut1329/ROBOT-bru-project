# ROBOT-bru-project
หุ่นยนต์เดินตามเส้นระดับมัธยมศึกษา
# 🤖 หุ่นยนต์เดินตามเส้นด้วย Robo ESP32  
**(Arduino Line Follower Robot with Robo ESP32)**

โครงการนี้ใช้บอร์ด **Robo ESP32** สร้างหุ่นยนต์เดินตามเส้น (Line Follower Robot) — เรียนรู้ไมโครคอนโทรลเลอร์, IoT และการประมวลผลเซ็นเซอร์

---

##  Getting Started with Robo ESP32  
เริ่มต้นที่ Cytron ได้เลยที่: [Getting Started with Robo ESP32 via Arduino IDE (Thai)](https://th.cytron.io/tutorial/getting-started-guide-with-robo-esp32-arduino-ide)  
— คู่มือนี้ครอบคลุมตั้งแต่การตั้งค่าบอร์ด ESP32, ติดตั้งไดรเวอร์ CP210x, จ่ายไฟให้บอร์ด และตัวอย่างโค้ดพื้นฐาน
การตั้งค่าบอร์ด ESP32: [Setting up the Robo ESP32](https://th.cytron.io/tutorial/setting-up-the-robo-esp32-arduino)

---

##  Features (คุณสมบัติ)
- ใช้ **Robo ESP32** เป็นไมโครคอนโทรลเลอร์หลัก
- เซ็นเซอร์ติดตามเส้น (IR Sensor/Line Sensor Array)
- ควบคุมมอเตอร์ผ่าน Motor Driver
- ปรับความเร็วและความแม่นยำของการเดินได้
- รองรับ Wi-Fi สำหรับอนาคต (ตัวเลือกเพิ่มเติม)

---

##  อุปกรณ์ (Hardware)
- Robo ESP32 Development Board  
- Motor Driver (L298N/L293D)  
- DC Motors + Wheels  
- IR Line Sensors (3–5 ตัว)  
- แหล่งจ่ายไฟ (Li-Po หรือแบตเตอรี่)
- โครงหุ่นยนต์ (Chassis)

---

##  Software
- Arduino IDE (พร้อมติดตั้ง ESP32 Board Support)
- ไลบรารีที่เกี่ยวข้อง (เช่น `Arduino.h`, `Wire.h`, `ESP32Servo.h`)

---

##  การต่อวงจร (Circuit Diagram)
- IR Line Sensor → GPIO ESP32  
- Motor Driver → PWM/GPIO ESP32  
- Power Supply → Board + Motor Driver  
*(สามารถใส่รูปหรือ Fritzing Diagram เพิ่มที่นี่)*

