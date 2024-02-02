#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2


void setup()
{
  // There's no need to set up the IR_RECEIVE_PIN with pinMode
  // the library takes care of that...
  // pinMode(IR_RECEIVE_PIN, INPUT);

  Serial.begin(115200);

  while(!Serial)
  {  }

  // Enable the IR receiver
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print("IR Receiver ready!");
}
int x = 1;

void loop()
{
  

  // decode returns 1 if something was received
  // otherwise it returns 0
  // The code and protocol type get stored in results
  if (IrReceiver.decode()) {

	    //Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
      // USE NEW 3.x FUNCTIONS
      /*
      IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
      */

      x = IrReceiver.decodedIRData.command;
      Serial.println(x);
      IrReceiver.resume();
  }
}