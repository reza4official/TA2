int lamp = 2; // choose the pin for the RELAY
int inputPin = 13; // choose the input pin (for PIR sensor)
int data = 0; // variable for reading the pin status

void setup() {
  pinMode(lamp, OUTPUT); // declare lamp as output
  pinMode(inputPin, INPUT); // declare sensor as input
  Serial.begin(9600);
}

void loop(){
  data = digitalRead(inputPin); // read input value
  if( data== 1) {
    digitalWrite(lamp,HIGH); // turn ON the lamp
    Serial.println("Gerakan Terdeteksi");
    delay(10000);
  } else {
    digitalWrite(lamp,LOW); // turn OFF the lamp
    Serial.println("Gerakan Tidak Terdeteksi");
    delay(0);
  }
}
