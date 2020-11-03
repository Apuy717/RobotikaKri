#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
//global servo running
#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   500
#define FREQUENCY             50

//global var ultrasonic
const int pingPinKiri = 2; // Trigger kiri
const int echoPinKiri = 3; // Echo kiri
const int pingPinKanan = 8; // Trigger kanan
const int echoPinKanan = 9; // Echo kanan
const int tembok = 20; //params tembok
long duration0, duration1;
long cm[] = {0, 0};
boolean getValue = true;
   
void setup() {
  //serial print debbugging
  Serial.begin(9600);

  //sensor
  pinMode(pingPinKiri, OUTPUT);
  pinMode(echoPinKiri, INPUT);
  pinMode(pingPinKanan, OUTPUT);
  pinMode(echoPinKanan, INPUT);

 //servo titik awal
  setupServoPwm();
  
}


void loop() {
  ultrasonKiriAndKanan();
  if(cm[0] > tembok && cm[1] > tembok){
    Serial.println("bingung");
  }else{
   if(cm[0] > tembok){
     Serial.println("pintu kiri");
     belokKiri();
   }else if(cm[1] > tembok){
     belokKanan();
     Serial.println("pintu kanan");
    } else{
      maju();
      Serial.println(cm[1]);
   } 
  }
}


int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}

