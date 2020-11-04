//new ultrason

const int trigerKiri = 14; // Trigger Pin of Ultrasonic Sensor
const int echoKiri = 15; // Echo Pin of Ultrasonic Sensor
const int trigerKanan = 16; // Trigger Pin of Ultrasonic Sensor
const int echoKanan = 17; // Echo Pin of Ultrasonic Sensor
const int trigerDepan = 18; // Trigger Pin of Ultrasonic Sensor
const int echoDepan = 19; // Echo Pin of Ultrasonic Sensor
const int tembok = 20;

void setup() {
  Serial.begin(9600);
  setUpUltrason();   
}

boolean getValue = true;
long durationKiri, durationKanan, durationDepan;
long cm[] = {0, 0, 0};
void loop() {
  getWall();
//   if(cm[0] > tembok){
//     Serial.println("pintu kiri");
//     getValue = false;
//   }else if(cm[1] >tembok){
//     Serial.println("pintu kanan");
//     getValue = false;
//   }else{
//     getValue = true;
//   }
//  if(getValue){
//   Serial.println("jalan terus gak ada pintu");
//  }

   Serial.print("nilai ke [0] / kiri");
   Serial.println(cm[0]); 
   Serial.print("nilai ke [1] / kanan");
   Serial.println(cm[1]);
   Serial.print("nilai ke [2] / Depan");
   Serial.println(cm[2]);
   delay(1000);
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void setUpUltrason(){
   pinMode(trigerKiri, OUTPUT);
   pinMode(echoKiri, INPUT);
   pinMode(trigerKanan, OUTPUT);
   pinMode(echoKanan, INPUT);
   pinMode(trigerDepan, INPUT);
   pinMode(echoDepan, INPUT);
}


void getWall(){
   // kiri
   digitalWrite(trigerKiri, LOW);
   digitalWrite(trigerKiri, HIGH);
   digitalWrite(trigerKiri, LOW);
   durationKiri = pulseIn(echoKiri, HIGH);
   cm[0] = microsecondsToCentimeters(durationKiri);
   //kanan
   digitalWrite(trigerKanan, LOW);
   digitalWrite(trigerKanan, HIGH);
   digitalWrite(trigerKanan, LOW);
   durationKanan = pulseIn(echoKanan, HIGH);
   cm[1] = microsecondsToCentimeters(durationKanan);

   //Depan
   digitalWrite(trigerDepan, LOW);
   digitalWrite(trigerDepan, HIGH);
   digitalWrite(trigerDepan, LOW);
   durationDepan = pulseIn(echoDepan, HIGH);
   cm[2] = microsecondsToCentimeters(durationDepan);
}
