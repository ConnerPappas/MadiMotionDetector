const int firstLEDIndicator = 12;
const int secondLEDIndicator = 13;
const byte interruptPin = 2;
volatile byte peopleDetected;
volatile unsigned long previousTime;
volatile unsigned long recentTime;
volatile int sensorValue;

void setup()
{
  pinMode(firstLEDIndicator, OUTPUT);
  pinMode(secondLEDIndicator, OUTPUT);
  peopleDetected = 0;
  recentTime = millis();
  previousTime = recentTime;
  sensorValue = analogRead(A0);
  attachInterrupt(digitalPinToInterrupt(interruptPin), detection, FALLING);
}

void loop()
{
  
}

void detection()
{
  previousTime = recentTime;
  recentTime = millis();
  sensorValue = analogRead(A0);

  if (peopleDetected == 0 && recentTime - previousTime > 10000)
  {
    peopleDetected++;
    lightEmUp();
  }
  else 
  {
    if (recentTime - previousTime >= 5000 + (int) floor((sensorValue * (5000.0 / 1023.0))))
    {
      peopleDetected++;
      lightEmUp();
    }
  }
}

void lightEmUp()
{
  digitalWrite(firstLEDIndicator, LOW);
  digitalWrite(secondLEDIndicator, LOW);

  if (peopleDetected <= 1)
  {
    digitalWrite(firstLEDIndicator, HIGH);
  }
  else if (peopleDetected > 1)
  {
    digitalWrite(secondLEDIndicator, HIGH);
  }
  else
  {
    digitalWrite(firstLEDIndicator, HIGH);
    digitalWrite(secondLEDIndicator, HIGH);
  }
}

