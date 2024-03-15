#include <Wire.h>
#include "rgb_lcd.h"
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 4

rgb_lcd lcd;


char Temp = 0;
char Humi = 0;
const int LEDA = 18;
const int LEDB = 2;
const int TRIG_PIN = 5;
const int ECHO_PIN = 17;
const int colorR = 225;
const int colorG = 0;
const int colorB = 0;
long duration;
float cms, inches;

void setup() {
  Serial.begin(115200);
  pinMode(LEDA, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.begin(16, 2);

  lcd.setRGB(colorR, colorG, colorB);

  delay(1000);
}

void loop() {

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  //lcd.setCursor(0, 1);

  lcd.setCursor(0, 0);
  lcd.print("Humi: ");
  lcd.print(DHT.humidity);

  delay(100);

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  cms = (duration/2) / 29.1;
  inches = (duration/2) / 74;

  Serial.print("UltraSonic Sensor\n");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cms);
  Serial.print("cm, ");
  Serial.println();
  delay(1000);

  DHT.read(DHT11_PIN);
  Serial.print("Temp: ");
  Temp = DHT.temperature;
  Serial.print(DHT.temperature);
  Serial.print("\nHumi: ");
  Serial.println(DHT.humidity);
  Humi = DHT.humidity;
  delay(1000);
  
  if(Temp > 21){
    lcd.setCursor(0, 1);
    lcd.print("Temp too high");
    //lcd.setCursor(0, 1);
    digitalWrite(LEDA, HIGH);
  }
  else{
    lcd.setCursor(0, 1);
    lcd.print(Temp);
    //lcd.setCursor(0, 1);
    lcd.print("Temp is okay");
    digitalWrite(LEDA, LOW);
  }

  if(Humi > 80){
    lcd.setCursor(0, 0);
    lcd.print("Humi is  high");
    digitalWrite(LEDB, HIGH);
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print(Humi);
    lcd.print("Humi is okay");
    digitalWrite(LEDB, LOW);
  }
}
