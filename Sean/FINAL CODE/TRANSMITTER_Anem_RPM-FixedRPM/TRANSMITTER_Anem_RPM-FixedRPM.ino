//#include <IRremote.h>
#include <math.h>
#include <RH_ASK.h>
#include <SPI.h>

#define PI 3.14159
//const int irSensorPin = 6;       // Replace with the actual pin connected to the IR sensor
   // Replace with the actual pin connected to the RF transmitter
 
RH_ASK rfDriver(2000, 11, 2, 12);
 
unsigned long lastOnTime = 0;
float distancePerPulse = 0.08;
float blade = 2.5;
float shaft = 0;
float wind = 0;
float angle = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 1000;
int pinInterrupt = 3;
int Count = 0;
 
void onChange()
{
   if (digitalRead(pinInterrupt) == LOW)
      Count++;
}
 
void setup() {
  Serial.begin(115200);
 
  rfDriver.init();
  // Initialize RF Transmitter
  if (!rfDriver.init())
    Serial.println("RF transmitter initialization failed");
 
  // Initialize IR Sensor
 // pinMode(irSensorPin, INPUT_PULLUP);
 
  // Initialize Anemometer
  pinMode(pinInterrupt, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinInterrupt), onChange, FALLING);
}
 
void loop() {
  // Check IR sensor for data
 // int irSensorValue = digitalRead(irSensorPin);
 /*
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
      shaft = distancePerPulse / (duration / 1000.0);
      blade = 0.15*shaft/0.0127;
 
      // Print the velocity to the serial monitor
      Serial.print("IR Sensor Linear Velocity: ");
      Serial.println(blade, DEC);  // Display velocity with 4 decimal places
 
      // Reset the last on time
      lastOnTime = 0;
 
      // Send the linear velocity over RF transmitter
     // sendRFSignal(blade);
    }
  }
 */
  // Anemometer logic
  if ((millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    Serial.print("Anemometer Speed: ");
    Serial.print(Count * 8.75/100);
    wind=Count*8.75/100;
    Count = 0;
    Serial.println(" m/s");
  }
 
  // Add a delay to avoid rapid readings and to make the output more readable
  delay(200);

  angle = atan(blade/wind)*180.0/PI;
  Serial.println(angle);
  sendRFSignal(angle);
}
 
void sendRFSignal(float value) {
  // Send the raw binary data of the float
  rfDriver.send((uint8_t *)&value, sizeof(value));
  rfDriver.waitPacketSent();
}