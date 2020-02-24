#include <SoftwareSerial.h>
#include <XBee.h>
//sensor SONBEST
//275;             
//A0=310 irrigate, A0=360 stop
SoftwareSerial XBee(2,3);
int data; int data1;
void setup() {
  Serial.begin(9600);
  XBee.begin(9600);
  pinMode(A0,INPUT);
}
void loop() {
  if (XBee.available()>0){
    int id = XBee.read();
    if (id == 202){
      data =(analogRead(A0)-310)/0.5;
      data1 =analogRead(A0);
      if (data <= 0){
        data = 0;
        }
      if (data >= 130){
        data = 130;
        }
        //print out the value you read:
        Serial.println( (String) "Soil sensor " );
        Serial.println(data);
      XBee.write(data);
      }
    }
}
