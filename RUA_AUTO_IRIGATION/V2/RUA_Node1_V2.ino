//node1
#include <DHT.h>
#include <XBee.h>
#include <SoftwareSerial.h>

//Define XBee 
SoftwareSerial XBee(2,3);

//define pin for DHT22 (Humidity and Temperature Sensor)
#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//unsigned pre_time and cur_time for set millis function
unsigned long pre_time;
unsigned long cur_time;

// Sensor node data transfer testing 4 parameters
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

float hum1 = 0.0;
float temp1 = 0.0;


//Define pin for 10HS (Soil Moisture Sensor)


int mois_value = 0;
int output_value = 0;
#define output A0

void setup() {
  XBee.begin(9600);
  Serial.begin(9600);
  //initiallize DHT22
  dht.begin();
}

void loop() {
  //Read data from DHT22
  hum1 = dht.readHumidity();
  temp1 = dht.readTemperature();

  output_value = analogRead(output);
  mois_value = map(output_value,0,1023,0,50);
  
  packet_t node;
  node.data_struct.header = 0x55;
  node.data_struct.node_id = 1;
    
  node.data_struct.humidity = hum1;
  node.data_struct.temperature = temp1;
  node.data_struct.moisture =  mois_value;
  node.data_struct.checksum = 0;
  //2min = 2 * 60 * 1000 = 120000
  cur_time = millis();
  if(cur_time - pre_time >=120500){ 
    packet_t coord;
      //Sending data though XBee
      for (int i=0; i < 16; ++i) {
        Serial.print(node.data_byte[i], HEX); Serial.print(",");
        coord.data_byte[i] = node.data_byte[i];
        XBee.write(coord.data_byte[i]);
        }    
      Serial.println();
      Serial.print("Temp1: "); Serial.println(coord.data_struct.temperature);
      Serial.print("Hum1: "); Serial.println(coord.data_struct.humidity);
      Serial.print("Mois1: "); Serial.println(coord.data_struct.moisture);
      pre_time = cur_time;
   }
}
