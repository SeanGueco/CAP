#include <IRremote.h>
#include <RH_ASK.h>
#include <SPI.h>
 
// Pin configurations for Arduino Nano
const int irSensorPin = 2;       // Replace with the actual pin connected to the IR sensor
const int transmitterPin = 3;   // Replace with the actual pin connected to the RF transmitter
 
// RF Transmitter setup
RH_ASK rfDriver(2000,6,3,5);
 
unsigned long lastOnTime = 0;
float distancePerPulse = 0.0127;  // Replace with the actual linear distance per pulse in meters
 
void setup() {
  Serial.begin(9600);
 
  // Initialize RF Transmitter
  if (!rfDriver.init())
    Serial.println("RF transmitter initialization failed");
 
  // Initialize IR Sensor
  pinMode(irSensorPin, INPUT_PULLUP);
}
 
void loop() {
  // Check IR sensor for data
  int irSensorValue = digitalRead(irSensorPin);
 
  if (irSensorValue == HIGH) {
    // LED is turned on
    if (lastOnTime == 0) {
      // Record the time when the LED turns on for the first time
      lastOnTime = millis();
    }
  } else {
    // LED is turned off
    if (lastOnTime != 0) {
      // Calculate the duration between turning on and off
      unsigned long duration = millis() - lastOnTime;
 
      // Convert the duration to linear velocity (meters per second)
      float velocity = distancePerPulse / (duration / 1000.0);
 
      // Print the velocity to the serial monitor
      Serial.print("IR Sensor Linear Velocity: ");
      Serial.println(velocity, 4);  // Display velocity with 4 decimal places
 
      // Reset the last on time
      lastOnTime = 0;
 
      // Send the linear velocity over RF transmitter
      sendRFSignal(velocity);
    }
  }
 
  // Add a delay to avoid rapid readings and to make the output more readable
  delay(1000);
}
 
void sendRFSignal(float value) {
  // Send the raw binary data of the float
  rfDriver.send((uint8_t *)&value, sizeof(value));
  rfDriver.waitPacketSent();
}