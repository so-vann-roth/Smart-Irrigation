#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <XBee.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#define RX 11 // set rx pin
#define TX 12 // set tx pin
String AP = "GTR_LAB";     // AP NAME
String PASS = "@gtrlab@"; // AP PASSWORD
String API = "88OOFGWCTW33Q0I6";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";

String field1 = "field1";
String field2 = "field2";
String field3 = "field3";
String field4 = "field4";
String field5 = "field5";
String field6 = "field6";
String field7 = "field7";

float temp1 = 0;
float hum1 = 0;
float temp2 = 0;
float hum2 = 0;
float rad1 = 0;

int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
SoftwareSerial esp8266(TX,RX);

//Define XBee
HardwareSerial &XBee = Serial;

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

void sendCommand(String command, int maxTime, char readReplay[]) {
  //Serial.print(countTrueCommand);
  //Serial.print(". at command => ");
  //Serial.print(command);
  //Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    //Serial.println("Yes");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  if(found == false)
  {
    //Serial.println("Failed");
    countTimeCommand = 0;
    countTrueCommand++;
  }
  //countTimeCommand = 0;
  found = false;
 }

void setup() {
  XBee.begin(9600);
  esp8266.begin(9600);
  sendCommand("AT",5,"OK");  //send AT command 
  sendCommand("AT+CWMODE=3",5,"OK"); // set MODE 1  
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK"); // configure esp8266 to WiFi
  
  lcd.begin();
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
      //Serial.print(coord.data_byte[0], HEX);
      //Serial.print(";");
      for (int i = 1; i <= 20; i++)
      {
        coord.data_byte[i] = XBee.read();
        //Serial.print(coord.data_byte[i], HEX);
        //Serial.print(";");
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
      
      hum1 = coord.data_struct.humidity;
      temp1 = coord.data_struct.temperature;
      mois1 = coord.data_struct.moisture;
      
      String getData = "GET /update?api_key="+ API +"&field1="+String(temp1)+"&field2="+String(hum1)+"&field3="+String(mois1);
      sendCommand("AT+CIPMUX=1",5,"OK"); // set to single connection
      sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK"); // to connect to the Thingspeak API using TCP protocol
      sendCommand("AT+CIPSEND=0," + String(getData.length()+4),4,">");// for read data and start sending data
      esp8266.println(getData); // send data to Thingspeak
      //delay(1000);
      countTrueCommand++;
      sendCommand("AT+CIPCLOSE=0",5,"OK");// for end and close transmission
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
      
      hum2 = coord.data_struct.humidity;
      temp2 = coord.data_struct.temperature;
      mois2 = coord.data_struct.moisture;  
      rad1 = coord.data_struct.radiation; 

      String getData = "GET /update?api_key="+ API +"&field4="+String(temp2)+"&field5="+String(hum2)+"&field6="+String(mois2)+"&field7="+String(rad1);
      sendCommand("AT+CIPMUX=1",5,"OK"); // set to single connection
      sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK"); // to connect to the Thingspeak API using TCP protocol
      sendCommand("AT+CIPSEND=0," + String(getData.length()+4),4,">");// for read data and start sending data
      esp8266.println(getData); // send data to Thingspeak
      //delay(1000);
      countTrueCommand++;
      sendCommand("AT+CIPCLOSE=0",5,"OK");// for end and close transmission     
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
    
    //Serial.println("Mois1 is: ");
    //Serial.print(mois1);
    //Serial.println("Mois2 is: ");
    //Serial.print(mois2);
       
  }
}
