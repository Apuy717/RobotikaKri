#include <Servo.h>
Servo myServo;
int pins[] = {A1, A2, A3, A4, A5};

int x;
int sudut = 90;

void setup() {
  myServo.attach(5);
  myServo.write(90);

  for (x=0; x<5; x++)
  {
    pinMode(pins[x], INPUT);
   // pinMode(dgts[x], INPUT);
    
  }
  
  
  Serial.begin(9600);
  delay(10);
}

int myValue[] = {0, 0, 0, 0, 0};
int myKey[] = {1, 2, 3, 4, 5};

int i;
int digitValue;

void loop() {
  Serial.println("");
  for (i=0; i<5; i++)
  {
    digitValue = 0;
    //digitValue = digitalRead(dgts[i]);
    //delay(10);
    
    Serial.print(digitValue);
    Serial.print(" ");
    
    //if (digitValue == 1)
      myValue[i] = analogRead(pins[i]);
   // else
     // myValue[i] = 0;
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
    if(myKey[2] == myKey[4]){
      //stop
       Serial.println("diam "); 
    }
  }
  else
  {
    if (myKey[4] + 1 > 3)
    {
      // putar kiri
        sudut = sudut + 20;
        myServo.write(sudut);
      
    }
    else
    {
      // putar kanan
        sudut = sudut - 20;
        myServo.write(sudut);
    }
  }
//  delay(1000);
  
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
