#include <Servo.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;
Servo myservo;

int val;
int prevVal;

int minAccelValue = 0;
int maxAccelValue = 0;

void setup() {
    Wire.begin();
    Serial.begin(9600);

    mpu.initialize();
    myservo.attach(9);
     myservo.write(90);
}

void loop() {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Dynamically adjust the range based on actual accelerometer readings
    if (ay < minAccelValue) {
        minAccelValue = ay;
    }
    if (ay > maxAccelValue) {
        maxAccelValue = ay;
    }

    // Map accelerometer values to servo angle
    val = map(ay, minAccelValue, maxAccelValue, 0, 179);

    if (val != prevVal) {
        myservo.write(val);
        prevVal = val;
    }

    // Debugging output
    Serial.print("Raw ay: "); Serial.print(ay);
    Serial.print(" | Mapped val: "); Serial.println(val);

    delay(500);
}