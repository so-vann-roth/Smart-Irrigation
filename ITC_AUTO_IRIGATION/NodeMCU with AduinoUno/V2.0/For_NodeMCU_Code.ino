#include <SoftwareSerial.h>
SoftwareSerial esp(D6,D5); //RX,TX

int mois1 ;
int mois2 ;
int hum1 ;
int hum2 ;
int temp1 ;
int temp2 ;
int r;
//String data;
void setup() {
  // put your setup code here, to run once:
esp.begin(115200);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  esp.write('s');
  if (esp.available()>0){
    char str = esp.read();
    if (str=='M'){
    mois1 = esp.read();
    }
    if(str =='m'){
      mois2 = esp.read();
    }
    if (str=='H'){
    hum1 = esp.read();
    }
    if(str =='h'){
      hum2 = esp.read();
    }
    if (str=='T'){
    temp1 = esp.read();
    }
    if(str =='t'){
      temp2 = esp.read();
    }
    if(str == 'r'){
      r = esp.read();
    }
    
    Serial.println(String("Hum1=")+String(hum1));
    Serial.println(String("Hum2=")+String(hum2));
    Serial.println(String("Mois1=")+String(mois1));
    Serial.println(String("Mois2=")+String(mois2));
    Serial.println(String("Temp1=")+String(temp1));
    Serial.println(String("Temp2=")+String(temp2));
    Serial.println(String("Rad=")+String(r*10));\
    delay(1000);
    
  }
}
