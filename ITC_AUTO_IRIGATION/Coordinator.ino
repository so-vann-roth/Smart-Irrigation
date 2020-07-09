#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <XBee.h>

//Define XBee
SoftwareSerial XBee(0,1);

//Define package structure
/* | header | node_id | humidity | temperature | moisture | rdiation |
   |   2    |    2    |     4    |      4      |     4    |     4    | */
   
typedef struct 
{
  uint8_t header;
  uint8_t node_id;
  
  float humidity;
  float temperature;
  float moisture;
  float radiation;
} data_struct_t;

typedef union
{
  data_struct_t data_struct;
  uint8_t data_byte[20];
} packet_t;

//Define LCD
LiquidCrystal_I2C lcd (0x3F, 20, 4);

//Define relay pin
#define relayPin 5

//Define mois1 and mois2, mois1 and 2 should more than 50 in order to prevent relay activate in case one node is not available
float mois1 = 50;
float mois2 = 50;

void setup() {
  XBee.begin(9600);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  //Set relay pin
  pinMode(relayPin, OUTPUT);

  //Set title
  lcd.setCursor(4,1);
  lcd.print("NEVER GIVE UP");
  delay(1000);
  lcd.clear();

}

void loop() {
  //Check if XBee available
  packet_t coord;
  if (XBee.available() > 0)
  {
    //Set seperate display
    lcd.setCursor(9,0);
    lcd.print("|");
    lcd.setCursor(9,1);
    lcd.print("|");
    lcd.setCursor(9,2);
    lcd.print("|");
    lcd.setCursor(9,3);
    lcd.print("|");
    
    coord.data_byte[0] = XBee.read();
    if (coord.data_struct.header == 0x55)
    {
      Serial.print(coord.data_byte[0], HEX);
      Serial.print(";");
      for (int i = 1; i <= 20; i++)
      {
        coord.data_byte[i] = XBee.read();
        Serial.print(coord.data_byte[i], HEX);
        Serial.print(";");
      }
    }
    
    //Print data from Node 1 on LCD
    if (coord.data_struct.node_id == 1)
    {  
      lcd.setCursor(0,0);
      lcd.print("H1:");
      lcd.setCursor(3,0);
      lcd.print(coord.data_struct.humidity ,2);
      lcd.setCursor(0,1);
      lcd.print("T1:");
      lcd.setCursor(3,1);
      lcd.print(coord.data_struct.temperature, 2);
      lcd.setCursor(0,2);
      lcd.print("M1:");
      lcd.setCursor(3,2);
      lcd.print(coord.data_struct.moisture, 2);

      mois1 = coord.data_struct.moisture;
    }
    
    //Print data from Node 2 on LCD
    if (coord.data_struct.node_id == 2)
    {   
      lcd.setCursor(11,0);
      lcd.print("H2:");
      lcd.setCursor(14,0);
      lcd.print(coord.data_struct.humidity, 2);
      lcd.setCursor(11,1);
      lcd.print("T2:");
      lcd.setCursor(14,1);
      lcd.print(coord.data_struct.temperature, 2);
      lcd.setCursor(11,2);
      lcd.print("M2:");
      lcd.setCursor(14,2);
      lcd.print(coord.data_struct.moisture, 2);
      lcd.setCursor(11,3);
      lcd.print("R1:");
      lcd.setCursor(14,3);
      lcd.print(coord.data_struct.radiation, 1);

      mois2 = coord.data_struct.moisture;
    }

    //Define when to start the Valve
    if (mois1 <= 32.00 or mois2 <= 32.00)
    {
      digitalWrite(relayPin, HIGH);
    }
    
    //Define when to stop the Valve
    if (mois1 >= 34.00 and mois2 >= 34.00)
    {
      digitalWrite(relayPin, LOW);
    }

    /*
    Serial.println("Mois1 is: ");
    Serial.print(mois1);

    Serial.println("Mois2 is: ");
    Serial.print(mois2);
    */
  }
}
