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

#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/|| defined(USBCON) /*STM32_stm32*/|| defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

#if defined(IR_SEND_PIN)
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and enable feedback LED at default feedback LED pin
#  if defined(IR_SEND_PIN_STRING)
    Serial.println(F("Send IR signals at pin " IR_SEND_PIN_STRING));
#  else
    Serial.println(F("Send IR signals at pin " STR(IR_SEND_PIN)));
#  endif
#else
    // Here the macro IR_SEND_PIN is not defined or undefined above with #undef IR_SEND_PIN
    uint8_t tSendPin = 3;
    IrSender.begin(tSendPin, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN); // Specify send pin and enable feedback LED at default feedback LED pin
    // You can change send pin later with IrSender.setSendPin();

    Serial.print(F("Send IR signals at pin "));
    Serial.println(tSendPin);
#endif

#if !defined(SEND_PWM_BY_TIMER)
    /*
     * Print internal software PWM signal generation info
     */
    IrSender.enableIROut(38); // Call it with 38 kHz just to initialize the values printed below
    Serial.print(F("Send signal mark duration is "));
    Serial.print(IrSender.periodOnTimeMicros);
    Serial.print(F(" us, pulse narrowing correction is "));
    Serial.print(IrSender.getPulseCorrectionNanos());
    Serial.print(F(" ns, total period is "));
    Serial.print(IrSender.periodTimeMicros);
    Serial.println(F(" us"));
#endif
}

/*
 * Set up the data to be sent.
 * For most protocols, the data is build up with a constant 8 (or 16 byte) address
 * and a variable 8 bit command.
 * There are exceptions like Sony and Denon, which have 5 bit address.
 */
uint16_t sAddress = 0x0102;
uint8_t sCommand = 1;
uint16_t s16BitCommand = 0x5634;
uint8_t sRepeats = 0;

void loop() {
    /*
     * Print values
     */
    Serial.println();
    Serial.print(F("address=0x"));
    Serial.print(sAddress, HEX);
    Serial.print(F(" command=0x"));
    Serial.print(sCommand, HEX);
    Serial.print(F(" repeats="));
    Serial.println(sRepeats);
    Serial.println();
    Serial.println();
    Serial.flush();

    Serial.println(F("Send NEC with 8 bit address"));
    Serial.flush();
    IrSender.sendNEC(sAddress /*& 0xFF*/, sCommand, sRepeats);
    delay(DELAY_AFTER_SEND); // delay must be greater than 5 ms (RECORD_GAP_MICROS), otherwise the receiver sees it as one long signal

    /*
    Serial.println(F("Send NEC with 16 bit address"));
    Serial.flush();
    IrSender.sendNEC(sAddress, sCommand, sRepeats);
    delay(DELAY_AFTER_SEND);

    Serial.println(F("Send NEC2 with 16 bit address"));
    Serial.flush();
    IrSender.sendNEC2(sAddress, sCommand, sRepeats);
    delay(DELAY_AFTER_SEND);

    */


#if FLASHEND >= 0x3FFF && (RAMEND >= 0x4FF || RAMSIZE >= 0x4FF) // For 16k flash or more, like ATtiny1604. Code does not fit in program memory of ATtiny85 etc.
    /*
     * Next example how to use the IrSender.write function
     */
    IRData IRSendData;
    // prepare data
    IRSendData.address = sAddress;
    IRSendData.command = sCommand;
    IRSendData.flags = IRDATA_FLAGS_EMPTY;



    // Bang&Olufsen must be sent with 455 kHz
//    Serial.println(F("Send Bang&Olufsen"));
//    Serial.flush();
//    IrSender.sendBangOlufsen(sAddress, sCommand, sRepeats);
//    delay(DELAY_AFTER_SEND);
/*
    IRSendData.protocol = BOSEWAVE;
    Serial.println(F("Send Bosewave with no address and 8 command bits"));
    Serial.flush();
    IrSender.write(&IRSendData, sRepeats);
    delay(DELAY_AFTER_SEND);
*/


#endif // FLASHEND
    /*
     * Force buffer overflow
     */
     /*
    Serial.println(F("Force buffer overflow by sending 700 marks and spaces"));
    for (unsigned int i = 0; i < 350; ++i) {
        // 400 + 400 should be received as 8/8 and sometimes as 9/7 or 7/9 if compensation by MARK_EXCESS_MICROS is optimal.
        // 210 + 540 = 750 should be received as 5/10 or 4/11 if compensation by MARK_EXCESS_MICROS is optimal.
        IrSender.mark(210); // 8 pulses at 38 kHz
        IrSender.space(540); // to fill up to 750 us
    }
    delay(DELAY_AFTER_SEND);
    */
    /*
     * Increment values
     * Also increment address just for demonstration, which normally makes no sense
     */
    
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

    delay(DELAY_AFTER_LOOP); // additional delay at the end of each loop
}