#include <SoftwareSerial.h>
SoftwareSerial SerialAT(7,8);
int MyValue1, MyValue2;

void setup() {
 SerialAT.begin(9600);
 Serial.begin(9600);

}

void loop() {

MyValue1 = random(0,50);  
MyValue2 = random(51,100); 

 Connect2Server();       // Establishing connection
Field1(MyValue1);       // Uploading to field 1 of Thingspeak
EndConnection();        // Terminating connection

Connect2Server();
Field2(MyValue2);     // Uploading to field 2 of Thingspeak 
EndConnection(); 

}

void Connect2Server()
{
  SerialAT.println("AT");
  delay(200);
  SerialAT.println("AT+CPIN?");
  delay(200);
  SerialAT.println("AT+CREG?");
  delay(200);
  SerialAT.println("AT+CGATT?");
  delay(200);
  SerialAT.println("AT+CIPSHUT");
  delay(200);
  SerialAT.println("AT+CIPSTATUS");
  delay(1000);
  SerialAT.println("AT+CIPMUX=0");
  delay(1000);
  ShowSerialData();

  SerialAT.println("AT+CSTT=\"internet\"");//start task and setting the APN,
  delay(200);

  ShowSerialData();
   
  SerialAT.println("AT+CIICR");//bring up wireless connection
  delay(2000);

  ShowSerialData();

  SerialAT.println("AT+CIFSR");//get local IP adress
  delay(2000);

  ShowSerialData();

  SerialAT.println("AT+CIPSPRT=0");
  delay(1000);

  ShowSerialData();

  SerialAT.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(2000);

  ShowSerialData();

  SerialAT.println("AT+CIPSEND");//begin send data to remote server
  delay(2000);
  ShowSerialData();
  
}

void Field1(int data) {
  String str = "GET http://api.thingspeak.com/update?api_key=2N8H22RQ1B83BZXT&field1=" + String (data);
  SerialAT.println(str);//begin send data to remote server

  delay(2000);
  ShowSerialData();
  SerialAT.println((char)26);//sending
  delay(4000);//waitting for reply, important! the time is base on the condition of internet
  SerialAT.println();

  ShowSerialData();

}


void Field2(int data) {
  String str = "GET http://api.thingspeak.com/update?api_key=2N8H22RQ1B83BZXT&field2=" + String (data);
  SerialAT.println(str);//begin send data to remote server

  delay(2000);
  ShowSerialData();
  SerialAT.println((char)26);//sending
  delay(4000);//waitting for reply, important! the time is base on the condition of internet
  SerialAT.println();

  ShowSerialData();

}

void EndConnection() {
  SerialAT.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();

}

void ShowSerialData()
{
  while(SerialAT.available()!=0)
    Serial.write(SerialAT.read());
}
