#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver(2000, 4, 2, 10);

void setup()
{
  driver.init();
 
  Serial.begin(115200);	  // Debugging only
  /*
  if (!driver.init()) {
    Serial.println("init failed");
  } else {
    Serial.println("driver begin");
  }
  */
}

void loop()
{
    const char *msg = "Hello World!";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println("Sending...");
    delay(200);

}
