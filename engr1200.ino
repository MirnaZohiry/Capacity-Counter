#include <IRremote.h>
#include <LiquidCrystal.h>

int sound=30;
int led=32;

long int x=0;

LiquidCrystal lcd(12, 11, 28, 26, 24, 22);

int RECV_PIN = 40;

IRrecv irrecv(RECV_PIN);

decode_results results;

int counter=0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  lcd.begin(16, 2);
  pinMode(led,OUTPUT);
  pinMode(sound,OUTPUT);
}

void loop() {
  delay(500);
  lcd.clear();
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    x=results.value;
    if(results.value==3855596927)
    {
      counter++;
      lcd.setCursor(0,0);
      lcd.print("   Library has   ");
      lcd.setCursor(4,1);
      lcd.print(counter);
      lcd.setCursor(8,1);
      lcd.print("people");
      if(counter>10)
      {
        lcd.clear();
        lcd.print(" library is over");
        lcd.setCursor(4,1);
        lcd.print("Capacity");
        digitalWrite(led,HIGH);
        digitalWrite(sound,HIGH);
      }
    }
      if(results.value==2747854299)
    {
      if(counter>0)
      {
      counter--;
      if(counter>10)
      {
        lcd.clear();
        lcd.print(" library is over");
        lcd.setCursor(4,1);
        lcd.print("Capacity");
        digitalWrite(led,HIGH);
        digitalWrite(sound,HIGH);
      }
      if(counter<=10)
      {
        digitalWrite(led,LOW);
        digitalWrite(sound,LOW);
        lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("   Library has   ");
      lcd.setCursor(4,1);
      lcd.print(counter);
      lcd.setCursor(8,1);
      lcd.print("people");
      }
      }
      if(counter==0)
      {
        lcd.clear();
        lcd.print("Library is empty");
      }
      
    }
   
    
    irrecv.resume(); // Receive the next value
  }
}
