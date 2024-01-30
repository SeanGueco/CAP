// Define the pin to which the 4-wire digital anemometer is connected
const int anemometerPin = 2; // Change this to the actual digital pin number

// Calibration factor (replace with the actual calibration factor from your datasheet)
const float calibrationFactor = 0.1; // Example value, replace with the actual calibration factor

// Variables to hold wind speed-related information
volatile unsigned long pulseCount = 0;  // Count of pulses
unsigned long previousMillis = 0;       // Previous time
const int interval = 1000;              // Interval to calculate wind speed (in milliseconds)

void setup() {
  Serial.begin(9600); // Initialize serial communication

  // Attach the interrupt for the anemometer pin
  attachInterrupt(digitalPinToInterrupt(anemometerPin), countPulse, RISING);
}

void loop() {
  unsigned long currentMillis = millis();

  // Calculate wind speed every interval
  if (currentMillis - previousMillis >= interval) {
    // Calculate wind speed based on pulse count and calibration factor
    float windSpeed = (float)pulseCount * calibrationFactor;

    // Print wind speed
    Serial.print("Wind Speed: ");
    Serial.print(windSpeed);
    Serial.println(" meters per second");

    // Reset pulse count and update previousMillis
    pulseCount = 0;
    previousMillis = currentMillis;
  }
  // Other non-blocking tasks can be performed here
}

// Interrupt service routine to count pulses
void countPulse() {
  pulseCount++;
}