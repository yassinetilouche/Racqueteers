/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
  This example code is in the public domain.
 */
 
// Pin 2-8 is connected to the 7 segments of the display.
int data;
int decimal,unite;
int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 8;
int pinG = 7;
int D1 = 9;
int D2 = 10;
//int D3 = 11;
//int D4 = 12;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pins as outputs.
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
 // pinMode(D3, OUTPUT);  
 //pinMode(D4, OUTPUT);  
  //analogWrite(PIN_LED1, 0);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  
 // digitalWrite(D1, HIGH);
  //digitalWrite(D2, HIGH);
  //digitalWrite(D3, LOW);
  //digitalWrite(D4, LOW); 
  //0
  if (Serial.available()){     
    //Si un message a été reçu  faire ceci
     data=Serial.read();
    //decimal=((data / 10) % 10);
    //unite=data / 10;
    Serial.write(data);
    //Serial.write(decimal);
    
     // controler la lampe 1 reliée à la broche 13
     //récuperer le caractère reçu
     if(data=='0') //si le caractère lu est égale à 1
    {digitalWrite(D2, HIGH);
     digitalWrite(D1, LOW);
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, HIGH);   
  // delay(2000)   ;  // wait for a second
     }else if(data=='1') //si le caractère lu est égale à 0

     {
  digitalWrite(D1, LOW);
  digitalWrite(D2, HIGH);
  //digitalWrite(D3, LOW);
 // digitalWrite(D4, LOW); 
  //1
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);
   // delay(2000);
     }
    /*else if(data=='15') //si le caractère lu est égale à 0

     {
          digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);
      
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW);
  //digitalWrite(D3, LOW);
 // digitalWrite(D4, LOW); 
  //1
      digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW); 
      delay(10);
  
   // delay(2000);
     }*/
    else if(data=='2')
    {
   // wait for a second
  
 // digitalWrite(D1, LOW);
  //digitalWrite(D2, LOW);
  //digitalWrite(D3, HIGH);
  //digitalWrite(D4, LOW); 
  //2
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, HIGH);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, LOW);     
  //delay(2000);               // wait for a second
  }
  //digitalWrite(D1, LOW);
 // digitalWrite(D2, LOW);
  //digitalWrite(D3, LOW);
  //digitalWrite(D4, HIGH); 
  //3
  else if(data=='3')
    {
  digitalWrite(pinA,LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, LOW);     
 // delay(1000);               // wait for a second
  } else if(data=='4')
  {//4
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
    //delay(1000);    // wait for a second
  } else if(data=='5')
  {
  //5
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
  //delay(1000);               // wait for a second
  } else if(data=='6')
  {
  //6
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, HIGH);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
  //delay(1000);               // wait for a second
  } else if(data=='7')
  {
  //7
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);     
  //delay(1000);               // wait for a second
  } else if(data=='8')
  {
  //8
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, LOW);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
  //delay(1000);               // wait for a second
  } else if(data=='9')
  {
  //9
  digitalWrite(pinA, LOW);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, LOW);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, LOW);   
  digitalWrite(pinG, LOW);     
  //delay(1000);   */            // wait for a second
  }
  }}
