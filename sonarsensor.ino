#define trigPin 13
#define echoPin 12

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  //delayMicroseconds(2); // Added this line
  delay(1000);
  digitalWrite(trigPin, HIGH);
  delay(1000);
  //delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration/2) / 29.1; //turn into cm
  //Serial.print(distance);
  //Serial.println(" cm");

  if(distance < 6)
  {
     Serial.println("Hit");
  }

}
