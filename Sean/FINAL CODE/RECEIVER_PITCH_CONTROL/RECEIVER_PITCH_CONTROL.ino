#include <math.h>
#include <RH_ASK.h>
#include <Servo.h>

#include <SPI.h>
//#include <IRremote.hpp>

//#define IR_RECEIVE_PIN 5
#define PI 3.14159

const int irSensorPin = 5;


Servo servo1;
RH_ASK rf_driver(2000, 6, 7, 8);

float angle = 10.0;
float ans = 0.0;

int zone = 1;
int pangle;

float sangle = 0.0;
int irSensorValue;
int count = 0;


unsigned long lastOnTime = 0;
unsigned long mdel;
unsigned long time;
unsigned long bounce = 0.0;
uint8_t anglelen = sizeof(angle);

void setup() {

  Serial.begin(115200);

  pinMode(irSensorPin, INPUT_PULLUP);

 // IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  rf_driver.init();

  servo1.attach(1);
  servo1.write(angle);

  

  
}

void loop() {

  //pangle = (int *)angle;
 // ans = angle;

  /*
  if (IrReceiver.decode()) {
    zone = IrReceiver.decodedIRData.command;
    if (zone == 1 || zone == 2 || zone == 3 || zone == 4) {
      Serial.print("Zone = ");
      Serial.println(zone);
    }
    IrReceiver.resume();
  }

  */

  irSensorValue = digitalRead(irSensorPin);
  time = millis();

  if ((time - lastOnTime) > 500) {
      count = 0;
    }



  if (irSensorValue == LOW) {
   
    if ((millis() - bounce) > 200) {
      count++;
      bounce = millis();
      lastOnTime = millis();

      
        if (count == 3 && zone == 4){
          zone = 1;
          mdel = millis();
          //servo1.write((int)sangle);
          //Serial.println("Moving motor");
        } else if (count == 4 && zone == 3) {
          zone = 2;
         // sangle = 180 - sangle;
          mdel = millis();
         // servo1.write((int)sangle);
        }
      }

    
    Serial.print("Zone = ");
    Serial.println(zone);
    Serial.print("Count = ");
    Serial.println(count);
  }

   sangle = angle + 7.0;
  if (time - mdel > 1000) {
    if (zone == 1) {
      servo1.write((int)sangle);
      zone = 3;
    }
    if (zone == 2) {
      sangle = 180 - sangle;
      servo1.write((int)sangle);
      zone = 4;
    }
  }
  
 // /*
  if (rf_driver.recv((uint8_t *)&angle, &anglelen)) {

    Serial.println(angle, 4);

  }
//  */
 

}
