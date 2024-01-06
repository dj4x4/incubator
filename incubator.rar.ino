
#include <LiquidCrystal.h>
#include <Servo.h>

const int temperaturePin = A0;
const int fanPin = 10;
const int ledPin = 13; 

int y;
Servo s1;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  s1.attach(9);
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(temperaturePin, INPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(ledPin, OUTPUT); 
}

void loop()
{
  rotateServo(); 
  checkTemperature(22.00, 25.00);
}

void rotateServo()
{
  for (int i = 0; i <= 180; i += 1)
  {
    s1.write(i);
    delay(15);
  }
  delay(6UL * 60UL * 60UL * 1000UL);
  for (int i = 180; i >= 0; i -= 1)
  {
    s1.write(i);
    delay(15);
  }
  delay(6UL * 60UL * 60UL * 1000UL);
  for (int i = 180; i >= 0; i -= 1)
  {
    s1.write(i);
    delay(15);
  }
}

void checkTemperature(float less, float more)
{
  digitalWrite(fanPin, HIGH); // Turn on the fan
  delay(5000);                 // Run the fan for 5 seconds (adjust as needed)

  int sensorValue = analogRead(temperaturePin);
  float voltage = (sensorValue / 1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100;

  Serial.print("Temperature: ");
  Serial.println(temperature);

  // Adjust the threshold temperatures as needed
  if (temperature < less)
  {
    digitalWrite(ledPin, HIGH); // Turn on the LED
  }
  else if (temperature > more)
  {
    digitalWrite(ledPin, LOW);  // Turn off the LED
    digitalWrite(fanPin, LOW); // Turn off the fan
  }
}