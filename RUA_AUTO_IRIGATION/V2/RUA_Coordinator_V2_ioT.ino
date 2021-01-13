#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <XBee.h>
#include <Wire.h>

HardwareSerial &XBee = Serial;
//SoftwareSerial XBee (0,1);
SoftwareSerial esp(5,6);//(RX,TX)
// Sensor node data transfer testing 2 parameters
// |Header|Node ID|Humidity|Temp|moisture|Checksum|
//     1      1        4      4      4        2    = 16 byte

typedef struct {
  uint8_t header;
  uint8_t node_id;
  float humidity;
  float temperature;
  float moisture;
  uint16_t checksum;
} data_struct_t;

typedef union {
  data_struct_t data_struct;
  uint8_t data_byte[16];
} packet_t;

//Define LCD
LiquidCrystal_I2C lcd (0x3F, 20, 4);

//define pins of fan and motor
#define motor 11
#define fan 12

//Define mois1 and mois2, mois1 and 2 should more than 50 in order to prevent relay activate in case one node is not available
float hum1 = 0.00;
float hum2 = 0.00;
float temp1= 0.00;
float temp2= 0.00;
float mois1= 50.00;
float mois2= 50.00;
//unsigned long pre_time;
//unsigned long cur_time;

void setup() {
  // put your setup code here, to run once:
  XBee.begin(9600);
  Serial.begin(9600);
  esp.begin(115200);
  lcd.begin();
  lcd.backlight();

  //Set relay pin
  pinMode(motor, OUTPUT);
  pinMode(fan, OUTPUT);

  //Set title
  lcd.setCursor(2,0);
  lcd.print("<<INSTITUTE OF");
  lcd.setCursor(5,1);
  lcd.print("TECHNOLOGY");
  lcd.setCursor(4,2);
  lcd.print("OF CAMBODIA>>>");
  lcd.setCursor(1,3);
  lcd.print("(RUA's GREENHOUSE)");
  delay(3000);
  lcd.clear();
}

void loop() {
  packet_t coord;
  if (XBee.available()>0){
    //Set seperate display
    lcd.setCursor(2,0);
    lcd.print("Node1");
    lcd.setCursor(12,0);
    lcd.print("Node2");
    lcd.setCursor(9,0);
    lcd.print("|");
    lcd.setCursor(9,1);
    lcd.print("|");
    lcd.setCursor(9,2);
    lcd.print("|");
    lcd.setCursor(9,3);
    lcd.print("|"); 
     // Check structure byte of Xbee's Node
    coord.data_byte[0] = XBee.read();
    if (coord.data_struct.header == 0x55){
      Serial.print(coord.data_byte[0], HEX); Serial.print(","); 
      for (int i = 1; i < 16; i++){
        delay(15);
        coord.data_byte[i] = XBee.read();      
        Serial.print(coord.data_byte[i], HEX); Serial.print(","); 
      }
      
    //write data to esp 
      esp.write(coord.data_byte,16); 
                     
    //Print data from Node 1 on LCD
    if (coord.data_struct.node_id == 1)
    {  
      lcd.setCursor(0,1);
      lcd.print("H1:");
      lcd.setCursor(3,1);
      lcd.print(coord.data_struct.humidity ,2);
      lcd.setCursor(0,2);
      lcd.print("T1:");
      lcd.setCursor(3,2);
      lcd.print(coord.data_struct.temperature, 2);
      lcd.setCursor(0,3);
      lcd.print("M1:");
      lcd.setCursor(3,3);
      lcd.print(coord.data_struct.moisture, 2);
      //Store data to new varaibles
      hum1 = coord.data_struct.humidity;
      temp1 = coord.data_struct.temperature;
      mois1 = coord.data_struct.moisture;
    }
    
    //Print data from Node 2 on LCD
    if (coord.data_struct.node_id == 2)
    {   
      lcd.setCursor(11,1);
      lcd.print("H2:");
      lcd.setCursor(14,1);
      lcd.print(coord.data_struct.humidity, 2);
      lcd.setCursor(11,2);
      lcd.print("T2:");
      lcd.setCursor(14,2);
      lcd.print(coord.data_struct.temperature, 2);
      lcd.setCursor(11,3);
      lcd.print("M2:");
      lcd.setCursor(14,3);
      lcd.print(coord.data_struct.moisture, 2);
      //Store data to new varaibles
      hum2 = coord.data_struct.humidity;
      temp2 = coord.data_struct.temperature;
      mois2 = coord.data_struct.moisture;
     }
     
     // Set auto for fan and motors
     if (mois1 <= 31 or mois2 <= 31){
      digitalWrite(motor, HIGH);
     }
     else if( mois1 >= 37 and mois2 >= 37){
      digitalWrite(motor,LOW);
     }
//     if( temp1 >= 35 or temp2 >= 35 ){
//      digitalWrite(fan, HIGH);
//     }
//     else if( temp1 <= 25 and temp2 <= 25){
//      digitalWrite(fan,LOW);
//     }
    Serial.println();
    Serial.print("Temp1: "); Serial.println(temp1);
    Serial.print("Hum1: "); Serial.println(hum1);
    Serial.print("Mois1: "); Serial.println(mois1);
    
    Serial.print("Temp2: "); Serial.println(temp2);
    Serial.print("Hum2: "); Serial.println(hum2);
    Serial.print("Mois2: "); Serial.println(mois2);
  }
  }
}
