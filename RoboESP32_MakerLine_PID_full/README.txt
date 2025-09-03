

### 4) เวอร์ชัน 5x DIGITAL Outputs (สำหรับเซ็นเซอร์ที่มีเอาต์พุตดิจิทัลทั้งหมด)
ไฟล์:
- `RoboESP32_MakerLine_PID_DIGITAL.ino`  (PID/PD ได้)
- `RoboESP32_MakerLine_PD_DIGITAL.ino`   (PD อย่างเดียว)

การตั้งค่า:
- `INVERT=true` ถ้าเซ็นเซอร์ **ให้ LOW เมื่อเซ็นทับเส้นดำ** (พบบ่อย)
- ใช้ `INPUT_PULLUP` กับขา S0..S4 (ต่อปุ่ม/ตัวต้านทานภายนอกได้ตามโมดูล)
- `linePosition()` ใช้ค่า {0,1} และ weights เพื่อคำนวณตำแหน่ง -2000..2000
- ถ้าหลุดเส้น (den==0) จะใช้ `lastPos` เพื่อช่วยคืนสู่เส้นเดิม
