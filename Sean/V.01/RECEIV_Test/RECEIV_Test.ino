#include <math.h>
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver(2000, 4, 12, 10);

float blade = 0.0;
float wind = 0.0;
int size = sizeof(blade);

String str_blade;
String str_wind;
String str_out;


void setup() {

  Serial.begin(115200);
  
  
  rf_driver.init();
  if (!rf_driver.init()){
    Serial.println("init failed");
  }

}

void loop() {
  //RF RECEIVER PORTION
 
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen)) {
    Serial.println(buflen);
    
    str_out = String((char *)buf);

    for (int i = 0; i < str_out.length(); i++) {
      if (str_out.substring(i, i+1) == ",") {
        str_blade = str_out.substring(0, i-1);
        str_wind = str_out.substring(i + 1);
        break;
      }
    }
    blade = str_blade.toFloat();
    wind = str_wind.toFloat();
    Serial.print(blade);
    Serial.print(",");
    Serial.println(wind);
  }

}
