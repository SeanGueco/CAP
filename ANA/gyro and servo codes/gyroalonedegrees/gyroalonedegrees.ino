#include <Wire.h>

const int MPU_ADDR = 0x68;
int16_t gyro_x_raw, gyro_y_raw, gyro_z_raw;
float gyro_x, gyro_y, gyro_z;

float sensitivity = 131.0; // Sensitivity for ±250 degrees per second

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU6050();
}

void loop() {
  readMPU6050Data();
  convertRawToDegreesPerSecond();

  // Do something with the angular velocity values
  Serial.print("Gyro X: "); Serial.print(gyro_x); Serial.print(" degrees/s | ");
  Serial.print("Gyro Y: "); Serial.print(gyro_y); Serial.print(" degrees/s | ");
  Serial.print("Gyro Z: "); Serial.println(gyro_z); 

  delay(1000); // Adjust the delay as needed for your application
}

void setupMPU6050() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void readMPU6050Data() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43); // starting with register 0x43 (GYRO_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true); // request a total of 6 registers

  gyro_x_raw = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  gyro_y_raw = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  gyro_z_raw = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

void convertRawToDegreesPerSecond() {
  gyro_x = gyro_x_raw / sensitivity;
  gyro_y = gyro_y_raw / sensitivity;
  gyro_z = gyro_z_raw / sensitivity;
}