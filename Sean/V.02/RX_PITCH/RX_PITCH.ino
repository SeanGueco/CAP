#include <math.h>
#include <RH_ASK.h>
#include <Servo.h>

#include <SPI.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 3
#define PI 3.14159

Servo servo1;
RH_ASK rf_driver(2000, 2, 12, 10);

float angle = 0.0;
float ans = 0.0;

int zone = 0;


void setup() {

  Serial.begin(115200);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  rf_driver.init();

  servo1.attach(4);
  servo1.write(angle);

}

void loop() {

  if (IrReceiver.decode()) {
    zone = IrReceiver.decodedIRData.command;
    if (zone != 0){
      Serial.print("Zone = ");
      Serial.println(zone);
    }
    IrReceiver.resume();
  }
  
  if (rf_driver.recv((uint8_t *)&angle, sizeof(angle))) {
    
    Serial.println(angle, 4);
    
    ans = angle;

    if (zone == 1) {
      angle += 7.0;
      if (angle >= 70.44) {
        angle = 70.0;
      }
      if (angle > (ans + 2) || angle < (ans - 2)){
        servo1.write((int)angle);
      }
    }

    if (zone == 3) {
      angle += 7.0;
      angle = 180 - angle;
      if (angle <= 116.56) {
      angle = 117.0;
      }
      if (angle != ans){
        servo1.write((int)angle);
      }
    }

  }





}
