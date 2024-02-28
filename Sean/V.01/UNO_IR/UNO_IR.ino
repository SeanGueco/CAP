#include <Arduino.h>

#define DISABLE_CODE_FOR_RECEIVER

#define IR_SEND_PIN 3

#include <IRremote.hpp>

#define DELAY_AFTER_SEND 250
#define DELAY_AFTER_LOOP 500

#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

void setup() {
    Serial.begin(115200);


#if defined(IR_SEND_PIN)
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and enable feedback LED at default feedback LED pin





uint16_t sAddress = 0x0102;
uint8_t sCommand = 1;
uint16_t s16BitCommand = 0x5634;
uint8_t sRepeats = 0;

void loop() {
 
    Serial.println(F("Send NEC with 8 bit address"));
    Serial.flush();
    IrSender.sendNEC(sAddress /*& 0xFF*/, sCommand, sRepeats);
    delay(DELAY_AFTER_SEND); // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal




    
    sCommand ++;
    if (sCommand > 4){
      sCommand = 1;
    }
    //s16BitCommand ++;
    //sRepeats++;
    // clip repeats at 4
    if (sRepeats > 4) {
        sRepeats = 4;
    }

    delay(DELAY_AFTER_LOOP); 
}