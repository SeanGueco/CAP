#include <math.h>
#include <RH_ASK.h>
#include <Servo.h>

#include <SPI.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2
#define PI 3.14159

Servo servo1;
RH_ASK rf_driver(2000, 4, 12, 10);

float del = 0.0;
float angle = 90.0;
float ans = 0.0;
float diff = 0.0;
float blade = 0.0;
float wind = 0.01;

String str_blade;
String str_wind;
String str_out;

int zone = 1; //Default IR Zone
void setup() {

  Serial.begin(115200);
  
  
  rf_driver.init();
  if (!rf_driver.init()){
    Serial.println("init failed");
  }

  servo1.attach(3);
  servo1.write(angle);

 // IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
 // Serial.print("IR Receiver ready!");

}

void loop() {
  //RF RECEIVER PORTION
  uint8_t buf[11];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen)) {
    str_out = String((char *)buf);

    for (int i = 0; i < str_out.length(); i++) {
      if (str_out.substring(i, i+1) == ",") {
        str_blade = str_out.substring(0, i);
        str_wind = str_out.substring(i + 1);
        break;
      }
    }
    blade = str_blade.toFloat();
    wind = str_wind.toFloat();
    Serial.print(blade);
    Serial.print(",");
    Serial.println(wind);
    ans = angle;
  angle = atan(blade/wind)*180.0/PI;

  if (zone == 1 || zone == 2) {
    angle += 7.0;
    if (angle >= 70.44) {
      angle = 70.0;
    }
    if (angle > (ans + 2) || angle < (ans - 2)){
      servo1.write((int)angle);
      diff = abs(angle - ans);
      del = diff * (15.0/6.0);
      //delay(del);
    }
  }
  }
/*
  //IR RECEIVER PORTION
  if (IrReceiver.decode()) {
      zone = IrReceiver.decodedIRData.command;
      if (zone != 0){
        Serial.print("Zone = ");
        Serial.println(zone);
      }
      IrReceiver.resume();
  }

*/
/*
  //MOTOR CONTROL
  ans = angle;
  angle = atan(blade/wind)*180.0/PI;

  if (zone == 1 || zone == 2) {
    angle += 7.0;
    if (angle >= 70.44) {
      angle = 70.0;
    }
    if (angle > (ans + 2) || angle < (ans - 2)){
      servo1.write((int)angle);
      diff = abs(angle - ans);
      del = diff * (15.0/6.0);
      delay(del);
    }
  }

  if (zone == 3 || zone == 4) {
    angle -= 7.0;
    angle = 180 - angle;
    if (angle <= 116.56) {
      angle = 117.0;
    }
    if (angle != ans){
      servo1.write((int)angle);
      diff = abs(angle - ans);
      del = diff * (15.0/6.0);
      delay(del);
    }
  }
  */
}
