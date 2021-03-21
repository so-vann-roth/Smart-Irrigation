#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial esp(5,6);

unsigned long pre_time;
unsigned long cur_time;

// Sensor data transfer testing 8 parameters
// |Header|Node ID|moisture1|moisture2|moisture3|moisture4|moisture5|moisture6|moisture7|moisture8|Checksum|
//     1      1        4        4         4         4           4         4         4         4         2    = 36 byte
typedef struct {
  uint8_t header;
  uint8_t node_id;
  float moisture1;
  float moisture2;
  float moisture3;
  float moisture4;
  float moisture5;
  float moisture6;
  float moisture7;
  float moisture8;
//  float moisture9;
//  float moisture10;
  uint16_t checksum;
} data_struct_t;

typedef union {
  data_struct_t data_struct;
  uint8_t data_byte[36];
} packet_t;

float rawHsValue1 = 0;
float voltageHsValue1 = 0;
float mois1  ;
float rawHsValue2 = 0;
float voltageHsValue2 = 0;
float mois2 ;
float rawHsValue3 = 0;
float voltageHsValue3 = 0;
float mois3 ;
float rawHsValue4 = 0;
float voltageHsValue4 = 0;
float mois4 ;
float rawHsValue5 = 0;
float voltageHsValue5 = 0;
float mois5 ;
float rawHsValue6 = 0;
float voltageHsValue6 = 0;
float mois6 ;
float rawHsValue7 = 0;
float voltageHsValue7 = 0;
float mois7 ;
float rawHsValue8 = 0;
float voltageHsValue8 = 0;
float mois8 ;
//float rawHsValue9 = 0;
//float voltageHsValue9 = 0;
//float mois9 = 0.0;
//float rawHsValue10 = 0;
//float voltageHsValue10 = 0;
//float mois10 = 0.0;

//Define pin for 10HS (Soil Moisture Sensor)

#define hs1Pin A1
#define hs2Pin A2
#define hs3Pin A3
#define hs4Pin A4
#define hs5Pin A5
#define hs6Pin A6
#define hs7Pin A7
#define hs8Pin A8
//#define hs9Pin A9
//#define hs10Pin A10

void setup() {
  Serial.begin(9600);
  esp.begin(115200);
}
void loop() {
  //Read data from 10HS
  rawHsValue1 = analogRead(hs1Pin);
  voltageHsValue1 = map (rawHsValue1,0 ,1023, 0, 5000);  
    mois1 = map (voltageHsValue1, 300,1250, 0, 57);
  rawHsValue2 = analogRead(hs2Pin);
  voltageHsValue2 = map (rawHsValue2,0 ,1023, 0, 5000);
    mois2 = map (voltageHsValue2, 300,1250, 0, 57);
  rawHsValue3 = analogRead(hs3Pin);
  voltageHsValue3 = map (rawHsValue3,0 ,1023, 0, 5000);
    mois3 = map (voltageHsValue3, 300,1250, 0, 57);
  rawHsValue4 = analogRead(hs4Pin);
  voltageHsValue4 = map (rawHsValue4,0 ,1023, 0, 5000);
    mois4 = map (voltageHsValue4, 300,1250, 0, 57);
  rawHsValue5 = analogRead(hs5Pin);
  voltageHsValue5 = map (rawHsValue5,0 ,1023, 0, 5000);
    mois5 = map (voltageHsValue5, 300,1250, 0, 57); 
  rawHsValue6 = analogRead(hs6Pin);
  voltageHsValue6 = map (rawHsValue6,0 ,1023, 0, 5000);   
    mois6 = map (voltageHsValue6, 300,1250, 0, 57);
  rawHsValue7 = analogRead(hs7Pin);
  voltageHsValue7 = map (rawHsValue7,0 ,1023, 0, 5000);
    mois7 = map (voltageHsValue7, 300,1250, 0, 57);
  rawHsValue8 = analogRead(hs8Pin);
  voltageHsValue8 = map (rawHsValue8,0 ,1023, 0, 5000);
    mois8 = map (voltageHsValue8, 300,1250, 0, 57);
//  rawHsValue9 = analogRead(hs9Pin);
//  voltageHsValue9 = map (rawHsValue9,0 ,1023, 0, 5000);
//    mois9 = map (voltageHsValue9, 300,1250, 0, 57);
//  rawHsValue10 = analogRead(hs10Pin);
//  voltageHsValue10 = map (rawHsValue10,0 ,1023, 0, 5000);
//    mois10 = map (voltageHsValue10, 300,1250, 0, 57);

  packet_t node;
  node.data_struct.header = 0x55;
  node.data_struct.node_id = 1;
  node.data_struct.moisture1 = mois1;
  node.data_struct.moisture2 = mois2;
  node.data_struct.moisture3 = mois3;
  node.data_struct.moisture4 = mois4;
  node.data_struct.moisture5 = mois5;
  node.data_struct.moisture6 = mois6;
  node.data_struct.moisture7 = mois7;
  node.data_struct.moisture8 = mois8;
//  node.data_struct.moisture9 = mois9;
//  node.data_struct.moisture10 = mois10;
  node.data_struct.checksum = 0;

  cur_time = millis();
  if(cur_time - pre_time >=5000){ 
    packet_t coord;
      //Sending data through NodeMCU
      for (int i=0; i < 36; ++i) {
        Serial.print(node.data_byte[i], HEX); Serial.print(",");
        coord.data_byte[i]= node.data_byte[i];
      }    
      esp.write(coord.data_byte,36);
      Serial.println();
      Serial.print("Mois1: "); Serial.println(node.data_struct.moisture1);
      Serial.print("Mois2: "); Serial.println(node.data_struct.moisture2);
      Serial.print("Mois3: "); Serial.println(node.data_struct.moisture3);
      Serial.print("Mois4: "); Serial.println(node.data_struct.moisture4);
      Serial.print("Mois5: "); Serial.println(node.data_struct.moisture5);
      Serial.print("Mois6: "); Serial.println(node.data_struct.moisture6);
      Serial.print("Mois7: "); Serial.println(node.data_struct.moisture7);
      Serial.print("Mois8: "); Serial.println(node.data_struct.moisture8);
//      Serial.print("Mois9: "); Serial.println(node.data_struct.moisture8);
//      Serial.print("Mois10: "); Serial.println(node.data_struct.moisture10);
      pre_time = cur_time;
}
}
