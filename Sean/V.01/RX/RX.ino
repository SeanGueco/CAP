#include <math.h>
#include <RH_ASK.h>
#include <Servo.h>

#include <SPI.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2
#define PI 3.14159

Servo servo1;
RH_ASK rf_driver(2000, 2, 12, 10);

float angle = 0.0;
float ans = 0.0;

int zone = 1;

String str_angle;

void setup() {
  Serial.begin(115200);

  rf_driver.init();

  servo1.attach(3);
 // servo1.write(angle);

  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  Serial.print("IR Receiver ready!");
}

void loop() {

  
  if (rf_driver.recv((uint8_t *)&angle, sizeof(angle))) {
    
    Serial.println(angle);
    
   // servo1.write(angle);
    delay(50);
  }

  if (IrReceiver.decode()) {
      zone = IrReceiver.decodedIRData.command;
      if (zone != 0){
        Serial.print("Zone = ");
        Serial.println(zone);
      }
      IrReceiver.resume();
  }


 // servo1.write(angle);


}
