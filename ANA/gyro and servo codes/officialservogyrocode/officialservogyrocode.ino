#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

Servo servo;
Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(9600);
  servo.attach(9);
  Wire.begin();
  mpu.begin();
  servo.write(90); // Set the initial position to the center

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(300);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  // Use the y-axis acceleration to control the servo
  int servoPosition = map(accel.acceleration.y, -10, 10, 0, 180);

  // Use the x-axis gyroscope reading to adjust the servo position
  int gyroAdjustment = map(gyro.gyro.x, -100, 100, -30, 30);
  servoPosition += gyroAdjustment;

  // Ensure that the servo position is within the valid range
  servoPosition = constrain(servoPosition, 0, 180);

  // Set the servo position
  servo.write(servoPosition);

  Serial.print("Accelerometer: ");
  Serial.print(accel.acceleration.y);
  Serial.print(", Gyroscope: ");
  Serial.print(gyro.gyro.x);
  Serial.print(", Servo Position: ");
  Serial.println(servoPosition);

  delay(300);
}