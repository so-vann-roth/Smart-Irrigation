#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <XBee.h>
SoftwareSerial XBee(0,1);
// Sensor node data transfer testing 2 parameters
// |Header|Node ID|Humidity|Temp|mois
//     1      1        2      2    2     = 8 byte
typedef struct {
  uint8_t header;
  uint8_t node_id;
  int humidity;
  int temperature;
  int moisture; 
  //uint16_t checksum;
} data_struct_t;

typedef union {
  data_struct_t data_struct;
  uint8_t data_byte[10];
} packet_t;


LiquidCrystal_I2C lcd(0x3f,20,4);
#define motor 5
#define fan 6

void setup() {

  XBee.begin(9600);
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
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
  packet_t coord;
  if (XBee.available()>0){
    coord.data_byte[0] = XBee.read();
    if (coord.data_struct.header == 0x55){
    Serial.print(coord.data_byte[0], HEX); Serial.print(","); 
      for (int i = 1; i < 10; ++i){
        coord.data_byte[i] = XBee.read();
        Serial.print(coord.data_byte[i], HEX); Serial.print(",");
      }
      Serial.println();
      if (coord.data_struct.node_id == 1){
      Serial.print("H1: ");
      Serial.println(coord.data_struct.humidity);
      Serial.print("T1: ");
      Serial.println(coord.data_struct.temperature);
      Serial.print("M1: ");
      Serial.println(coord.data_struct.moisture);
      }
      else if (coord.data_struct.node_id == 2){
      Serial.print("H2: ");
      Serial.println(coord.data_struct.humidity);
      Serial.print("T2: ");
      Serial.println(coord.data_struct.temperature);
      Serial.print("M2: ");
      Serial.println(coord.data_struct.moisture);
      }
      if (coord.data_struct.node_id == 1){
      lcd.setCursor(0,1);
      lcd.print("Hum1:");
      lcd.setCursor(5,1);
      lcd.print(coord.data_struct.humidity);
      lcd.setCursor(7,1);
      lcd.print("%");
      lcd.setCursor(0,2);
      lcd.print("Moi1:");
      lcd.setCursor(5,2);
      lcd.print(coord.data_struct.moisture);
      lcd.setCursor(7,2);
      lcd.print("%");
      lcd.setCursor(0,3);
      lcd.print("Tem1:");
      lcd.setCursor(5,3);
      lcd.print(coord.data_struct.temperature);
      lcd.setCursor(7,3);
      lcd.print("C");
      if (coord.data_struct.moisture < 40&&coord.data_struct.moisture <= 20){
        digitalWrite(motor,1);
      }
      }   
      else if (coord.data_struct.node_id == 2){
      lcd.setCursor(11,1);
      lcd.print("Hum2:");
      lcd.setCursor(16,1);
      lcd.print(coord.data_struct.humidity);
      lcd.setCursor(18,1);
      lcd.print("%");
      lcd.setCursor(11,2);
      lcd.print("Moi2:");
      lcd.setCursor(16,2);
      lcd.print(coord.data_struct.moisture);
      lcd.setCursor(18,2);
      lcd.print("%");  
      lcd.setCursor(11,3);
      lcd.print("Tem2:");
      lcd.setCursor(16,3);
      lcd.print(coord.data_struct.temperature);
      lcd.setCursor(18,3);
      lcd.print("C");  
            if ( coord.data_struct.moisture < 40 && coord.data_struct.moisture <=20){
        digitalWrite(motor,1);
      }
      }
      if(coord.data_struct.moisture>=40&&coord.data_struct.moisture>20){
      digitalWrite(motor,0); 
    }
    if(coord.data_struct.temperature>100||coord.data_struct.moisture>100||coord.data_struct.humidity>100){
      lcd.clear();
    }
   }
  }
 }
