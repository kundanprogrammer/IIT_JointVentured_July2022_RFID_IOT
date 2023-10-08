// RFID: -> Radio-Frequency IDentification 

//RC522 is the highly integrated RFID card reader based on the MFRC522 controller 
// which works on non-contact 13.56mhz communication, is designed by NXP as low power consumption, 
// low cost and compact size read and write chip, is the best choice in the developm
// ent of smart meters and portable hand-held devices.

//      "https://www.arduino.cc/reference/en/libraries/""


#include <SPI.h> //This library allows you to communicate with SPI devices, with the Arduino as the controller device. This library is 
//bundled with every Arduino platform (avr, megaavr, mbed, samd, sam, arc32), so you do not need to install the library separately.
//SERIAL PERIPHERAL INTERFACE
#include<MFRC522.h>//Arduino RFID Library for MFRC522 (SPI)
// Read/Write a RFID Card
#include <Ethernet.h> //Enables network connection (local and Internet) using the Arduino Ethernet Board or Shield.
// With this library you can use the Arduino Ethernet (shield or board) to connect to Internet. The
//  library provides both client and server functionalities. The library permits you to connec
//  t to a local network also with DHCP and to resolve DNS.

#define SS_PIN 10 
#define RST_PIN 9
#define No_Of_Card 3


MFRC522 rfid(SS_PIN,RST_PIN); // Create MFRC522 instance .
MFRC522::MIFARE_Key key; 

byte id[No_Of_Card][4]={
  {142,76,58,42},             //RFID NO-1
  {112,224,72,84},             //RFID NO-2
  {151,94,80,84}              //RFID NO-3
};
byte id_temp[3][3];
byte i;
int j=0;

void setup() {
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();
  for(byte i=0;i<6;i++)
  {
    key.keyByte[i]=0xFF;
  }
}
//------------------------------------------------------------------------------


/* Infinite Loop */
void loop()
{int m=0;
  if(!rfid.PICC_IsNewCardPresent())
  return;
  if(!rfid.PICC_ReadCardSerial())
  return;
  for(i=0;i<4;i++)
  {
   id_temp[0][i]=rfid.uid.uidByte[i]; 
             delay(50);
  }
   for(i=0;i<No_Of_Card;i++)
  {
          if(id[i][0]==id_temp[0][0])
          {
            if(id[i][1]==id_temp[0][1])
            {
              if(id[i][2]==id_temp[0][2])
              {
                if(id[i][3]==id_temp[0][3])
                {
                  Serial.println("Card detected:");
                  for(int s=0;s<4;s++)
                  {
                    Serial.print(rfid.uid.uidByte[s]);
                  }
                   Serial.print(" ");
                  Sending_To_db();
                  j=0;
                            
                            rfid.PICC_HaltA(); rfid.PCD_StopCrypto1();   return; 
                }
              }
            }
          }
   else
   {j++;
    if(j==No_Of_Card)
    {
      Serial.println("Card detected:");
      for(int s=0;s<4;s++)
        {
          Serial.print(rfid.uid.uidByte[s]);
        }
      Serial.print(" ");
      Sending_To_db();
      j=0;
    }
   }
  }
     // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
 }

 void Sending_To_db()  
 {
    if(j!=No_Of_Card)
    {
      Serial.print('1');
      Serial.print(" ");
    }
    else
    {
      Serial.print('0');
      Serial.print(" ");
    }
 }
