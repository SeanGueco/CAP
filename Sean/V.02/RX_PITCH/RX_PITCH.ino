#include <math.h>
#include <RH_ASK.h>
#include <Servo.h>

#include <SPI.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2
#define PI 3.14159

Servo servo1;
RH_ASK rf_driver(2000, 3, 12, 10);

float angle = 0.0;
float ans = 0.0;

int zone = 0;
int pangle;

void setup() {

  Serial.begin(115200);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);


  servo1.attach(5);
  servo1.write(angle);

  rf_driver.init();

  
}

void loop() {

  pangle = (int)angle;
  ans = angle;

  if (IrReceiver.decode()) {
    zone = IrReceiver.decodedIRData.command;
    if (zone == 1 || zone == 2 || zone == 3 || zone == 4) {
      Serial.print("Zone = ");
      Serial.println(zone);
    }
    IrReceiver.resume();
  }

  

  if (rf_driver.recv((uint8_t *)&angle, sizeof(angle))) {

    Serial.println(angle, 4);

  }

 // servo1.write((int)angle);
 // delay(20);



 
    if (zone == 1) {
        angle += 7.0;
        
          servo1.write((int)angle);
        
      }

      else if (zone == 3) {
        angle += 7.0;
        angle = 180 - angle;
        
          servo1.write((int)angle);
        
      }
 
}
