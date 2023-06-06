#include <NewPing.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int ledPin1 =(7); // Add the onboard LED on pin 13.
int ledPin2 =(8);
int ledPin3 =(13);
int trigPin = (10); // Add the Trig pin on pin 10.
int echoPin = (9); // Add the ECHO pin on pin 9.
int duration, distance; // Add types 'duration' and 'distance'.
void setup()
{
     Serial.begin(9600);
lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("Welcome to ");   
lcd.setCursor(0, 1);
lcd.print("Racqueteers Club");
pinMode (ledPin1, OUTPUT); // The LED must be controlled by Arduino, it means it is an output type.
pinMode (ledPin2, OUTPUT); // The LED must be controlled by Arduino, it means it is an output type.
pinMode (ledPin3, OUTPUT); // The LED must be controlled by Arduino, it means it is an output type.
pinMode (trigPin, OUTPUT);// Same as above, the TRIG pin will send the ultrasonic wave.
pinMode (echoPin, INPUT); // The ECHO pin will recieve the rebounded wave, so it must be an input type.
}
void loop()
{
digitalWrite (ledPin1, LOW); // Here, LOW means off and HIGH means on.
digitalWrite (ledPin2, LOW); // Here, LOW means off and HIGH means on.
digitalWrite (ledPin3, LOW); // Here, LOW means off and HIGH means on.
digitalWrite (trigPin, HIGH);
delay(50);
digitalWrite (trigPin, LOW);
duration=pulseIn(echoPin,HIGH);
distance=(duration/2)/29.1;

if(distance <=20&& distance >12)
{
digitalWrite (ledPin1, HIGH);//yellow
digitalWrite (ledPin2, LOW);
digitalWrite (ledPin3, LOW);
lcd.setCursor(0, 0);
lcd.clear();
lcd.print("La voiture est");   
lcd.setCursor(0, 1);
lcd.print("trop loin");
Serial.write('0');
delay(50);
}

if(distance <=12 && distance >8)
{digitalWrite (ledPin1, LOW);
digitalWrite (ledPin2, HIGH); //green
digitalWrite (ledPin3, LOW);
lcd.clear();
lcd.print("Parfait !");   
Serial.write('1');
delay(50);
}
if(distance <=6&& distance >=0)
{digitalWrite (ledPin1, LOW);
digitalWrite (ledPin2, LOW);
digitalWrite (ledPin3, HIGH);//red
lcd.clear();
lcd.print("La voiture est");   
lcd.setCursor(0, 1);
lcd.print("trop proche");
Serial.write('0');
Serial.write('2');
delay(50);}
if (distance>20){
 lcd.clear();
 lcd.setCursor(0, 0);
lcd.print("Welcome to ");   
lcd.setCursor(0, 1);
lcd.print("Racqueteers Club");
}



}
