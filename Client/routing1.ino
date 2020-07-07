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

int RXPin = 11;
int TXPin = 10;
double lati, longi;
double jam, menit, detik;
int GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);

char idkapal[3] = {"20"};
char longitude[20] = {"\0"};
char latitude[20] = {"\0"};
char jamc[3] = {"\0"};
char menitc[3] = {"\0"};
char detikc[3] = {"\0"};
char flaga[3] = {"1"};
char flagb[3] = {"0"};

char idkapal2[3] = {"0"};
char longitude2[20] = {"0"};
char latitude2[20] = {"0"};
char jamc2[3] = {"0"};
char menitc2[3] = {"0"};
char detikc2[3] = {"0"};

//status
char sa[3] = {"1"}; //tubrukan
char sb[3] = {"2"}; //kebocoran
char sc[3] = {"3"}; //terbakar
char sd[3] = {"4"}; //kandas
char se[3] = {"0"}; //flag 0

//lora
char data[200] = {"\0"};
uint8_t datasend[200] = {"\0"};

RHReliableDatagram manager(driver, CLIENT_ADDRESS1);

int buttona = 24;
int buttonb = 26;
int buttonc = 28;
int buttond = 32;
int buttone = 34;
int leda = 36;
int ledb = 38;
int ledc = 40;
int ledd = 42;
int lede = 44;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttona, INPUT);
  pinMode(buttonb, INPUT);
  pinMode(buttonc, INPUT);
  pinMode(buttond, INPUT);
  pinMode(buttone, INPUT);
  Serial.begin(9600);

  gpsSerial.begin(GPSBaud);
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
  // put your main code here, to run repeatedly:
 //GPS
  while (gpsSerial.available() > 0){
  if (gps.encode(gpsSerial.read())){
    if (gps.location.isValid())
    {
      lati = gps.location.lat();
//      Serial.print(lati);
//      Serial.print(",");
      longi = gps.location.lng();
//      Serial.println(longi);
    }
    if (gps.time.isValid())
    {
//      jam = gps.time.hour();
//      jam = (gps.time.hour()+7);
        jam = (gps.time.hour()+7)-24;
//      Serial.print(jam);
//      Serial.print(":");
      menit = gps.time.minute();
//      Serial.print(menit);
//      Serial.print(":");
      detik = gps.time.second();
//      Serial.print(menit);
    }
  }
  }
  
  //convert to char
  dtostrf(longi,0,6,longitude);
  dtostrf(lati,0,6,latitude);
  dtostrf(jam,2,0,jamc);
  dtostrf(menit,2,0,menitc);
  dtostrf(detik,2,0,detikc);
  
  //button
  int but1 = digitalRead(buttona);
  int but2 = digitalRead(buttonb);
  int but3 = digitalRead(buttonc);
  int but4 = digitalRead(buttond);
  int but5 = digitalRead(buttone);

  

  if(but1 == HIGH){
    sprintf(data, "%s,%s,%s,%s,%s,%s:%s:%s",flaga,idkapal,latitude,longitude,sa,jamc,menitc,detikc);
    //Serial.println(data);
 //   Serial.println(buttona);
    strcpy((char *)datasend,data);
    manager.sendtoWait(datasend, sizeof(datasend), 255);
    Serial.print("Data terkirim: ");
    Serial.println((char*)datasend);
    uint8_t len = sizeof(buf);
    uint8_t from;
      if (manager.recvfromAck(buf, &len, 10000, &from))
        {
            char datasend2[100] = {"\0"};
            Serial.print("Data diterima: ");
            Serial.println((char*)buf);
        }
        //delay(2000);
    }
  
  else if(but2 == HIGH){
    sprintf(data, "%s,%s,%s,%s,%s,%s:%s:%s",flaga,idkapal,latitude,longitude,sb,jamc,menitc,detikc);
    //Serial.println(data);
  //  Serial.println(buttonb);
    strcpy((char *)datasend,data);
    manager.sendtoWait(datasend, sizeof(datasend), 255);
    Serial.print("Data terkirim: ");
    Serial.println((char*)datasend);
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, 10000, &from))
      {
          char datasend2[100] = {"\0"};
          Serial.print("Data diterima: ");
          Serial.println((char*)buf);
      }
      //delay(2000);
  }
  else if(but3 == HIGH){
    sprintf(data, "%s,%s,%s,%s,%s,%s:%s:%s",flaga,idkapal,latitude,longitude,sc,jamc,menitc,detikc);
   //Serial.println(data);
  //  Serial.println(buttonc);
    strcpy((char *)datasend,data);
    manager.sendtoWait(datasend, sizeof(datasend), 255);
    Serial.print("Data terkirim: ");
    Serial.println((char*)datasend);
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, 10000, &from))
      {
          char datasend2[100] = {"\0"};
          Serial.print("Data diterima: ");
          Serial.println((char*)buf);
      }
      //delay(2000);
  }
  else if(but4 == HIGH){
    sprintf(data, "%s,%s,%s,%s,%s,%s:%s:%s",flaga,idkapal,latitude,longitude,sd,jamc,menitc,detikc);
    //Serial.println(data);
    //Serial.println(buttond);
    strcpy((char *)datasend,data);
    manager.sendtoWait(datasend, sizeof(datasend), 255);
    Serial.print("Data terkirim: ");
    Serial.println((char*)datasend);
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, 10000, &from))
      {
          char datasend2[100] = {"\0"};
          Serial.print("Data diterima: ");
          Serial.println((char*)buf);
      }
      //delay(2000);
  }
  else if(but5 == HIGH){
    sprintf(data, "%s,%s,%s,%s,%s,%s:%s:%s",flagb,idkapal2,latitude2,longitude2,se,jamc2,menitc2,detikc2);
    //Serial.println(data);
   // Serial.println(buttone);
    strcpy((char *)datasend,data);
    manager.sendtoWait(datasend, sizeof(datasend), 255);
    Serial.print("Data terkirim: ");
    Serial.println((char*)datasend);
    uint8_t len = sizeof(buf);
    uint8_t from;
    if (manager.recvfromAck(buf, &len, 10000, &from))
      {
          char datasend2[100] = {"\0"};
          Serial.print("Data diterima: ");
          Serial.println((char*)buf);
      }
      //delay(2000);
  }
//  else if(but1 == LOW || but2 == LOW || but3 == LOW || but4 == LOW || but5 == LOW)
//  {
//    sprintf(data, "%s,%s,%s,%s,%s:%s:%s,%s",idkapal,latitude,longitude,se,jamc,menitc,detikc,flaga);
//    strcpy((char *)datasend,data);
//    manager.sendtoWait(datasend, sizeof(datasend), 255);
//    Serial.print("Data terkirim: ");
//    Serial.println((char*)datasend);
//    uint8_t len = sizeof(buf);
//    uint8_t from;
//    if (manager.recvfromAck(buf, &len, 10000, &from))
//      {
//          char datasend2[100] = {"\0"};
//          Serial.print("Data diterima: ");
//          Serial.println((char*)buf);
//      }
//      delay(60000);
//  }
}
