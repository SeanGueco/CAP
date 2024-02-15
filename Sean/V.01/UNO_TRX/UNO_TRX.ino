#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK rf_driver(2000, 4, 2, 5);

float blade = 0.1;
float wind = 0.2;

String str_blade;
String str_wind;
String str_out;

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
   //wind = anemometer input
   //blade = Shaft rotation input

   str_blade = String(blade);
   str_wind = String(wind);
   str_out = str_blade + "," + str_wind;

   //static char *msg = str_out.c_str();
  static char *msg = str_out.c_str();
   rf_driver.send((uint8_t *)msg, strlen(msg));
   rf_driver.waitPacketSent();
  delay(400);
}