void belokKanan(){
  //posisi 1
    //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan atas kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang atas kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan atas kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror atas belakang 
    // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(90));//kiri depan
    pwm.setPWM(9, 0, pulseWidth(90));//kanan belakang
    pwm.setPWM(5, 0, pulseWidth(90));//kanan depan
    pwm.setPWM(13, 0, pulseWidth(90));//kiri belakang
    //bawah
    pwm.setPWM(2, 0, pulseWidth(86));//bawah miror    //kiri depan
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror   //kiri belakang
    pwm.setPWM(6, 0, pulseWidth(94));  //kanan depan
    pwm.setPWM(10, 0, pulseWidth(94)); //kanan belakang
    delay(30);
  //posisi 2
    //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan atas kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang atas kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan atas kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror atas belakang 
    // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(115));//kiri depan
    pwm.setPWM(9, 0, pulseWidth(65));//kanan belakang
    pwm.setPWM(5, 0, pulseWidth(90));//kanan depan
    pwm.setPWM(13, 0, pulseWidth(90));//kiri belakang
    //bawah
    pwm.setPWM(2, 0, pulseWidth(97));//bawah miror    //kiri depan
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror   //kiri belakang
    pwm.setPWM(6, 0, pulseWidth(94));  //kanan depan
    pwm.setPWM(10, 0, pulseWidth(83)); //kanan belakang
    delay(30);
   //posisi 3
   //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror belakang 
   // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(115));
    pwm.setPWM(9, 0, pulseWidth(65));
    pwm.setPWM(5, 0, pulseWidth(90));
    pwm.setPWM(13, 0, pulseWidth(90));
   //bawah
    pwm.setPWM(2, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(6, 0, pulseWidth(94));
    pwm.setPWM(10, 0, pulseWidth(94));
    delay(30);
    //posisi 4
   //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror belakang 
   // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(90));
    pwm.setPWM(9, 0, pulseWidth(90));
    pwm.setPWM(5, 0, pulseWidth(115));
    pwm.setPWM(13, 0, pulseWidth(65));
   //bawah
    pwm.setPWM(2, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(14, 0, pulseWidth(97));//bawah miror
    pwm.setPWM(6, 0, pulseWidth(83));
    pwm.setPWM(10, 0, pulseWidth(94));
    delay(30);
     //posisi 5
   //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror belakang 
   // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(90));
    pwm.setPWM(9, 0, pulseWidth(90));
    pwm.setPWM(5, 0, pulseWidth(115));
    pwm.setPWM(13, 0, pulseWidth(65));
   //bawah
    pwm.setPWM(2, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(6, 0, pulseWidth(94));
    pwm.setPWM(10, 0, pulseWidth(94));
    delay(30);
      //posisi 6
   //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror belakang 
   // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(90));
    pwm.setPWM(9, 0, pulseWidth(90));
    pwm.setPWM(5, 0, pulseWidth(90));
    pwm.setPWM(13, 0, pulseWidth(90));
   //bawah
    pwm.setPWM(2, 0, pulseWidth(97));//bawah miror
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(6, 0, pulseWidth(94));
    pwm.setPWM(10, 0, pulseWidth(83));
        //posisi 7
    delay(30);
   //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror belakang 
   // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(90));
    pwm.setPWM(9, 0, pulseWidth(90));
    pwm.setPWM(5, 0, pulseWidth(90));
    pwm.setPWM(13, 0, pulseWidth(90));
   //bawah
    pwm.setPWM(2, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(6, 0, pulseWidth(94));
    pwm.setPWM(10, 0, pulseWidth(94));
    delay(30);
}

void belokKiri(){
    //posisi 7
   //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror belakang 
   // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(90));
    pwm.setPWM(9, 0, pulseWidth(90));
    pwm.setPWM(5, 0, pulseWidth(90));
    pwm.setPWM(13, 0, pulseWidth(90));
   //bawah
    pwm.setPWM(2, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(6, 0, pulseWidth(94));
    pwm.setPWM(10, 0, pulseWidth(94));
    delay(30);

    //posisi 6
   //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror belakang 
   // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(90));
    pwm.setPWM(9, 0, pulseWidth(90));
    pwm.setPWM(5, 0, pulseWidth(90));
    pwm.setPWM(13, 0, pulseWidth(90));
   //bawah
    pwm.setPWM(2, 0, pulseWidth(97));//bawah miror
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(6, 0, pulseWidth(94));
    pwm.setPWM(10, 0, pulseWidth(83));
    delay(30);
    //posisi 5
   //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror belakang 
   // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(90));
    pwm.setPWM(9, 0, pulseWidth(90));
    pwm.setPWM(5, 0, pulseWidth(115));
    pwm.setPWM(13, 0, pulseWidth(65));
   //bawah
    pwm.setPWM(2, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(6, 0, pulseWidth(94));
    pwm.setPWM(10, 0, pulseWidth(94));
    delay(30);

    //posisi 4
   //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror belakang 
   // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(90));
    pwm.setPWM(9, 0, pulseWidth(90));
    pwm.setPWM(5, 0, pulseWidth(115));
    pwm.setPWM(13, 0, pulseWidth(65));
   //bawah
    pwm.setPWM(2, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(14, 0, pulseWidth(97));//bawah miror
    pwm.setPWM(6, 0, pulseWidth(83));
    pwm.setPWM(10, 0, pulseWidth(94));
    delay(30);

     //posisi 3
   //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror belakang 
   // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(115));
    pwm.setPWM(9, 0, pulseWidth(65));
    pwm.setPWM(5, 0, pulseWidth(90));
    pwm.setPWM(13, 0, pulseWidth(90));
   //bawah
    pwm.setPWM(2, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror
    pwm.setPWM(6, 0, pulseWidth(94));
    pwm.setPWM(10, 0, pulseWidth(94));
    delay(30);

  //posisi 2
    //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan atas kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang atas kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan atas kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror atas belakang 
    // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(115));//kiri depan
    pwm.setPWM(9, 0, pulseWidth(65));//kanan belakang
    pwm.setPWM(5, 0, pulseWidth(90));//kanan depan
    pwm.setPWM(13, 0, pulseWidth(90));//kiri belakang
    //bawah
    pwm.setPWM(2, 0, pulseWidth(97));//bawah miror    //kiri depan
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror   //kiri belakang
    pwm.setPWM(6, 0, pulseWidth(94));  //kanan depan
    pwm.setPWM(10, 0, pulseWidth(83)); //kanan belakang
    delay(30);

     //posisi 1
    //1 set atas 4
    pwm.setPWM(0, 0, pulseWidth(90)); //depan atas kiri
    pwm.setPWM(8, 0, pulseWidth(90)); //belakang atas kiri
    pwm.setPWM(4, 0, pulseWidth(90)); //miror depan atas kanan
    pwm.setPWM(12, 0, pulseWidth(90)); //miror atas belakang 
    // 1 set tengah
    pwm.setPWM(1, 0, pulseWidth(90));//kiri depan
    pwm.setPWM(9, 0, pulseWidth(90));//kanan belakang
    pwm.setPWM(5, 0, pulseWidth(90));//kanan depan
    pwm.setPWM(13, 0, pulseWidth(90));//kiri belakang
    //bawah
    pwm.setPWM(2, 0, pulseWidth(86));//bawah miror    //kiri depan
    pwm.setPWM(14, 0, pulseWidth(86));//bawah miror   //kiri belakang
    pwm.setPWM(6, 0, pulseWidth(94));  //kanan depan
    pwm.setPWM(10, 0, pulseWidth(94)); //kanan belakang
    delay(30);
}

void maju(){
  pwm.setPWM(0, 0, pulseWidth(104));
  pwm.setPWM(8, 0, pulseWidth(81));
  pwm.setPWM(4, 0, pulseWidth(99));
  pwm.setPWM(12, 0, pulseWidth(76));
  pwm.setPWM(1, 0, pulseWidth(90));
  pwm.setPWM(9, 0, pulseWidth(90));
  pwm.setPWM(5, 0, pulseWidth(90));
  pwm.setPWM(13, 0, pulseWidth(90));
  pwm.setPWM(2, 0, pulseWidth(89));
  pwm.setPWM(14, 0, pulseWidth(91));
  pwm.setPWM(6, 0, pulseWidth(91));
  pwm.setPWM(10, 0, pulseWidth(89));
  
  delay(40);
  pwm.setPWM(0, 0, pulseWidth(91));
  pwm.setPWM(8, 0, pulseWidth(85));
  pwm.setPWM(4, 0, pulseWidth(95));
  pwm.setPWM(12, 0, pulseWidth(89));
  pwm.setPWM(1, 0, pulseWidth(90));
  pwm.setPWM(9, 0, pulseWidth(90));
  pwm.setPWM(5, 0, pulseWidth(90));
  pwm.setPWM(13, 0, pulseWidth(90));
  pwm.setPWM(2, 0, pulseWidth(91.5));
  pwm.setPWM(14, 0, pulseWidth(88.5));
  pwm.setPWM(6, 0, pulseWidth(77));
  pwm.setPWM(10, 0, pulseWidth(103));
  delay(40);
  pwm.setPWM(0, 0, pulseWidth(81));
  pwm.setPWM(8, 0, pulseWidth(104));
  pwm.setPWM(4, 0, pulseWidth(76));
  pwm.setPWM(12, 0, pulseWidth(99));
  pwm.setPWM(1, 0, pulseWidth(90));
  pwm.setPWM(9, 0, pulseWidth(90));
  pwm.setPWM(5, 0, pulseWidth(90));
  pwm.setPWM(13, 0, pulseWidth(90));
  pwm.setPWM(2, 0, pulseWidth(89));
  pwm.setPWM(14, 0, pulseWidth(91));
  pwm.setPWM(6, 0, pulseWidth(91));
  pwm.setPWM(0, 0, pulseWidth(89));
  delay(40);
  pwm.setPWM(0, 0, pulseWidth(85));
  pwm.setPWM(8, 0, pulseWidth(91.5));
  pwm.setPWM(4, 0, pulseWidth(88.5));
  pwm.setPWM(12, 0, pulseWidth(95));
  pwm.setPWM(1, 0, pulseWidth(90));
  pwm.setPWM(9, 0, pulseWidth(90));
  pwm.setPWM(5, 0, pulseWidth(90));
  pwm.setPWM(13, 0, pulseWidth(90));
  pwm.setPWM(2, 0, pulseWidth(103));
  pwm.setPWM(14, 0, pulseWidth(77));
  pwm.setPWM(6, 0, pulseWidth(89));
  pwm.setPWM(10, 0, pulseWidth(91));
  delay(40);
  pwm.setPWM(0, 0, pulseWidth(104));
  pwm.setPWM(8, 0, pulseWidth(81));
  pwm.setPWM(4, 0, pulseWidth(99));
  pwm.setPWM(12, 0, pulseWidth(76));
  pwm.setPWM(1, 0, pulseWidth(90));
  pwm.setPWM(9, 0, pulseWidth(90));
  pwm.setPWM(5, 0, pulseWidth(90));
  pwm.setPWM(13, 0, pulseWidth(90));
  pwm.setPWM(2, 0, pulseWidth(89));
  pwm.setPWM(14, 0, pulseWidth(91));
  pwm.setPWM(6, 0, pulseWidth(91));
  pwm.setPWM(10, 0, pulseWidth(89));
  delay(40);
}

void setupServoPwm(){
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
//  //1 set atas 4
  pwm.setPWM(0, 0, pulseWidth(90)); //depan atas kiri
  pwm.setPWM(8, 0, pulseWidth(90)); //belakang atas kiri
  pwm.setPWM(4, 0, pulseWidth(90)); //miror depan atas kanan
  pwm.setPWM(12, 0, pulseWidth(90)); //miror atas belakang kanan
// 1 set tengah

  pwm.setPWM(1, 0, pulseWidth(90));
  pwm.setPWM(9, 0, pulseWidth(90));
  pwm.setPWM(5, 0, pulseWidth(90));
  pwm.setPWM(13, 0, pulseWidth(90));

//  //set bawah
  pwm.setPWM(2, 0, pulseWidth(95));//bawah miror
  pwm.setPWM(14, 0, pulseWidth(95));//bawah miror
  pwm.setPWM(6, 0, pulseWidth(85));
  pwm.setPWM(10, 0, pulseWidth(85));
}

void ultrasonKiriAndKanan(){
     // kiri
   digitalWrite(pingPinKiri, LOW);
   digitalWrite(pingPinKiri, HIGH);
   digitalWrite(pingPinKiri, LOW);
   duration0 = pulseIn(echoPinKiri, HIGH);
   cm[0] = microsecondsToCentimeters(duration0);
   //kanan
   digitalWrite(pingPinKanan, LOW);
   digitalWrite(pingPinKanan, HIGH);
   digitalWrite(pingPinKanan, LOW);
   duration1 = pulseIn(echoPinKanan, HIGH);
   cm[1] = microsecondsToCentimeters(duration1);
}


long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
