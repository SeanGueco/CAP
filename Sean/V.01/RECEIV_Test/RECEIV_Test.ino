#include <math.h>
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver(2000, 4, 12, 10);

float blade = 0.0;
//float wind = 0.0;

String str_blade;
//String str_wind;
//String str_out;


void setup() {

  Serial.begin(115200);
  
  
  rf_driver.init();
  if (!rf_driver.init()){
    Serial.println("init failed");
  }

}

void loop() {
  //RF RECEIVER PORTION
  uint8_t buf[4];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen)) {
    str_blade = String((char *)buf);

    Serial.println(str_blade);
    blade = str_blade.toFloat();
   
    Serial.println(blade);
   
  }

}
