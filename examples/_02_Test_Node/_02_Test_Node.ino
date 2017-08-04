//#define MESH24_DEBUG
//#define MESH24_DEBUG_MESSAGE_STORE
//#define MESH24_DEBUG_ROUTE_MGR
//#define MESH24_DEBUG_SESSION_MGR

#include <AESLib.h>
#include <Mesh24.h>
#include <RF24.h>
#include <SPI.h>

#define NODE_ID 2
#define CHANNEL 65

Mesh24 mesh24(9, 10);
Mesh24Timer sendTimer(1000);

void setup() {
  Serial.begin(57600);
  mesh24.setChannel(CHANNEL);
  mesh24.setAddr(NODE_ID);
  mesh24.begin();
}

void loop() {
  Mesh24Message message;
  if (mesh24.read(message)) {
    Serial.print(millis());
    Serial.print(" rcvd=");
    Mesh24Utils.printAsHex(Serial, message.getBuffer(), MESH24_MESSAGE_SIZE);
    Serial.println();
    unsigned msg;
    message.readPayload(msg);
    Serial.print("   msg=");
    Serial.print(msg);
    Serial.println();
  }
  
  
  if (sendTimer.isDue()) {
    Mesh24Message payload(2, 1, MESH24_MSG_HEARTBEAT);   
    unsigned long msg = 425;
    payload.writePayload(msg);    
    mesh24.write(payload,true);
    Serial.print(millis());
    Serial.print(" payLoad=");
    Mesh24Utils.printAsHex(Serial, payload.getBuffer(), MESH24_MESSAGE_SIZE);
    Serial.println();
    
  }
}
