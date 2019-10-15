#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "light-control-fe6f8.firebaseio.com"              //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "VrkBz0o2te1yZFSy7AaoHKMJcbtFLKsd832G0T9y"        //Your Firebase Database Secret goes here
#define WIFI_SSID "Razer WiFi"                                          //Your WiFi Name
#define WIFI_PASSWORD "01454765"                                        //Password of your wifi network 

int lamp = 2; // choose the pin for the RELAY
int inputPin = 13; // choose the input pin (for PIR sensor)
int data = 0; // variable for reading the pin status
int lampu1;

void setup() {
  pinMode(lamp, OUTPUT); // declare lamp as output
  pinMode(inputPin, INPUT); // declare sensor as input
  digitalWrite(lamp, 0);
  Serial.begin(9600);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.setInt("Lampu1",0);
}

void firebasereconnect(){
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void PIRbypass(){
  lampu1 = Firebase.getString("Lampu1").toInt();
  if (lampu1 == 0) {
    digitalWrite(lamp, LOW); 
    Serial.println("Lampu Mati");
  }
  else {
    digitalWrite(lamp,HIGH);
    Serial.println("Lampu Menyala");
  }
}

void loop(){
  if (Firebase.failed()){
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    firebasereconnect();
    return;
  }
  data = digitalRead(inputPin); // read input value
  if( data== 1) {
    PIRbypass();
    digitalWrite(lamp,HIGH); // turn ON the lamp
    Serial.println("Gerakan Terdeteksi");
    delay(10000);
    Firebase.setInt("Lampu1",1);
  } else {
    PIRbypass();
    Firebase.setInt("Lampu1",0);
    digitalWrite(lamp,LOW); // turn OFF the lamp
    Serial.println("Gerakan Tidak Terdeteksi");
    delay(0);
  }
}
