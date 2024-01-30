#include <math.h>
#include <Servo.h>

Servo servo1;

float del = 0.0;
float angle = 91.0;
float ans = 0.0;
float time = 0.0;
float diff = 0.0;

void setup() {

  Serial.begin(9600);
  servo1.attach(3);
  servo1.write(angle);

}

void loop() {

  ans = angle;
  angle = 90.0*sin(1.0/2000.0*time) + 91.0;
  servo1.write((int)angle);

  diff = abs(angle - ans);
  del = diff*(10.0/6.0);
  
  time += del + 1;
  delay(del);
  
}
