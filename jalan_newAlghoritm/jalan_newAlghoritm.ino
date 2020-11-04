#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
//global servo running
#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   500
#define FREQUENCY             50


//setVar ultrasonic===============================================
const int trigerKiri = 14; // Trigger Pin of Ultrasonic Sensor
const int echoKiri = 15; // Echo Pin of Ultrasonic Sensor
const int trigerKanan = 16; // Trigger Pin of Ultrasonic Sensor
const int echoKanan = 17; // Echo Pin of Ultrasonic Sensor
const int trigerDepan = 18; // Trigger Pin of Ultrasonic Sensor
const int echoDepan = 19; // Echo Pin of Ultrasonic Sensor
const int tembok = 20; // tembok

boolean getValue = true;
long durationKiri, durationKanan, durationDepan;
long cm[] = {0, 0, 0};

//flame var the box==============================
int pins[] = {A1, A2, A3, A4, A5};
int x;
int sudut = 90;
int myValue[] = {0, 0, 0, 0, 0};
int myKey[] = {1, 2, 3, 4, 5};
int i, digitValue;

   
void setup() {
  Serial.begin(9600);
  setUpUltrason();
  pwm.begin(); 
  pwm.setPWMFreq(FREQUENCY);
  //tengah
  pwm.setPWM(5, 0, pulseWidth(90));//kanan tengah depan
  pwm.setPWM(1, 0, pulseWidth(90));//kiri tengah depan
  pwm.setPWM(9, 0, pulseWidth(90));//kanan tengah belakang
  pwm.setPWM(13, 0, pulseWidth(90));//kiri tengah belakang
  degre(80,100);
  delay(5000);
  setUpFlame();
}


void loop() {
  getWall();
  getFlameData();
   if(cm[0] >= tembok){
      Serial.println("Belok Kiri");
      Belok(40, 130); //kiri
      pwm.setPWM(15, 0, pulseWidth(90));//servo leher X
      
   }else if(cm[1] >= tembok){
      Serial.println("Belok kanannnn");
      Belok(130, 40);//kanan
       pwm.setPWM(15, 0, pulseWidth(90));//servo leher X
       
   }else if(cm[2] <= 10){
      Serial.println("Berhenti");
      degre(80, 100);
//      if (myKey[4] + 1 == 3 )
//      {
//        Serial.println("stoped");
//      }   
//      else
//      {
//        if (myKey[4] + 1 > 3)
//        {
//          // putar kiri
//           Serial.println("Kiriiiiiiii");
//            sudut = sudut + 20;
//             pwm.setPWM(15, 0, pulseWidth(sudut));//servo leher X
//             
//          
//        }
//        else
//        {
//          // putar kanan
//          Serial.println("kanannnnnnnn");
//            sudut = sudut - 20;
//            pwm.setPWM(15, 0, pulseWidth(sudut));//servo leher X
//        }
//      }
   }else{
      Serial.println("maju terus pantang mundur I LOVE YOU yang baca....!!! muach");
      setupServoPwm();
      pwm.setPWM(15, 0, pulseWidth(90));//servo leher X
   }

}


int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}

int d = 100;
int dly = 50;
int noMiror = 30;
int miror = 150;



//maju=============================
//atas
int atNoMr = 90; //def 30
int atMr = 90; // def 150

//tengah
int backnoMr = 80; //def
int backMr = 100;

//bawah
int noMr = 80;
int mr = 100;



void Belok(int p, int m){

  //satu kanan depan
   pwm.setPWM(4, 0, pulseWidth(100)); //kanan bawah atas 
   pwm.setPWM(6, 0, pulseWidth(80)); //kanan bawah 84,120 
   delay(dly);
   pwm.setPWM(5, 0, pulseWidth(p)); //kanan tengah 84,120
   pwm.setPWM(6, 0, pulseWidth(100)); //kanan bawah 84,120 
   delay(d);

   //dua kiri depan
   pwm.setPWM(0, 0, pulseWidth(100)); //kanan bawah atas 
   pwm.setPWM(2, 0, pulseWidth(80)); //kanan bawah 84,120 
   delay(dly);
   pwm.setPWM(1, 0, pulseWidth(p)); //kanan tengah 84,120
   pwm.setPWM(2, 0, pulseWidth(100)); //kanan bawah 84,120 
   delay(d);

   // belakang kanan
   pwm.setPWM(8, 0, pulseWidth(100)); //kanan bawah atas 
   pwm.setPWM(10, 0, pulseWidth(80)); //kanan bawah 84,120 
   delay(dly);
   pwm.setPWM(9, 0, pulseWidth(m)); //kanan tengah 84,120
   pwm.setPWM(10, 0, pulseWidth(100)); //kanan bawah 84,120 
   delay(d);

   // belakang kiri
   pwm.setPWM(12, 0, pulseWidth(70)); //kanan bawah atas 
   pwm.setPWM(14, 0, pulseWidth(80)); //kanan bawah 84,120 
   delay(dly);
   pwm.setPWM(13, 0, pulseWidth(m)); //kanan tengah 84,120
   pwm.setPWM(14, 0, pulseWidth(100)); //kanan bawah 84,120 
   delay(d);
  degre(80,100);
  pwm.setPWM(5, 0, pulseWidth(90));//kanan tengah depan
  pwm.setPWM(1, 0, pulseWidth(90));//kiri tengah depan
  pwm.setPWM(9, 0, pulseWidth(90));//kanan tengah belakang
  pwm.setPWM(13, 0, pulseWidth(90));//kiri tengah belakang
  delay(d);
   
   
}



