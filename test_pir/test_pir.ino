//const int PIR = 2;
//const int ledPin = 7;
//const int batasdelay = 0;
//int waktuawal = 0;
//void setup() {
//  Serial.begin(9600);
//  pinMode(PIR, INPUT);
//  pinMode(ledPin, OUTPUT);
//
//}
//void loop() {
//  int dataPIR = digitalRead(PIR);
////  Serial.println("ON");
//  if (dataPIR == HIGH)
//  {
//    digitalWrite(ledPin, HIGH);
//    Serial.println("ON");
//    //        waktuawal = millis();
//  } else {
//    digitalWrite(ledPin, );
//    Serial.println("OFF");
//  }
//  //    if(millis()-waktuawal>batasdelay)
//  //    {
//  //        digitalWrite(ledPin, LOW);
//  //    }
//}

#define RELAY_ON LOW // Relay LED off when relay on
#define RELAY_OFF HIGH // Relay LED on when relay off
#define RELAY_1  2   // pin yang digunakan bisa diganti ganti bro

int indikator = 12; // buat indikator LED
int inputVout = 13; // Vout PIR
int statusPIR = LOW; // status logical
int data = 0; // variabel temporary utk menampung data PIR 
 
void setup() {
pinMode(indikator, OUTPUT); //set pin D6 sbg output
pinMode(inputVout, INPUT); // set pin D7 sbg input
Serial.begin(9600); //serial monitor
// Set pin as output.
pinMode(RELAY_1, OUTPUT); 
// Initialize relay one as off so that on reset it would be off by default
digitalWrite(RELAY_1, RELAY_OFF);
} 
 
void loop(){
data = digitalRead(inputVout); // baca input dr Vout
if ((data == HIGH) && (statusPIR == LOW)) { // cek jika ada pergerakan
       digitalWrite(indikator, LOW); // nyalakan led indikator di board Arduino
        Serial.println("GERAKAN TERDETEKSI!"); //buat monitor ke laptop
         statusPIR = HIGH; //diset high spy tdk mendeteksi terus
         
         digitalWrite(RELAY_1, RELAY_ON);
         delay(10000);
         digitalWrite(RELAY_1, RELAY_OFF);
         delay(0);
} else {
  if ((data == LOW) && (statusPIR == HIGH)){
   digitalWrite(indikator, HIGH); // matikan led indikator
   Serial.println("GERAKAN BERAKHIR!"); //buat monitor ke laptop
   statusPIR = LOW;
   }
 }
}
