
//Add Library
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//Explicit ประกาศตัวแปร
int myOutput = D2;
int myOutput2 = D8;
int myDelay = 1000;//ค่าของเวลาจะมีหน่วยเป็น มิลลิวินาที
//int intIndex = 0;
int intSwitch = 0;
int intSwitch2 = 0;

//การกำหนดค่าคงที
#define wifiSSID "Kik"    //String wifiSSID="";
#define wifiPassword "12345678"
//-------------------------------------------------
//การทำงานบนfirebase
#define firebaseHost "fir-4950a.firebaseio.com"//"supawadeenodemcu.firebaseio.com"
#define firebaseKey "udAL17fOlK9jFO1lLyqd4ylv5gf8s4B1VbqunqGp"
//-------------------------------------------------





void setup() {

  //  ส่วนที่กำหนดการส่งสัญญาณ digital Out จากขาของ Node
  pinMode(myOutput, OUTPUT);
  pinMode(myOutput2, OUTPUT);
  
//  การกำหนดช่องทางในการ monitor
  Serial.begin(9600);
//-------------------------------------------------
//  การกำหนดข้อมูลเกี่ยวกับการเชื่อมต่อ wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiSSID, wifiPassword);
  Serial.println("Start Find WiFi");  

  while(WiFi.status() != WL_CONNECTED) 
  {
    //ถ้า Condition Ture จะทำงานที่นี้
    Serial.print("=");
    delay(1000);
    
    }

//    ถ้ามาทำงานตรงนี้คือ Connected WiFi ได้แล้ว
  Serial.println();
  Serial.println("Success Connected WiFi");
  Serial.println(WiFi.localIP());

//------------------------------------------------------
//  ส่วนของการเชื่อมต่อ Firebase 

  Firebase.begin(firebaseHost, firebaseKey);

}//setup

void loop() {

  
//  Serial.println("Hello Supawadee");
//  delay(2000);

//Check Connected Firebase
  //Firebase.setInt("led", intIndex);
  
  if (Firebase.failed()) {

    //    เมื่อไรก็ตามที่ไม่สามารถเข้า Firebase
    Serial.print("Connot Connected Firebase :...");
    Serial.println(Firebase.error());
    return;
    delay(myDelay);
    }

    Serial.print("Success Connected Firebase Times ==>\n");
    //Serial.println(Firebase.getInt("led"));

    //intIndex = Firebase.getInt("led");

    //intIndex++;

  intSwitch = Firebase.getInt("Switch1/LED1");

  if(intSwitch==0){
    //  for myOutput
      digitalWrite(myOutput, LOW);   // turn the LED on (HIGH is the voltage level) 
  }
  else{
      digitalWrite(myOutput, HIGH);  
    
    }

  intSwitch2 = Firebase.getInt("Switch1/LED2");

  if(intSwitch2==0){
    //  for myOutput
      digitalWrite(myOutput2, LOW);   // turn the LED on (HIGH is the voltage level) 
  }
  else{
      digitalWrite(myOutput2, HIGH);  
    
    }
  
    delay(myDelay);


  
}//Loop
