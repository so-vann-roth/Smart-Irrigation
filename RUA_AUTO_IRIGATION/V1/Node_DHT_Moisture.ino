#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <XBee.h>
//Code for end node to send data to coordinator
#include <SoftwareSerial.h>

SoftwareSerial XBee(2,3);
// Sensor node data transfer testing 2 parameters
// |Header|Node ID|Humidity|Temp|Checksum|
//     1      1        4      4     2     = 12 byte
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

#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
int mois_value = 0;
int output_value = 0;
int output = A0; 
void setup() {
  // put your setup code here, to run once:
  XBee.begin(9600);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
 
  output_value = analogRead(output);
  mois_value = map(output_value,0,830,0,100);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
 
  packet_t node;
  node.data_struct.header = 0x55;
  node.data_struct.node_id = 1;
  node.data_struct.humidity = h;
  node.data_struct.temperature =t;
  node.data_struct.moisture =40;// mois_value;
packet_t coord;

  for (int i = 0; i < 10; ++i)
  {
    Serial.print(node.data_byte[i], HEX); Serial.print(",");
    coord.data_byte[i] = node.data_byte[i];
    XBee.write(coord.data_byte[i]);
  }
  Serial.println();
  Serial.print("Temperature: "); 
  Serial.println(coord.data_struct.temperature);
  Serial.print("Humidity: "); 
  Serial.println(coord.data_struct.humidity);
  Serial.print("Moisture: "); 
  Serial.println(coord.data_struct.moisture);
  delay(23000);
}
