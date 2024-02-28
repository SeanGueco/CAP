#include <RH_ASK.h>
#include <SPI.h>
 
const int ledPin = 5;  // Pin number for the LED
volatile unsigned long long lastPulseTime = 0;  // Variable to store the time of the last pulse
 
// Constants for your specific system
const float linearDistancePerPulse = 0.02;  // Replace with the actual linear distance covered by each pulse (in meters)
 
// Exponential Moving Average parameters
const float alpha = 0.2;  // Smoothing factor (adjust as needed)
 
float smoothedSpeed = 0.0;  // Variable to store the current speed
 
RH_ASK driver(2000, 2, 4, 10);
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, INPUT);  // Assuming the LED pulses are detected as changes in this pin
  attachInterrupt(digitalPinToInterrupt(ledPin), handlePulse, FALLING);
 
  driver.init();
}
 
void loop() {
  handlePulse(); // Add any additional code or tasks here if needed
}
 
void handlePulse() {
  unsigned long long currentTime = micros();  // Get the current time in microseconds
  unsigned long long timeBetweenPulses = currentTime - lastPulseTime;  // Calculate time between pulses
 
  // Check if time between pulses is too small
  if (timeBetweenPulses < 1) {
    // Avoid division issues, set a minimum time to prevent extremely high speeds
    timeBetweenPulses = 1;
  }
 
  // Calculate speed in meters per second
  float speed = linearDistancePerPulse / (timeBetweenPulses / 1000000.0);  // Convert time to seconds
 
  // Apply exponential moving average for smoothing
  smoothedSpeed = alpha * speed + (1 - alpha) * smoothedSpeed;
 
  // Limit the speed to a maximum of 5 meters per second
  smoothedSpeed = min(smoothedSpeed, 5.0);
 
  Serial.print("Time between pulses: ");
  Serial.print(static_cast<unsigned long>(timeBetweenPulses));  // Explicit cast to avoid ambiguity
  Serial.print(" microseconds. Smoothed Speed: ");
  Serial.print(smoothedSpeed);
  Serial.println(" meters per second");
 
  lastPulseTime = currentTime;  // Update last pulse time
  // Transmit data using RadioHead library
  const char *msg = "Hello World!";
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  Serial.println("Sending...");
  delay(500);
}