#include <math.h>
#include <Servo.h>

Servo servo1;
int del = 50;
float angle = 0.0;
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
  angle = 90.0*sin(1.0/100.0*time) + 90.0;
  servo1.write((int)angle);

  diff = angle - ans;
  del = abs(diff*(10.0/6.0));
  
  time += (float)del;
  delay(del);
  
}
