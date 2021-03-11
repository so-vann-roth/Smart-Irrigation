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

} data_struct_t;

typedef union
{
  data_struct_t data_struct;
  uint8_t data_byte[20];
} packet_t;

void setup() {
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop() {
  //Collect data into package
  packet_t node;
  node.data_struct.header = 0x55;
  node.data_struct.node_id = 1;
    
  node.data_struct.humidity = 10;
  node.data_struct.temperature = 20;
  node.data_struct.moisture = 65;
  node.data_struct.radiation = 100;

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
  Serial.println("Data has been sent sucessfully.");
  Serial.print("Humidity: ");
  Serial.println(node.data_struct.humidity);
  Serial.print("Temperature: ");
  Serial.println(node.data_struct.temperature);

  delay(1000);
}
