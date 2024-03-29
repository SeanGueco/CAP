#include <Arduino.h>

#define DISABLE_CODE_FOR_RECEIVER

#define IR_SEND_PIN 3

#include <IRremote.hpp>

#define DELAY_AFTER_SEND 250
#define DELAY_AFTER_LOOP 1000

#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

#include <math.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK rf_driver(2000, 4, 2, 5);

float angle = 0.0;
float ans = 0.0;
float time = 0.0;
float diff = 0.0;
float del = 100.0;


//REQUIRES CODE FOR ANEMOMETER AND SHAFT ROTATION VELOCITY INPUT

void setup()
{
  

  Serial.begin(115200);	  // Debugging only
  /*
  if (!driver.init())
    Serial.println("init failed");
  */
  rf_driver.init();

  IrSender.begin();
}

uint16_t sAddress = 0x0102;
uint8_t sCommand = 1;
uint16_t s16BitCommand = 0x5634;
uint8_t sRepeats = 0;


void loop()
{

   // angle = 0.0;

   // rf_driver.send((uint8_t *)&angle, sizeof(angle));
  // rf_driver.waitPacketSent();

  // delay(500);
  if (angle < 1) {
    angle = 180.0;
  } else {
    angle = 0.0;
  }
   //angle = 180.0;
   ans = angle;
   //angle = 90.0*sin(1.0/750.0*time) + 90.0;

  diff = abs(angle - ans);
  //del = diff*(10.0/6.0);

   rf_driver.send((uint8_t *)&angle, sizeof(angle));
   rf_driver.waitPacketSent();

   Serial.println(angle);
  // blade += 0.5;
   time += del + 1;
   delay(1000);

  /*
  Serial.println(F("Send NEC with 8 bit address"));
    Serial.flush();
    IrSender.sendNEC(sAddress , sCommand, sRepeats);
    delay(DELAY_AFTER_SEND);

  sCommand ++;
    if (sCommand > 4){
      sCommand = 1;
    }
    delay(DELAY_AFTER_LOOP);
  */
}
