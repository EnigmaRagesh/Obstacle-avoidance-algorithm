/*Sabertooth Motor Driver,  3 Ultrasonic Sensors
      //s1 is right motor and s2 is left motor
     //0-forward
      //180-backward*/
/*___________________________________________________________________________________________________________________________________________*/

#include <Servo.h>

void measure();
 
Servo S1, S2; 
int flag=0;                                                                 
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;
const int trigPin3 = 6;
const int echoPin3 = 7;
long R;
long C;
long L;


void measure()
{
  //left sensor//
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  L = pulseIn(echoPin1, HIGH);
  //center sensor//
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  C = pulseIn(echoPin2, HIGH);
  //right//
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  R = pulseIn(echoPin3, HIGH);
  /*Serial.print("Duration1: ");
  Serial.println(R);
  delay(50);
  Serial.print("Duration2: ");
  Serial.println(C);
  delay(50);
  Serial.print("Duration3: ");
  Serial.println(L);
  delay(50);*/
}

void setup() 
{
  S1.attach( 11, 1000, 2000);
  S2.attach(12, 1000, 2000);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  Serial.begin(9600);
  
}
void loop()
{
  find_angle(); 
  measure();
  if (C >= 2500)
  {

    if (R <= 2000)
    {
      S1.write(0);
      S2.write(180);
      delay(10);
    }
    else if (L <= 2000)
    {
      S1.write(180);
      S2.write(0);
      delay(10);
    }
    else
    {
      S1.write(0);
      S2.write(0);
      delay(10);

    }
  }
  if (C < 2200){
    S1.write(90);
    S2.write(90);
    delay(10);
    if (R > L )
    {
      while( C < 10000)
     {
      S1.write(180);
      S2.write(0);
      delay(50);
      measure();
     }
    }
    else if (L < R )
    {
     while( C < 10000)
     {
      S1.write(0);
      S2.write(180);
      delay(50);
      measure();
     }
    }
    else
    {
      S1.write(0);
      S2.write(180);
      delay(50);
      flag++;
      if(flag==3)
      {
         flag=0;
         S1.write(180);
         S2.write(0);
         delay(50);
      }
    }
    
  }

}
