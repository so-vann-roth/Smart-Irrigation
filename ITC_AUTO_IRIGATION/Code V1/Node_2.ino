#include <DHT.h>
#include <XBee.h>
#include <SoftwareSerial.h>

//Define XBee 
SoftwareSerial XBee(2,3);

//Define package structure
/* | header | node_id | humidity | temperature | moisture | radiation |
   |   2    |    2    |     4    |      4      |     4    |     4    | */
typedef struct 
{
  uint8_t header;
  uint8_t node_id;
  
  float humidity;
  float temperature;
  float moisture;
  float radiation;

  // uint16_t checksum;
} data_struct_t;

typedef union
{
  data_struct_t data_struct;
  uint8_t data_byte[20];
} packet_t;

//define pin for DHT22 (Humidity and Temperature Sensor)
#define dhtPin A0
#define dhtType DHT22
DHT dht(dhtPin,dhtType);

float hum= 0;
float temp = 0;

//Define pin for 10HS (Soil Moisture Sensor)
#define hsPin A1

float rawHsValue = 0;
float voltageHsValue = 0;
float mois = 0;

//Initialize Radiaton which is not used in this node
float rad = 0;

void setup() {
  XBee.begin(9600);
  dht.begin();
  Serial.begin(9600);
}

void loop() {

  //Read data from DHT22
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  //Read data from 10HS
  rawHsValue = analogRead(hsPin);
  voltageHsValue = map (rawHsValue,0 ,1023, 0, 5000);
  mois = 40.00; //map (voltageHsValue, 300,1250, 0, 57);

  //Collect data into package
  packet_t node;
  node.data_struct.header = 0x55;
  node.data_struct.node_id = 2;
    
  node.data_struct.humidity = hum;
  node.data_struct.temperature = temp;
  node.data_struct.moisture = mois;
  node.data_struct.radiation = rad;

  // node.data_struct.checksum = 0;
  packet_t coord;

  //Sending data though XBee
  for (int i=0; i <= 20; ++i)
  {
    /*Serial.print(node.data_byte[i]);*/
    coord.data_byte[i] = node.data_byte[i];
    XBee.write(coord.data_byte[i]);
  }
  
  //Print datas to serial monitor
  Serial.print("Humidity: ");
  Serial.println(hum);
  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Soil moisture is: ");
  Serial.println(mois);
  
  delay(5000);
}
