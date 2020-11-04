#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
int pins[] = {A1, A2, A3, A4, A5};

int x;
int sudut = 90;

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   500
#define FREQUENCY             50


int myValue[] = {0, 0, 0, 0, 0};
int myKey[] = {1, 2, 3, 4, 5};

int i, digitValue;
void setup() {
  pwm.begin(); 
  pwm.setPWMFreq(FREQUENCY);
  setUpFlame();
  Serial.begin(9600);
  delay(10);
}

void loop() {
  getFlameData();
  Serial.println("Nilai setelah diurutkan: ");
  for(i=0; i<5; i++)
  {
    Serial.print("Nilai pin #");
    Serial.print(myKey[i] + 1);
    Serial.print(": ");
    Serial.print(myValue[i]);
    
    Serial.println("");    
  }

  if (myKey[4] + 1 == 3 )
  {
    Serial.println("stoped");
  }   
  else
  {
    if (myKey[4] + 1 > 3)
    {
      // putar kiri
       Serial.println("Kiriiiiiiii");
        sudut = sudut + 20;
         pwm.setPWM(15, 0, pulseWidth(sudut));//servo leher X
         
      
    }
    else
    {
      // putar kanan
      Serial.println("kanannnnnnnn");
        sudut = sudut - 20;
        pwm.setPWM(15, 0, pulseWidth(sudut));//servo leher X
    }
  }
  delay(1000);
  
}

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

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}
