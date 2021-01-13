//Node2
#include <XBee.h>
#include <DHT.h>;
//Code for end node to send data to coordinator
#include <SoftwareSerial.h>
SoftwareSerial XBee(2,3);


// Sensor node data transfer testing 4 parameters
// |Header|Node ID|Humidity|Temp|moisture|Checksum|
//     1      1        4      4      4        2    = 20 byte
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

float hum2 = 0.0;
float temp2 = 0.0;

#define DHTPIN 8    // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); 
unsigned long pre_time;
unsigned long cur_time;
//Define pin (Soil Moisture Sensor)
int mois_value = 0;
int output_value = 0;
int output = A0; 

void setup() {
  XBee.begin(9600);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  //Read data from DHT22
  hum2 = dht.readHumidity();
  temp2= dht.readTemperature();
  
  //Read data from moisture
  output_value = analogRead(output);
  mois_value = map(output_value,0,1023,0,50);
//  rawHsValue = analogRead(hsPin);
//  voltageHsValue = map (rawHsValue,0 ,1023, 0, 5000);
//  mois2 = map (voltageHsValue, 300,1250, 0, 57);
   
  packet_t node;  
  node.data_struct.header = 0x55;
  node.data_struct.node_id = 2;
  node.data_struct.humidity = hum2;
  node.data_struct.temperature = temp2;
  node.data_struct.moisture = mois_value;
  node.data_struct.checksum = 0;
  //set time 1mn =60000 for send data to coord once time
  cur_time = millis();
  if(cur_time - pre_time >=60000){    
    packet_t coord;   
    //Sending data through XBee
      for (int i = 0; i < 16; ++i) {
        Serial.print(node.data_byte[i], HEX); Serial.print(",");
        coord.data_byte[i] = node.data_byte[i];
        XBee.write(coord.data_byte[i]);
        }
      Serial.println();
      Serial.print("Temp2: "); Serial.println(coord.data_struct.temperature);
      Serial.print("Hum2: "); Serial.println(coord.data_struct.humidity);
      Serial.print("Mois2: "); Serial.println(coord.data_struct.moisture);
      pre_time = cur_time;
   }
}
