
//Add Library
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//Explicit ประกาศตัวแปร
int led1 = D5;
int led2 = D6;
int myDelay = 1000;//ค่าของเวลาจะมีหน่วยเป็น มิลลิวินาที
int intIndex = 0;
int intSwitch = 0;
int intSwitch2 = 0;
int smoke = A0;
int sensorThres = 0;
int ledSmoke = D4;

//การกำหนดค่าคงที
#define wifiSSID "Kik"    //String wifiSSID="";
#define wifiPassword "12345678"
//-------------------------------------------------
//การทำงานบนfirebase
#define firebaseHost "kornchrismas.firebaseio.com"
#define firebaseKey "MBs1mOgX357Bf0egUqd8YMuhjNJEp8Ula6Fw6iHb"
//-------------------------------------------------





void setup() {

  //  ส่วนที่กำหนดการส่งสัญญาณ digital Out จากขาของ Node
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(smoke, INPUT);

  pinMode(ledSmoke, OUTPUT);
  
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
  Firebase.setInt("index", intIndex);
  
  if (Firebase.failed()) {

    //   มื่อไรก็ตามที่ไม่สามารถเข้า Firebase
    Serial.print("Connot Connected Firebase :...");
    Serial.println(Firebase.error());
    return;
    delay(myDelay);
    }

  Serial.print("Success Connected Firebase Times ==>\n");
  Serial.println(Firebase.getInt("LED1"));
  Serial.println(Firebase.getInt("LED2"));

  intIndex = Firebase.getInt("index");

  intIndex++;

  intSwitch = Firebase.getInt("LED1");

  if(intSwitch==0){
    //  for led1
      digitalWrite(led1, LOW);   // turn the LED on (HIGH is the voltage level) 
  }
  
  else {
      digitalWrite(led1, HIGH);  
  }

  intSwitch2 = Firebase.getInt("LED2");

  if(intSwitch2==0){
    //  for led2
      digitalWrite(led2, LOW);   // turn the LED on (HIGH is the voltage level) 
  }
  
  else {
      digitalWrite(led2, HIGH);  
    }
    
//------------------------------------------------------------------------------
//  sensersmoke

  int analogSensor = analogRead(smoke);
  Firebase.setInt("SensorGas", analogSensor);
  
  Serial.print("Sensor : ");
  Serial.println(analogSensor);
  
  if (analogSensor > sensorThres) {
    digitalWrite(ledSmoke, HIGH);
  }
  
  else {
    digitalWrite(ledSmoke, LOW);   
  }
  
  delay(myDelay);


  
}//Loop
