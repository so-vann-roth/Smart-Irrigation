#include <SoftwareSerial.h>
#include <XBee.h>

//Define XBee
SoftwareSerial XBee(2,3);

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

//Define mois1 and mois2, mois1 and 2 should more than 50 in order to prevent relay activate in case one node is not available
float mois1 = 50;
float mois2 = 50;

void setup() {
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop() {
  //Check if XBee available
  packet_t coord;
  if (XBee.available() > 0)
  {   
    coord.data_byte[0] = XBee.read();
    if (coord.data_struct.header == 0x55)
    {
      for (int i = 1; i <= 20; i++)
      {
        coord.data_byte[i] = XBee.read();
      }
    }
    
    //Print data from Node 1 on Serial monitor
    if (coord.data_struct.node_id == 1)
    {
    Serial.println("Data has been recieved sucessfully.");  
    Serial.print("Humidity: ");
    Serial.println(coord.data_struct.humidity);
    Serial.print("Temperature: ");
    Serial.println(coord.data_struct.temperature);
    }
  }

  delay(2000);
}
