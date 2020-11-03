//new ultrason

const int pingPinKiri = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPinKiri = 3; // Echo Pin of Ultrasonic Sensor
const int pingPinKanan = 8; // Trigger Pin of Ultrasonic Sensor
const int echoPinKanan = 9; // Echo Pin of Ultrasonic Sensor
const int tembok = 20;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(pingPinKiri, OUTPUT);
   pinMode(echoPinKiri, INPUT);
   pinMode(pingPinKanan, OUTPUT);
   pinMode(echoPinKanan, INPUT);
}

boolean getValue = true;
long duration0;
long duration1;
long cm[] = {0, 0};
void loop() {
    // kiri
   digitalWrite(pingPinKiri, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPinKiri, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPinKiri, LOW);
   duration0 = pulseIn(echoPinKiri, HIGH);
   cm[0] = microsecondsToCentimeters(duration0);
   delay(10);
   //kanan
   digitalWrite(pingPinKanan, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPinKanan, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPinKanan, LOW);
   duration1 = pulseIn(echoPinKanan, HIGH);
   cm[1] = microsecondsToCentimeters(duration1);

   if(cm[0] > tembok){
     Serial.println("pintu kiri");
     getValue = false;
   }else if(cm[1] >tembok){
     Serial.println("pintu kanan");
     getValue = false;
   }else{
     getValue = true;
   }
  if(getValue){
   Serial.println("jalan terus gak ada pintu");
  }

   Serial.print("nilai ke [0] / kiri");
   Serial.println(cm[0]); 
   Serial.print("nilai ke [1] / kanan");
   Serial.println(cm[1]);
   delay(1000);
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
