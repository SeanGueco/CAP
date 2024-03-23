#include <math.h>
#include <Servo.h>

Servo servo1;

float del = 0.0;
float angle = 90.0;
float ans = 0.0;
float time = 0.0;
float diff = 0.0;

void setup() {

  Serial.begin(115200);
  servo1.attach(1);
  servo1.write(angle);

}

void loop() {

  ans = angle;
  angle = 90.0*sin(1.0/800.0*time) + 90.0;
  servo1.write((int)angle);

  diff = abs(angle - ans);
  del = diff*(10.0/6.0);
  
  time += 1;
 // delay(del);
  
  servo1.write(angle);
  delay(100);
  //angle++;
}
