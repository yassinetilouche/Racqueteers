//Code for reading RFID Tag/Card and giving access or not to it
//SurtrTech Youtube channel 

#include <LiquidCrystal_I2C.h>
#include <RFID.h> //RFID library

#define SS_PIN 10 //SDA pin
#define RST_PIN 9 //Reset pin
#define I2C_ADDR 0x27 //I2c Address
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

int serNum[5];
int cards[][5] = {
   {35,231,84,0,144},{122, 223, 114, 130, 85} // Authorized Card ID, You can add others if you want after the last comma like {x1,x2,x3,x4,x5},{y1,y2,y3,y4,y5},
    };
bool access = false;

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

RFID rfid(SS_PIN, RST_PIN); 


void setup() {
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();
  lcd.print("Hello"); //Showing hello on the screen of 3s
  delay(3000);
  lcd.clear();
  lcd.print("Please place");
  lcd.setCursor(0,1);
  lcd.print("your card");
  }



void loop() { 
    if (rfid.isCard()) { //Waiting for a Tag/Card to be near the RFID antenna
        if (rfid.readCardSerial()) { //If there is a RFID card
          lcd.clear(); //Clearing lcd screen from previous value
              
              for(int x = 0; x < sizeof(cards); x++){ 
                    for(int i = 0; i < sizeof(rfid.serNum); i++ ){ //These two loops are for comparing the card ID with authorized ID's we set before
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false; //If one number is different from the authorized card, access become false
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }
        
             }

             
             delay(300);
             if(access){ //If acces is given do the following instructions, I just show a simple message, you can turn on a LED
              lcd.clear();// Or activate a relay to unlock a real door or something...
              lcd.setCursor(0,0);
              lcd.print("Access granted");

 } 
  else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Access denied");
  }
              delay(5000);//After 5s we show the first message again to be on standby
              lcd.clear();
              lcd.print("Please place");
              lcd.setCursor(0,1);
              lcd.print("your card");
             }
          }