void setupServoPwm(){
    // satu======================================================================
    pwm.setPWM(4, 0, pulseWidth(atNoMr)); //miror depan atas kanan
    pwm.setPWM(6, 0, pulseWidth(backnoMr)); //kanan bawah 84,120
    delay(dly);
    pwm.setPWM(6, 0, pulseWidth(mr)); //kanan bawah 84,120 
    delay(d);

    //dua=========================================================================
    pwm.setPWM(0, 0, pulseWidth(atMr)); //depan atas kiri
    pwm.setPWM(2, 0, pulseWidth(backMr));//bawah miror//
    delay(dly);
    pwm.setPWM(2, 0, pulseWidth(noMr));//bawah miror//
    delay(d);

    
    //3 belakang===================================================================
    pwm.setPWM(10, 0, pulseWidth(atNoMr));//belakang kanan bawah
    pwm.setPWM(8, 0, pulseWidth(backnoMr)); //belakang atas kiri
    delay(dly);
    pwm.setPWM(10, 0, pulseWidth(mr));//belakang kanan bawah
    delay(d); 

    
    //4 belakang====================================================================
    pwm.setPWM(12, 0, pulseWidth(atMr)); //belakang atas kiri 
    pwm.setPWM(14, 0, pulseWidth(backMr));//belakang kanan bawah
    delay(dly);
    pwm.setPWM(14, 0, pulseWidth(noMr));//belakang kanan bawah
    delay(d);
    degre(80, 100);
    delay(d);
    
}

void degre(int p, int nP){
   // satu
   pwm.setPWM(4, 0, pulseWidth(nP)); //miror depan atas kanan 1
   pwm.setPWM(6, 0, pulseWidth(nP)); //kanan bawah 84,120
   pwm.setPWM(6, 0, pulseWidth(nP)); //kanan bawah 84,120
   //dua   
   pwm.setPWM(2, 0, pulseWidth(p));//bawah miror//
   pwm.setPWM(0, 0, pulseWidth(p)); //depan atas kiri
   pwm.setPWM(2, 0, pulseWidth(p));//bawah miror// 
   //3 belakang
   pwm.setPWM(10, 0, pulseWidth(nP));//belakang kanan bawah
   pwm.setPWM(8, 0, pulseWidth(nP)); //belakang atas kiri
   pwm.setPWM(10, 0, pulseWidth(nP));//belakang kanan bawah
   //4 belakang
   pwm.setPWM(14, 0, pulseWidth(p));//belakang kanan bawah
   pwm.setPWM(12, 0, pulseWidth(p)); //belakang atas kiri
   pwm.setPWM(14, 0, pulseWidth(p));//belakang kanan bawah
}


//sensor ultrasonic =========================================================
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

//flame seetttt ===============================
void setUpFlame(){
  pwm.setPWM(15, 0, pulseWidth(90));//servo leher X
  for (x=0; x<5; x++)
  {
    pinMode(pins[x], INPUT);
  }
}

void Urutkan()
{
  int j, k;
  int temp;
  int tempKey; 
  
  for (j=0; j<5; j++)
  {
    for(k=0; k<5; k++)
    {
      if (myValue[j] < myValue[k])
      {
        temp = myValue[k];
        tempKey = myKey[k];
        
        myValue[k] = myValue[j];
        myKey[k] = myKey[j];
        
        myValue[j] = temp;      
        myKey[j] = tempKey;      
      }
    }
  }
}

void getFlameData(){
  Serial.println("");
  for (i=0; i<5; i++)
  {
    digitValue = 0;
    //digitValue = digitalRead(dgts[i]);
    //delay(10);
    
    Serial.print(digitValue);
    Serial.print(" ");
      myValue[i] = analogRead(pins[i]);
    delay(5);
      
    myKey[i] = i;
  }
  Serial.println("");

  Serial.println("Nilai sebelum diurutkan: ");
  for(i=0; i<5; i++)
  {
    Serial.print("Nilai pin #");
    Serial.print(myKey[i] + 1);
    Serial.print(": ");
    Serial.print(myValue[i]);
    
    Serial.println("");    
  }
  
  Urutkan();
}
