#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <RHReliableDatagram.h>

#define CLIENT_ADDRESS1 20
#define CLIENT_ADDRESS2 30
#define SERVER_ADDRESS1 40
#define SERVER_ADDRESS2 50

RH_RF95 driver;
float frequency = 915.0;

//lora
//char data[200] = {"\0"};
//uint8_t datasend[200] = {"\0"};

RHReliableDatagram manager(driver, CLIENT_ADDRESS2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  while (!Serial) ; 
  if (!manager.init()){
    Serial.println("init failed");
  }
  
  driver.setFrequency(frequency);
  driver.setTxPower(23);
  driver.setSpreadingFactor(7);
  driver.setSignalBandwidth(31200);
}

uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
void loop() {
  if (manager.available())
  {
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, 10000, 20))
      {
        char datasend[200] = {"\0"};
        Serial.print("Data diterima: ");
        Serial.println((char*)buf);
        strcpy(datasend,(char*)buf);
        manager.sendtoWait(datasend, sizeof(datasend), 40);
        Serial.print("Data terkirim: ");
        Serial.println((char*)datasend);
      }
  }
}
