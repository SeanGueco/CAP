const int IR_SENSOR_PIN = 5;   // Replace with the actual pin connected to the IR sensor and LED
unsigned long lastOnTime = 0;
float distancePerPulse = 0.02;  // Replace with the actual linear distance per pulse in meters

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR_PIN, INPUT_PULLUP);
}

void loop() {
  int irSensorValue = digitalRead(IR_SENSOR_PIN);
Serial.println(irSensorValue);
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
      Serial.println(velocity, 4);  // Display velocity with 4 decimal places

      // Reset the last on time
      lastOnTime = 0;
    }
  }

  // Add a delay to avoid rapid readings and to make the output more readable
  delay(1000);
}
