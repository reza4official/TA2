#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "tugasakhir-02.firebaseio.com"                    //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "7I5IORRKJXuSURNvmjh6C5Sl37uEAEXjQNBaROCm"        //Your Firebase Database Secret goes here
//#define WIFI_SSID "Razer WiFi"                                          //Your WiFi Name
//#define WIFI_PASSWORD "01454765"                                        //Password of your wifi network 
#define timeSeconds 20

/** constant */
String ID = "Alat 1";       // Current device
String child = "Alat 2";    // device afterwards
String parent = "Alat 3";   // previous device
const char *ssid = "Razer WiFi";
const char *password = "01454765";

/** declare inputs */
int relay = 2;                                   // choose the pin for the RELAY
int pir = 13;                                    // choose the input pin (for PIR sensor)
int gerak = 0;                                   // variable for reading the pin status
int layer, automode, manualmode;                 // variable for reading firebase value
int Status, bypass;                              // variable for reading firebase value
int lampu, lampu2;                               // variable for reading firebase value
int sensor, lamp;                                // variable for reading input value

unsigned long now = millis();
unsigned long lastTrigger = 0;
bool mulaiTimer = false;

void setup() {
  Serial.begin(9600);                                                    // Serial Monitor baudrate
  pinMode(relay, OUTPUT);                                                // declare lamp as output
  pinMode(pir, INPUT_PULLUP);                                            // declare sensor as input
  attachInterrupt(digitalPinToInterrupt(pir), deteksiGerakan, RISING);
  digitalWrite(relay, 0);                                                // relay initial state
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                          // Begin Firebase connection
  WiFi.begin(ssid, password);                                  // Begin WiFi connection
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to wifi");
  gerak = digitalRead(pir);                                              // read input value
  layer = Firebase.getString(ID + "/Layer").toInt();                                // Get data for "Layer" variable from Firebase
}

/** Firebase reconnect function */
void firebasereconnect(){
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void readFirebaseData(){
  automode = Firebase.getString("Auto").toInt();
  manualmode = Firebase.getString("Manual").toInt();
  Status = Firebase.getString(ID + "/Status").toInt();
  lampu = Firebase.getString(parent + "/Lampu").toInt();
  lampu2 = Firebase.getString(child + "/Lampu").toInt();
  bypass = Firebase.getString(ID + "/Bypass").toInt();
}

/** Interrupt Procedure */
ICACHE_RAM_ATTR void deteksiGerakan(){
  if ((layer == 1 && Status == 1) && (automode == 1 && manualmode == 0)){           // Turn on layer 1
    digitalWrite(relay, HIGH);
    Serial.println("Gerakan Terdeteksi!");
    mulaiTimer = true;
    lastTrigger = millis();
    sensor = 1;
    lamp = 1;
  } else if ((layer == 2 && Status == 1) && (automode == 1 && manualmode == 0)){    // Turn on layer 2
    if (lampu == 1){
      digitalWrite(relay, HIGH);
      Serial.println("Gerakan Terdeteksi!");
      mulaiTimer = true;
      lastTrigger = millis();
      sensor = 1;
      lamp = 1;
    }
  } else if ((layer == 3 && Status == 1) && (automode == 1 && manualmode == 0)){    // Turn on layer 3
    if (lampu == 1){
      digitalWrite(relay, HIGH);
      Serial.println("Gerakan Terdeteksi!");
      mulaiTimer = true;
      lastTrigger = millis();
      sensor = 1;
      lamp = 1;
    }
  }
}

void loop(){
  
//** Firebase reconnect */
  if (Firebase.failed()){
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    firebasereconnect();
    return;
  }

  
  now = millis();
  

//  if ((layer == 1 && Status == 1) && (now - lastTrigger > (timeSeconds*1000))){           // Turn off layer 1
//    if (lampu2 == 0){
//      digitalWrite(relay, LOW);
//      Serial.println("Gerakan Tidak Terdeteksi");
//      mulaiTimer = false;
//      sensor = 0;
//      lamp = 0;
//    }
//  } 
//  else if ((layer == 2 && Status == 1) && (now - lastTrigger > (timeSeconds*1000))){    // Turn off layer 2
//    if (lampu2 == 0){
//      digitalWrite(relay, LOW);
//      Serial.println("Gerakan Tidak Terdeteksi");
//      mulaiTimer = false;
//      sensor = 0;
//      lamp = 0;
//    }
//  } else 
  if ((layer == 3 && Status == 1) && (now - lastTrigger > (timeSeconds*1000))){    // Turn off layer 3
    digitalWrite(relay, LOW);
    Serial.println("Gerakan Tidak Terdeteksi");
    mulaiTimer = false;
    sensor = 0;
    lamp = 0;
  }

//** turn off layer 2 */
  if ((layer == 2 && Status == 1) && (now - lastTrigger > (timeSeconds*1000))){
    if (lampu2 == 0){
      digitalWrite(relay, LOW);
      Serial.println("Gerakan Tidak Terdeteksi");
      mulaiTimer = false;
      sensor = 0;
      lamp = 0;
    }
  }

/** turn off layer 1 */
  if ((layer == 1 && Status == 1) && (now - lastTrigger > (timeSeconds*1000))){
    if (lampu2 == 0){
      digitalWrite(relay, LOW);
      Serial.println("Gerakan Tidak Terdeteksi");
      mulaiTimer = false;
      sensor = 0;
      lamp = 0;
    }
  }

/** Write data to Firebase */
  if (sensor == 1){
//    Firebase.setInt(child + "/Status", 1);
    Firebase.setString(child + "/Status", "1");
  } else {
//    Firebase.setInt(child + "/Status", 0);
    Firebase.setString(child + "/Status", "0"); 
  }
  
  if (lamp == 1){
//    Firebase.setInt(ID + "/Lampu", 1);
    Firebase.setString(ID + "/Lampu", "1");
  } else {
//    Firebase.setInt(ID + "/Lampu", 0);
    Firebase.setString(ID + "/Lampu", "0");
  }

/** Set Auto/Manual mode procedure */
  if (manualmode == 1 && automode == 0){
      if (bypass == 1) {
      digitalWrite(relay, HIGH); 
      Serial.println("Lampu1-1 Menyala");
    } else {
      digitalWrite(relay,LOW);
      Serial.println("Lampu1-1 Mati");
    }
  }
  readFirebaseData();
}
