//node1
#include <DHT.h>
#include <XBee.h>
#include <SoftwareSerial.h>

//Define XBee 
SoftwareSerial XBee(2,3);

//define pin for DHT22 (Humidity and Temperature Sensor)
#define dhtPin A0
#define dhtType DHT22
DHT dht(dhtPin,dhtType);
unsigned long pre_time;
unsigned long cur_time;
// Sensor node data transfer testing 4 parameters
// |Header|Node ID|Humidity|Temp|moisture|radiation|Checksum|
//     1      1        4      4      4        4         2    = 20 byte
typedef struct {
  uint8_t header;
  uint8_t node_id;
  float humidity;
  float temperature;
  float moisture;
  float radiation;
  uint16_t checksum;
} data_struct_t;

typedef union {
  data_struct_t data_struct;
  uint8_t data_byte[20];
} packet_t;

float hum1 = 0.0;
float temp1 = 0.0;

//Define pin for 10HS (Soil Moisture Sensor)
#define hsPin A1

float rawHsValue = 0;
float voltageHsValue = 0;
float mois1 = 0.0;

//Initialize Radiaton which is not used in this node
float rad = 0.0;

void setup() {
  XBee.begin(9600);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  //Read data from DHT22
  hum1 = dht.readHumidity();
  temp1 = dht.readTemperature();

  //Read data from 10HS
  rawHsValue = analogRead(hsPin);
  voltageHsValue = map (rawHsValue,0 ,1023, 0, 5000);
  mois1 = map (voltageHsValue, 300,1250, 0, 57);

  //Collect data into package
  packet_t node;
  node.data_struct.header = 0x55;
  node.data_struct.node_id = 1;
    
  node.data_struct.humidity = hum1;
  node.data_struct.temperature = temp1;
  node.data_struct.moisture = mois1;
  node.data_struct.radiation = rad;
  node.data_struct.checksum = 0;
  
  cur_time = millis();
  if(cur_time - pre_time >=120000){ 
    packet_t coord;
      //Sending data though XBee
      for (int i=0; i < 20; ++i) {
//        Serial.print(node.data_byte[i], HEX); Serial.print(",");
        coord.data_byte[i] = node.data_byte[i];
        XBee.write(coord.data_byte[i]);
        }    
//      Serial.println();
//      Serial.print("Temp1: "); Serial.println(coord.data_struct.temperature);
//      Serial.print("Hum1: "); Serial.println(coord.data_struct.humidity);
//      Serial.print("Mois1: "); Serial.println(coord.data_struct.moisture);
      pre_time = cur_time;
   }
}
