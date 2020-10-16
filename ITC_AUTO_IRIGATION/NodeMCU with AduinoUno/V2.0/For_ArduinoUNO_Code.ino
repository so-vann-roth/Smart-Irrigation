#include <SoftwareSerial.h>
SoftwareSerial esp(5,6);

int mois1 = 85.54 ;
int mois2 = 86.76 ;
int hum1 = 66.76 ;
int hum2 = 65.45 ;
int temp1 = 29.75 ;
int temp2 = 30.12 ;
float r = 730.67 ;
int rad = r;
void setup() {
  esp.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
int data = 60;
  if(esp.available()>0){
    char str = esp.read();
    if(str == 's'){
      esp.write('M');
      esp.write(mois1);
      delay(1000);
      esp.write('m');
      esp.write(mois2);
      delay(1000);
      esp.write('H');
      esp.write(hum1);
      delay(1000);
      esp.write('h');
      esp.write(hum2);
      delay(1000);
      esp.write('T');
      esp.write(temp1);
      delay(1000);
      esp.write('t');
      esp.write(temp2);
      delay(1000);
      esp.write('r');
      esp.write(rad/10);
      delay(1000);
    }
    }
  }
