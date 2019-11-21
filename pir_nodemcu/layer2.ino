#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "tugasakhir-02.firebaseio.com"                    //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "NcsExe8RUjhTFwLFQ15Ke8utRRBfaWM8W7lNJYgz"       //Your Firebase Database Secret goes here
#define WIFI_SSID "Razer WiFi"                                          //Your WiFi Name
#define WIFI_PASSWORD "01454765"                                        //Password of your wifi network 
#define timeSeconds 20

int relay = 2; // choose the pin for the RELAY
int pir = 13; // choose the input pin (for PIR sensor)
int gerak = 0; // variable for reading the pin status
int bypass, lampu, automode, manualmode, layer2, lampu3, layer3; // neighbor; // variable for reading firebase value
int sensor;

unsigned long now = millis();
unsigned long lastTrigger = 0;
bool mulaiTimer = false;

void setup() {
  pinMode(relay, OUTPUT); // declare lamp as output
  pinMode(pir, INPUT_PULLUP); // declare sensor as input
  attachInterrupt(digitalPinToInterrupt(pir), deteksiGerakan, RISING);
  digitalWrite(relay, 0);
  Serial.begin(9600);
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
//  Firebase.setInt("Layer 2", 0);
//  Firebase.setInt("Layer 3", 0);
//  Firebase.setInt("Lampu2-1", 0);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to wifi");
  bypass = Firebase.getString("Bypass2-1").toInt();
  automode = Firebase.getString("Auto").toInt();
  manualmode = Firebase.getString("Manual").toInt();
  layer2 = Firebase.getInt("Layer 2");
//  layer3 = Firebase.getInt("Layer 3");
  lampu3 = Firebase.getInt("Lampu3-1");
  gerak = digitalRead(pir); // read input value
}

void firebasereconnect(){
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

ICACHE_RAM_ATTR void deteksiGerakan(){
  if (layer2 == 1 && (automode == 1 && manualmode == 0)){
    digitalWrite(relay, HIGH);
    Serial.println("Gerakan Terdeteksi!");
    mulaiTimer = true;
    lastTrigger = millis();
    sensor = 1;
    lampu = 1;
  }
}
 
void loop(){
  now = millis();
  if(lampu3 == 0 && (mulaiTimer && (now - lastTrigger > (timeSeconds*1000)))) {
    digitalWrite(relay, LOW);
    Serial.println("Gerakan Tidak Terdetksi");
    mulaiTimer = false;
    lampu = 0;
    sensor = 0;
  }
  
  if (sensor == 1){
    Firebase.setInt("Layer 3", 1);
  } else {
    Firebase.setInt("Layer 3", 0);
  }

  if (lampu == 1){
    Firebase.setInt("Lampu2-1", 1);
  } else {
    Firebase.setInt("Lampu2-1", 0);
  }
  
  if (Firebase.failed()){
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    firebasereconnect();
    return;
  }

  if (manualmode == 1 && automode == 0){
      if (bypass == 0) {
      digitalWrite(relay, LOW); 
      Serial.println("Lampu2-1 Mati");
    } else {
      digitalWrite(relay,HIGH);
      Serial.println("Lampu2-1 Menyala");
    }
  }
}
