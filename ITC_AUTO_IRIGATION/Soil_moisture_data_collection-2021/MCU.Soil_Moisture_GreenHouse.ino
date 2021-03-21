#include <SoftwareSerial.h>
#include <ESP8266WiFi.h> //Librarry connecting ESP8266 to connect
WiFiClient client; 
String apiKey = "WAN95HDLEHQZO9O7"; //Write API key of your ThingSpeak channel
const char* server = "api.thingspeak.com"; // API for thingspeak
const char* ssid = "Bunrongproeung"; // Wifi SSID of your Internet connection
const char* pass = "bunrong2877"; // Password
unsigned long pre_time;
unsigned long cur_time;
SoftwareSerial esp(D6,D5); //RX,TX
// Sensor data transfer testing 8 parameters
// |Header|Node ID|moisture1|moisture2|moisture3|moisture4|moisture5|moisture6|moisture7|moisture8|Checksum|
//     1      1        4        4         4         4           4         4         4         4         2    = 36 byte
typedef struct __attribute__((__packed__)) {
  uint8_t header;
  uint8_t node_id;
  float moisture1;
  float moisture2;
  float moisture3;
  float moisture4;
  float moisture5;
  float moisture6;
  float moisture7;
  float moisture8;
//  float moisture9;
//  float moisture10;
  uint16_t checksum;
} data_struct_t;

typedef union {
  data_struct_t data_struct;
  uint8_t data_byte[36];
} packet_t;

float mois1 = 0.0;
float mois2 = 0.0;
float mois3 = 0.0;
float mois4 = 0.0;
float mois5 = 0.0;
float mois6 = 0.0;
float mois7 = 0.0;
float mois8 = 0.0;
//float mois9 = 0.0;
//float mois10 = 0.0;

void setup() {
  esp.begin(115200);
  Serial.begin(9600);
//  delay(1000);
//  Serial.println("Trying to Connect with ");
//  Serial.println(ssid);
  WiFi.begin(ssid, pass); // Connecting ESP8266 with Internet enabled Wifi with above mentioned credentials
  while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.println("connection was unsuccesfull.");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
}
  packet_t coord;
void loop() {     
  if (esp.available()>0){
  coord.data_byte[0] = esp.read();
    if (coord.data_struct.header == 0x55)
    {
       Serial.print(";");
      for (int i=1; i<36; i++)
      {
       coord.data_byte[i] = esp.read();
      }
      for (int i = 0; i <36; i++){
      Serial.print(coord.data_byte[i], HEX); Serial.print(","); 
    }
//  Serial.println(coord.data_struct.node_id);
  if (coord.data_struct.node_id == 1){
  mois1= coord.data_struct.moisture1;
  mois2= coord.data_struct.moisture2;
  mois3= coord.data_struct.moisture3;
  mois4= coord.data_struct.moisture4;
  mois5= coord.data_struct.moisture5;
  mois6= coord.data_struct.moisture6;
  mois7= coord.data_struct.moisture7;
  mois8= coord.data_struct.moisture8;
//  mois9= coord.data_struct.moisture9;
//  mois10= coord.data_struct.moisture10;
      Serial.println();
      Serial.print("Mois1: "); Serial.println(coord.data_struct.moisture1);
      Serial.print("Mois2: "); Serial.println(coord.data_struct.moisture2);
      Serial.print("Mois3: "); Serial.println(coord.data_struct.moisture3);
      Serial.print("Mois4: "); Serial.println(coord.data_struct.moisture4);
      Serial.print("Mois5: "); Serial.println(coord.data_struct.moisture5);
      Serial.print("Mois6: "); Serial.println(coord.data_struct.moisture6);
      Serial.print("Mois7: "); Serial.println(coord.data_struct.moisture7);
      Serial.print("Mois8: "); Serial.println(coord.data_struct.moisture8);
    }
    }
  }
  cur_time = millis();
  if(cur_time - pre_time >=5000){
  if (client.connect(server,80)) // "184.106.153.149" or api.thingspeak.com
  {
  // Format of DATA Packet "Write API Key&field1=Temperature data&field2=Humidity Data"
  String postStr = apiKey;{
  postStr +="&field1=";
  postStr += String(mois1);
  postStr +="&field2=";
  postStr += String(mois2);
  postStr +="&field3=";
  postStr += String(mois3);
  postStr +="&field4=";
  postStr += String(mois4);
  postStr +="&field5=";
  postStr += String(mois5);
  postStr +="&field6=";
  postStr += String(mois6);
  postStr +="&field7=";
  postStr += String(mois7);
  postStr +="&field8=";
  postStr += String(mois8);
  postStr += "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";
  
  client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(postStr.length());
  client.print("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
  client.print(postStr);
  client.flush();        
  client.stop();
  Serial.println("Waiting to initiate next data packet...");
  }
  }
  pre_time = cur_time;
  }
  
}
