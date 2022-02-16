#include <SPI.h>
#include <RF24.h>


RF24 radio(9, 10);


void setup() {
  // put your setup code here, to run once:
  while (!Serial);
  
  Serial.begin(9600);
  Serial.println("Starting.. Setting up.. Radio on.."); // debug message

  radio.begin(); // start radio at ce pin 9, csn pin 10
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(45);
  

  const uint64_t pipe = 0xE0E0F1F1E0LL;

  radio.openReadingPipe(1, pipe); // start reading pipe
  radio.enableDynamicPayloads();
  radio.powerUp();
  

}

void loop(void) {
  // put your main code here, to run repeatedly:
  radio.startListening();
  char receivedMessage[32] = {0}; // Set incoming message for 32 bytes
  if (radio.available())  {
    //Serial.println("HELLO!");
    radio.read(receivedMessage, sizeof(receivedMessage));
    Serial.println(receivedMessage);
    // print message on serial monitor
    Serial.println("Turning off the radio.");
    radio.stopListening(); // stop listening to radio
    String stringMessaage(receivedMessage); // change char to string

      delay(1000);
  }

  delay(10);
}
