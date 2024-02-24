#include <Arduino.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK rf_driver(2000, 4, 2, 5);

float blade = 0.1;
float wind = 5.0;

char buffer_out[8];
char A[4];
float *pf;
int ind;




//REQUIRES CODE FOR ANEMOMETER AND SHAFT ROTATION VELOCITY INPUT

void setup()
{
  rf_driver.init();

/*
  Serial.begin(115200);	  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
*/
}

void loop()
{
  

  static char *msg = buffer_out;
   rf_driver.send((uint8_t *)buffer_out, strlen(buffer_out));
   rf_driver.waitPacketSent();
   blade += 0.1;
  delay(500);
}
