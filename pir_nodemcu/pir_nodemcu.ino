#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "light-control-fe6f8.firebaseio.com"                       //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "VrkBz0o2te1yZFSy7AaoHKMJcbtFLKsd832G0T9y"        //Your Firebase Database Secret goes here
#define WIFI_SSID "Razer WiFi"                                          //Your WiFi Name
#define WIFI_PASSWORD "01454765"                                        //Password of your wifi network 

int relay = 2; // choose the pin for the RELAY
int pir = 13; // choose the input pin (for PIR sensor)
int gerak = 0; // variable for reading the pin status
int bypass;
int automode;
int manualmode;

void setup() {
  pinMode(relay, OUTPUT); // declare lamp as output
  pinMode(pir, INPUT); // declare sensor as input
  digitalWrite(relay, 0);
  Serial.begin(9600);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

void firebasereconnect(){
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

//void PIRbypass(){
//  lampu = Firebase.getString("Lampu").toInt();
//  if (lampu1 == 0) {
//    digitalWrite(relay, LOW); 
//    Serial.println("Lampu Mati");
//  }
//  else {
//    digitalWrite(relay,HIGH);
//    Serial.println("Lampu Menyala");
//  }
//}

  
void loop(){
  if (Firebase.failed()){
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    firebasereconnect();
    return;
  }
  bypass = Firebase.getString("Lampu").toInt();
  automode = Firebase.getString("Auto").toInt();
  manualmode = Firebase.getString("Manual").toInt();
  gerak = digitalRead(pir); // read input value
  if (automode == 1){
    if (gerak == 1){
      digitalWrite(relay,HIGH); // turn ON the lamp
      Serial.println("Gerakan Terdeteksi");
    } else {
      digitalWrite(relay,LOW); // turn ON the lamp
      Serial.println("Gerakan Tidak Terdeteksi");
    }
  }
  if (manualmode == 1){
    if (bypass == 0) {
    digitalWrite(relay, LOW); 
    Serial.println("Lampu Mati");
  } else {
    digitalWrite(relay,HIGH);
    Serial.println("Lampu Menyala");
  }
 }
}
//  if (lampu == 0) {
//    digitalWrite (relay, LOW); 
//    Serial.println("Lampu Mati");
//  } else if (lampu == 1) {
//    digitalWrite(relay,HIGH);
//    Serial.println("Lampu Menyala");
//  } else if (gerak == 1) {
//    digitalWrite(relay,HIGH); // turn ON the lamp
//    Serial.println("Gerakan Terdeteksi");
//  } else {
//    digitalWrite (relay,LOW); // turn OFF the lamp
//    Serial.println("Gerakan Tidak Terdeteksi");
//  }
//  delay(1000);
//  gerak = digitalRead(pir); // read input value
//  if( gerak== 1) {
//    PIRbypass();
//    digitalWrite(relay,HIGH); // turn ON the lamp
//    Serial.println("Gerakan Terdeteksi");
//    delay(10000);
//    Firebase.setInt("Lampu1",1);
//  } else {
//    PIRbypass();
//    Firebase.setInt("Lampu1",0);
//    digitalWrite(relay,LOW); // turn OFF the lamp
//    Serial.println("Gerakan Tidak Terdeteksi");
//    delay(0);
//  }
//}
