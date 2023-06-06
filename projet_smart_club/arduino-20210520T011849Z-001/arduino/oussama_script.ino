// include the library code:
#include <LiquidCrystal.h>
char data;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
   Serial.begin(9600);
    lcd.begin(16, 2);

  lcd.print("Welcome !");
  
}

void loop() 
{
        lcd.clear();

  if(Serial.available())
  {
    data=Serial.read();
    if(data=='1')
    {
      lcd.print("entrez");
    delay(3000);
    lcd.clear();
      Serial.write(data);
    }
    if(data=='2')
    {
    lcd.print("pas de places");
    
    delay(3000);
    lcd.clear();
    }
      
  }
  else 
    lcd.print("Racqueteers Club");
    delay(3000);
    lcd.clear();
}
 
