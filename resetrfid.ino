//...This is the code to read UID for rfid card...//
/*If your RFID can't read UID, try these steps:
1. Check if the wires are connected correctly
2. Pull out the RFID and reconnect it
3. And upload this code */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(9600);
  SPI.begin();      // Init SPI bus
  rfid.PCD_Init();  // Init MFRC522

  Serial.println("Place your RFID card/tag near the reader...");
}

void loop() {
  // Check if a new card is present
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Verify if the card can be read
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Print card UID
  Serial.print("Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();
  
  // Halt the RFID to stop the reader after each scan
  rfid.PICC_HaltA();
}
