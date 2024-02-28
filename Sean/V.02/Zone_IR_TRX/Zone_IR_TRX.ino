#include <RH_ASK.h>
#include <SPI.h>
 
RH_ASK rf_driver(2000, 5, 2, 6);
 
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 1000;    // the debounce time; increase if the output flickers
 
int pinInterrupt = 4;
 
int Count = 0;
 
float speed = 0.0;
 
void onChange()
{
   if (digitalRead(pinInterrupt) == LOW)
      Count++;
}
 
void setup() {
   Serial.begin(115200); // Initialize serial port
   rf_driver.init();
 
   pinMode(pinInterrupt, INPUT_PULLUP);  // set the interrupt pin
 
   // Enable interrupt
   attachInterrupt(digitalPinToInterrupt(pinInterrupt), onChange, FALLING);
}
 
void loop() {
   if ((millis() - lastDebounceTime) > debounceDelay) {
      lastDebounceTime = millis();
      Serial.print(Count * 8.75);
      speed = Count * 8.75;
      Count = 0;
      Serial.println("cm/s");
   }
   delay(1);
 
   // Receive data using RadioHead library
   uint8_t buf[sizeof(speed)];
   uint8_t buflen = sizeof(buf);
   if (rf_driver.recv(buf, &buflen)) {
      float receivedSpeed;
      memcpy(&receivedSpeed, buf, sizeof(receivedSpeed));
      Serial.print("Received Speed: ");
      Serial.print(receivedSpeed);
      Serial.println(" cm/s");
   }
}