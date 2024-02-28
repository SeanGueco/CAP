#include <math.h>
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver(2000, 5, 2, 6);

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 1000;    // the debounce time; increase if the output flickers 

int pinInterrupt = 4; 

int Count=0;

float speed = 0.0;

void onChange()
{
   if ( digitalRead(pinInterrupt) == LOW )
      Count++;
}


void setup() {

  Serial.begin(115200); //Initialize serial port
  rf_driver.init();

  pinMode( pinInterrupt, INPUT_PULLUP);// set the interrupt pin

  

  //Enable
  attachInterrupt( digitalPinToInterrupt(pinInterrupt), onChange, FALLING);
   
}

void loop() {
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    Serial.print(Count*8.75);
    speed = Count*8.75;
    Serial.println(speed);
    Count=0;
    Serial.println("cm/s");
  }
  delay(1); 

  rf_driver.send((uint8_t *)&speed, sizeof(speed));
  rf_driver.waitPacketSent();
  
}