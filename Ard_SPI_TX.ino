#include <SPI.h>
#include <RF24.h>
#include <TimeLib.h>


RF24 radio(9, 10);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  while (!Serial); // Needed for Leonardo only

  
  Serial.println("Starting.. Setting up.. Radio on.."); // debug message

  radio.begin(); // start radio at CE pin 9, CSN pin 10
  radio.setPALevel(RF24_PA_MAX); // set PA level
  radio.setDataRate(RF24_1MBPS); // set radio data rate
  radio.setChannel(45); // set the channel as 76 decimal
  radio.setPayloadSize(32); // set the payload size as 32 bytes

  const uint64_t pipe = 0xE0E0F1F1E0LL;

  radio.setAutoAck(true); // enable acknowledgement
  radio.enableDynamicPayloads();
  radio.enableAckPayload();

  radio.openWritingPipe(pipe); // open the defined pipe for writing
  radio.printDetails(); // print basic details of radio

 
}

void loop() {
    // put your main code here, to run repeatedly:

    char charMSG[32]; 
    
    String stringMSG = "Hi..Arduino UNO"; // the message to be sent
    while (stringMSG.length() < 32)  {
        stringMSG += 0;
    }

    stringMSG.toCharArray(charMSG, 32);


    time_t t1 = now(); // Store the current time in time variable t
    
   
    radio.write(&charMSG, 32); // Just write message to radio
    Serial.print("Sent the message: ");
    Serial.println(charMSG); // Print a message after a successful send
    radio.startListening();
  
    

    time_t t2 = now();
    
    if (!radio.available())  {
      delay(10);
      if ((second(t2) - second(t1))  > 2) {
        Serial.println("Timed out."); // print error message if radio disconnected or not functioning anymore
      }
    }
    radio.stopListening(); // close radio
    delay(3000);
}
    
