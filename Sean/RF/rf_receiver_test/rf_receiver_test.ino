#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver(2000, 2, 4, 5);

float result = 0.0;

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
    //uint8_t buf[20];
    //uint8_t buflen = sizeof(buf);
    if (driver.recv((uint8_t *)&result, sizeof(result))) // Non-blocking
    {
      Serial.println(result);         
    } 
    
}
