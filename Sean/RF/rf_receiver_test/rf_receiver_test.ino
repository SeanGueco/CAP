#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver(2000, 2, 4, 5);

void setup()
{
    Serial.begin(115200);	// Debugging only
    driver.init();
    if (!driver.init()) {
         Serial.println("init failed");
    } else {
      Serial.println("driver begin");
    }
}

void loop()
{
    uint8_t buf[20];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);         
    } 
}
