#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHTPIN 13     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define RX 11 // set rx pin
#define TX 12 // set tx pin
String AP = "GTR_LAB";       // AP NAME
String PASS = "@gtrlab@"; // AP PASSWORD
String API = "WMPVK2XDR9Z3T798";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
String field1 = "field1";
String field2 = "field2";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial esp8266(TX,RX);

void setup() {
  Serial.begin(9600); 
  esp8266.begin(9600);
  sendCommand("AT",5,"OK");  //send AT command 
  sendCommand("AT+CWMODE=3",5,"OK"); // set MODE 1  
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK"); // configure esp8266 to WiFi
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(1000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  String getData = "GET /update?api_key="+ API +"&field1="+String(t)+"&field2="+String(h);
  
  //String getData1 = "GET /update?api_key="+ API +"&"+ field1 +"="+String(t);// set string for send data to thing speak
  sendCommand("AT+CIPMUX=1",5,"OK"); // set to single connection
  sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK"); // to connect to the Thingspeak API using TCP protocol
  sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");// for read data and start sending data
  esp8266.println(getData); // send data to Thingspeak
  //delay(1000);
  countTrueCommand++;
  sendCommand("AT+CIPCLOSE=0",5,"OK");// for end and close transmission
  //delay(10000);
  
  //String getData2 = "GET /update?api_key="+ API +"&"+ field2 +"="+String(h);
  //sendCommand("AT+CIPMUX=1",5,"OK"); // set to single connection
  //sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK"); // to connect to the Thingspeak API using TCP protocol
  //sendCommand("AT+CIPSEND=0," +String(getData2.length()+4),4,">");// for read data and start sending data
  //esp8266.println(getData2);
  //delay(1500);
  //countTrueCommand++;
  //sendCommand("AT+CIPCLOSE=0",5,"OK");// for end and close transmission

//  Serial.print("Humidity: "); 
//  Serial.print(h);
//  Serial.print(" %\t");
//  Serial.print("Temperature: "); 
//  Serial.print(t);
//  Serial.println(" .,*C ");
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("Yes");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  if(found == false)
  {
    Serial.println("Failed");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  found = false;
 }
