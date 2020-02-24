#include <SoftwareSerial.h>
#include <XBee.h>
#include <SPI.h>
#include <SD.h>

File myFile;
SoftwareSerial XBee(2,3);//rx tx
int p = 0;//loop for data transfer
int id = 2;//id of node
int d;//for detect
int data[] = {0,0,0};//for save
int n = 1;//interation for data[]

int data1_node1=0;int data1_node2=0;
int val;//additional for identify the id
int ti;//condition for error
int q;//water controller
void setup() {
  pinMode(6,OUTPUT);
  Serial.begin(9600); 
  XBee.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}
void loop() {
  p++;
  //The saving condition when all communication with all nodes are done
      if (id == 4){
        if (!SD.begin(4)) {
          //Serial.println("initialization failed!");
          goto somepoint;//if fail to find SD card skip write text then go to "somepoint"
          while (1);
        }
        myFile = SD.open("test.txt", FILE_WRITE);//create or open file test.txt
          if (myFile) {
            myFile.print("          soil (node_1):");//write text to file (code is similar to Serial print)
            delay(500);// set a delay time between two writing text
            myFile.print(data1_node1);
            delay(500);
            myFile.print("          soil (node_2):");
            delay(500);
            myFile.println(data1_node2);
            myFile.close();// close file
            //Serial.println("done");
          }
      somepoint://"somepoint" point for the skip SD write
      id = 2;
      delay(1000);
      //delay(299850); DELAY 5 MIN//time for run full cod is 2150ns
      }
  //The request data from node condition
      if (p == 5){
        val = 200 + id;
        XBee.write(val);//Send request
        
        //Wait for replycondition
        for (int i =0; i <5000;i++){
          if (XBee.available()>0){
            d = XBee.read();
            data[1] = d;
            Serial.println("received data");
            d = 0;
            }
          }
         Serial.println(id);
         if (id == 2){
          data1_node1 = data[1];
          Serial.print("data :");Serial.println(data1_node1);
          data[1] = data1_node2;
          }
         if (id == 3){
          data1_node2 = data[1];
          Serial.print("data :");Serial.println(data1_node2);
          data[1] = data1_node1;
          }
         Serial.println("...............");
         id++;

      //Watering condition
      if (data1_node1 == 0 || data1_node2 == 0){
        q = 1;//watering
        }
      if (data1_node1 >= 100 || data1_node2 >= 100){
        q = 2;
        }
      if ((data1_node1 == 0 && data1_node2 >= 100) ||(data1_node1 >= 100 && data1_node2 == 0)){
        q = 3;
        }
      if ((data1_node1 <= 100 && data1_node1 > 0) && (data1_node2 <= 100 && data1_node2 > 0)){
        q = 4;
      }
      //Watering control
      if (q == 1){
        digitalWrite(6,LOW);
        ti++;
        if (ti == 1000){ //time of relay connected
          digitalWrite(6,HIGH);
          delay(900000);//delay when error
          ti = 0;
          }
        }
      if (q == 2 || q==3 || q==4){
        digitalWrite(6,HIGH);
        ti = 0;
        }
      p = 0;
      }
  delay(1000);
}
