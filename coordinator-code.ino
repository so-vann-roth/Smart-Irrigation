#include <SoftwareSerial.h>
#include <XBee.h>
SoftwareSerial XBee(0,1);
// Sensor node data transfer testing 2 parameters
// |Header|Node ID|Humidity|Temp|Checksum|
//     1      1        4      4     2     = 12 byte
typedef struct {
  uint8_t header;
  uint8_t node_id;
  float humidity;
  float temperature;
  uint16_t checksum;
} data_struct_t;

typedef union {
  data_struct_t data_struct;
  uint8_t data_byte[12];
} packet_t;

void setup() {
  // put your setup code here, to run once:
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop() {
  packet_t coord;
  if (XBee.available()>0){
    coord.data_byte[0] = XBee.read();
    if (coord.data_struct.header == 0x55){
    Serial.print(coord.data_byte[0], HEX); Serial.print(","); 
      for (int i = 1; i < 12; ++i)
      {
        coord.data_byte[i] = XBee.read();
       
        Serial.print(coord.data_byte[i], HEX); Serial.print(","); 
      } 
      Serial.println();
      Serial.print("Temp: "); Serial.println(coord.data_struct.temperature);
    }
  }
}
