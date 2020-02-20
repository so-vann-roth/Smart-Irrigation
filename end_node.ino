#include <SoftwareSerial.h>
#include <XBee.h>
SoftwareSerial XBee(2,3);
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
  // put your main code here, to run repeatedly:
packet_t node;
  node.data_struct.header = 0x55;
  node.data_struct.node_id = 1;
  node.data_struct.humidity = analogRead(A0);
  node.data_struct.temperature = 25.45;
  node.data_struct.checksum = 0;

packet_t coord;
  for (int i = 0; i < 12; ++i)
  {
    Serial.print(node.data_byte[i], HEX); Serial.print(",");
    coord.data_byte[i] = node.data_byte[i];
    XBee.write(coord.data_byte[i]);
  }
  Serial.println();

  Serial.print("Temp: "); Serial.println(coord.data_struct.temperature);
  delay(1000);
}
