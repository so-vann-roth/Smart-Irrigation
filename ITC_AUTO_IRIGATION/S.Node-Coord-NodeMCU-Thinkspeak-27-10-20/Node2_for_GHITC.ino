//Code for end node to send data to coordinator
#include <XBee.h>
#include <DHT.h>;
//Code for end node to send data to coordinator
#include <SoftwareSerial.h>
SoftwareSerial XBee(2,3);

#define DHTPIN A0     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); 
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

float hum2 = 0.0;
float temp2 = 0.0;

//Define pin for 10HS (Soil Moisture Sensor)
#define hsPin A1

float rawHsValue = 0;
float voltageHsValue = 0;
float mois2 = 0.0;

//Define Davis6405 (Solar Radiation Sensor)
#define davisPin A2

float rawDavisValue = 0;
float voltageDavisValue = 0;
float rad = 0.0;

void setup() {
  XBee.begin(9600);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  //Read data from DHT22
  hum2 = dht.readHumidity();
  temp2= dht.readTemperature();
  
  //Read data from 10HS
  rawHsValue = analogRead(hsPin);
  voltageHsValue = map (rawHsValue,0 ,1023, 0, 5000);
  mois2 = map (voltageHsValue, 300,1250, 0, 57);

  //Read data from Davis6405
  rawDavisValue = analogRead(davisPin);
  voltageDavisValue = map (rawDavisValue, 0, 1023, 0, 5000);
  rad = map (voltageDavisValue, 0, 3000, 0, 1800); 
   
  packet_t node;  
  node.data_struct.header = 0x55;
  node.data_struct.node_id = 2;
  
  node.data_struct.humidity = hum2;
  node.data_struct.temperature = temp2;
  node.data_struct.moisture = mois2;
  node.data_struct.radiation = rad;
  node.data_struct.checksum = 0;
  
  cur_time = millis();
  if(cur_time - pre_time >=120000){    
    packet_t coord;   
    //Sending data through XBee
      for (int i = 0; i < 20; ++i) {
        Serial.print(node.data_byte[i], HEX); Serial.print(",");
        coord.data_byte[i] = node.data_byte[i];
        XBee.write(coord.data_byte[i]);
        }
      Serial.println();
      Serial.print("Temp2: "); Serial.println(coord.data_struct.temperature);
      Serial.print("Hum2: "); Serial.println(coord.data_struct.humidity);
      Serial.print("Mois2: "); Serial.println(coord.data_struct.moisture);
      Serial.print("Rad: "); Serial.println(coord.data_struct.radiation);
      pre_time = cur_time;
   }
}
