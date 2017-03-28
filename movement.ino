#define trigPin 6
#define echoPin 5

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
}

void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  //delay(1000);
  digitalWrite(trigPin, HIGH);
  //delay(1000);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration/2) / 29.1; //turn into cm
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 1)
  {
     Serial.println("stop");
     digitalWrite(9, HIGH);  //Engage the Brake for Channel A
     analogWrite(3, 0);
     digitalWrite(8, HIGH);  //Engage the Brake for Channel B
     analogWrite(11, 0);
  }
  else if(distance < 10 && distance > 1)
  {
    //going backward
    //Motor A forward @ full speed
    digitalWrite(12, HIGH);  //Establishes backward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 123);    //Spins the motor on Channel A at half speed

    //Motor B backward @ full speed
    digitalWrite(13, LOW); //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 123);   //Spins the motor on Channel B at full speed
    
  }
  else
  {
  //going backward
    //Motor A forward @ full speed
    digitalWrite(12, LOW);  //Establishes backward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 123);    //Spins the motor on Channel A at half speed

    //Motor B backward @ full speed
    digitalWrite(13, HIGH); //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 123);   //Spins the motor on Channel B at full speed
  }

}
