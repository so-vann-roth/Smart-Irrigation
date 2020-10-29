#include <SoftwareSerial.h>
#include <ESP8266WiFi.h> //Librarry connecting ESP8266 to connect
WiFiClient client; 
String apiKey = "88OOFGWCTW33Q0I6"; //Write API key of your ThingSpeak channel
const char* server = "api.thingspeak.com"; // API for thingspeak
const char* ssid = "GTR_LAB"; // Wifi SSID of your Internet connection
const char* pass = "@gtrlab@"; // Password
unsigned long pre_time;
unsigned long cur_time;
SoftwareSerial esp(D6,D5); //RX,TX
// Sensor node data transfer testing 2 parameters
// |Header|Node ID|Humidity|Temp|moisture|radiation|Checksum|
//     1      1        4      4      4        4         2    = 20 byte

typedef struct __attribute__((__packed__)) {
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
float hum2 = 0.0;
float temp2 = 0.0;
float mois1 = 0.0;
float mois2 = 0.0;
float rad = 0.0;

packet_t coord;

void setup() {
  esp.begin(115200);
  Serial.begin(9600);
//  delay(1000);
  Serial.println("Trying to Connect with ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass); // Connecting ESP8266 with Internet enabled Wifi with above mentioned credentials
  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print("connection was unsuccesfull.");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
}

void loop() {     
  if (esp.available()>0){
  coord.data_byte[0] = esp.read();
    if (coord.data_struct.header == 0x55)
    {
 //      Serial.print(";");
      for (int i=1; i<20; i++)
      {
       coord.data_byte[i] = esp.read();
      }
      for (int i = 0; i < 20; i++){
      Serial.print(coord.data_byte[i], HEX); Serial.print(","); 
    }
//    Serial.println();
    Serial.println(coord.data_struct.node_id);
    if (coord.data_struct.node_id == 1){    
      hum1 = coord.data_struct.humidity;
      temp1 = coord.data_struct.temperature;
      mois1= coord.data_struct.moisture;
    }
    if (coord.data_struct.node_id == 2)
    {   
      hum2 = coord.data_struct.humidity;
      temp2 = coord.data_struct.temperature;
      mois2 = coord.data_struct.moisture;
      rad = coord.data_struct.radiation; 
    }   
//      Serial.println("node1");  
//      Serial.print("Temp1: "); Serial.println(temp1);
//      Serial.print("Hum1: "); Serial.println(hum1);
//      Serial.print("Mois1: "); Serial.println(mois1);
//      Serial.println("node2"); 
//      Serial.print("Temp2: "); Serial.println(temp2);
//      Serial.print("Hum2: "); Serial.println(hum2);
//      Serial.print("Mois2: "); Serial.println(mois2);
//      Serial.print("Rad: "); Serial.println(rad);       
    }
     cur_time = millis();
  if(cur_time - pre_time >=120000){
  if (client.connect(server,80)) // "184.106.153.149" or api.thingspeak.com
  {
  // Format of DATA Packet "Write API Key&field1=Temperature data&field2=Humidity Data"
  String postStr = apiKey;{
  //node1
  postStr +="&field1=";
  postStr += String(temp1);
  postStr +="&field2=";
  postStr += String(hum1);
  postStr +="&field3=";
  postStr += String(mois1);
  
  //node2
  postStr +="&field4=";
  postStr += String(temp2);
  postStr +="&field5=";
  postStr += String(hum2);
  postStr +="&field6=";
  postStr += String(mois2);
  postStr +="&field7=";
  postStr += String(rad); 
  postStr += "\r\n\r\n\r\n\r\n\r\n\r\n\r\n";
  
  client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(postStr.length());
  client.print("\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
  client.print(postStr);
  client.flush();
//  Serial.println(postStr);
//  delay(10000);        
  client.stop();
//  Serial.println("Waiting to initiate next data packet...");
//  delay(10000);
  }
  }
  pre_time = cur_time;
  }
  }
}
