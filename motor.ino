// initial motor tests
const int ultraTrig = 7;
const int ultraEcho = 4;
const int pwmA = 11;
const int pwmB = 3;
const int dirA = 12;
const int dirB = 13;
const int brakeA = 9;
const int brakeB = 8;
unsigned long duration;
int state = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(ultraTrig,OUTPUT);
  pinMode(ultraEcho,INPUT);
  pinMode(pwmA,OUTPUT);
  pinMode(pwmB,OUTPUT);
  pinMode(dirA,OUTPUT);
  pinMode(dirB,OUTPUT);
  pinMode(brakeA,OUTPUT);
  pinMode(brakeB,OUTPUT);
  
  // set directio for both as 1
  digitalWrite(dirA,HIGH);
  digitalWrite(dirB,LOW);
  digitalWrite(brakeA,LOW);
  digitalWrite(brakeB,LOW);
  analogWrite(pwmA,0);
  analogWrite(pwmB,0);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  readDistance2();
}


void readDistance2()
{
  Serial.print("State: ");
  Serial.println(state);
  
  switch (state)
  {
    case 0: // initialization, touch only once
       // we have turned on,  perhaps I want to init things here
       // in the future
       state = 1;
    break;
    case 1: // go forward
       // set us to go forward
       digitalWrite(dirA,HIGH);
       digitalWrite(dirB,LOW);

       analogWrite(pwmA,255);
       analogWrite(pwmB,255);
       state = 2;
    break;
    case 2: // poll forward state
       digitalWrite(ultraTrig, HIGH);
       delay(1);
       digitalWrite(ultraTrig, LOW);
       duration = pulseIn(ultraEcho,HIGH);
       if (duration < 1200)
       {
         analogWrite(pwmA,0);
         analogWrite(pwmB,0);
         state = 3; // transition to go backwards state after stopping motor
       } // else we stay in this state and just poll
       delay(200);
    break;
    case 3: // turning state 
         digitalWrite(dirB,HIGH);
         analogWrite(pwmA,255);
         analogWrite(pwmB,255);   
         state = 4; 
    break;
    case 4:
       digitalWrite(ultraTrig, HIGH);
       delay(1);
       digitalWrite(ultraTrig, LOW);
       duration = pulseIn(ultraEcho,HIGH);
       if (duration > 1200)
       {
         analogWrite(pwmA,0);
         analogWrite(pwmB,0);
         state = 1; // transition to go backwards state after stopping motor
       } // else we stay in this state and just poll
       delay(200);
    break;
  }
  
}

void readDistance()
{
  digitalWrite(ultraTrig, HIGH);
  delay(1);
  digitalWrite(ultraTrig, LOW);
  duration = pulseIn(ultraEcho,HIGH);
  Serial.print("Duration: ");
  Serial.println(duration);
  if (duration < 1200)
  {
      Serial.println("Turning off motor");
      analogWrite(pwmA,0);
      analogWrite(pwmB,0);
      Serial.println("Reversing Motor");
      digitalWrite(dirB,LOW);
      analogWrite(pwmA,255);
      analogWrite(pwmB,255);

      
   } else
   {
      Serial.println("Both Motors Forward");
      digitalWrite(dirB,HIGH);
      analogWrite(pwmA,255);
      analogWrite(pwmB,255);
     
   }
  delay(500);                   // delay for onTime milliseconds

}
