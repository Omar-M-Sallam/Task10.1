#include <Wire.h>

const int MPU6050_ADDR = 0x68;  // MPU6050 I2C address
int16_t gyroZ;
float yaw = 0;
unsigned long prevTime;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Wake up MPU6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0x00);  // Wake up MPU6050
  Wire.endTransmission();

  prevTime = millis();
}

void loop() {
  // Request gyro Z-axis data
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x47);  // Gyro Z-axis high byte register
  Wire.endTransmission();
  Wire.requestFrom(MPU6050_ADDR, 2);  // Request 2 bytes

  // Combine high and low bytes to get raw gyro Z-axis value
  gyroZ = Wire.read() << 8 | Wire.read();

  // Calculate time difference
  unsigned long currentTime = millis();
  float dt = (currentTime - prevTime) / 1000.0;
  prevTime = currentTime;

  // Convert to degrees per second and update yaw
  yaw += (gyroZ / 131.0) * dt;

  // Print yaw value
  Serial.print("Yaw: ");
  Serial.println(yaw);
  
  delay(100);
}
