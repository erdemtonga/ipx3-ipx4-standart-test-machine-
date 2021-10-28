#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 16, 2);

Stepper myStepper1(200, 2, 3, 4, 5);
Stepper myStepper2(200, 10, 11, 12, 13);

extern volatile unsigned long timer0_millis;
unsigned long zaman = 0;
unsigned long saat  = 0;
unsigned long dakika = 0;
unsigned long saniye = 0;
int butondurumu = 0;
int butondurumu1 = 0;
int buton = 7;
int buton1 = 6;


void setMillis(unsigned long new_millis)
{
  
  uint8_t oldSREG = SREG;
 
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
 
}



void setup() {

  lcd.init( );
  lcd.backlight();
  myStepper1.setSpeed(100);
  myStepper2.setSpeed(100);
 
  Serial.begin(9600);
  pinMode(A0,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(buton,INPUT);
  pinMode(buton1,INPUT);
 
  Serial.println("Connection OK");
  
}


void loop() {
  butondurumu = digitalRead(buton);
  butondurumu1 = digitalRead(buton1);
   

     if((butondurumu1 == LOW) && (butondurumu == LOW)){
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(A0,LOW);
    lcd.setCursor(0, 0);
    lcd.print("IPX3 TEST PASIF");
    lcd.setCursor(0, 1);
    lcd.print("IPX4 TEST PASIF");
         
    }
    
    
    
  if(butondurumu == HIGH){
   
  
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
   

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("IPX3 Test Aktif");
    
    zaman = millis();
  
    
    saat = zaman / 3600000;
    dakika = ((zaman / 60000) - (saat * 60));
    saniye = ((zaman / 1000) - (saat * 3600 + dakika * 60));

    Serial.print("  Zaman ");
    Serial.print(saat);
    Serial.print(" h ");
    Serial.print(dakika);
    Serial.print(" m ");
    Serial.print(saniye);
    Serial.println(" s ");
    lcd.setCursor(0,1);
    lcd.print(dakika);
    lcd.setCursor(1,1);
    lcd.print("dk");
    lcd.setCursor(3,1);
    lcd.print(saniye);
    lcd.setCursor(5,1);
    lcd.print("sn");
    
    if (dakika < 1 ) {
      digitalWrite(A0,HIGH);
      
      for (int s = 0; s < 132; s++) {
      myStepper1.step(1);
      myStepper2.step(1);
      
       
     
    }
    for (int s = 0; s < 132; s++) {
      myStepper1.step(-1);
      myStepper2.step(1);
      
      
    }
      }
      else
      digitalWrite(A0,LOW);
     
      
       
   }

     


 
    
    
  else if(butondurumu1 == HIGH){
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("IPX4 Test Aktif");
    
    zaman = millis();
  
    
    saat = zaman / 3600000;
    dakika = ((zaman / 60000) - (saat * 60));
    saniye = ((zaman / 1000) - (saat * 3600 + dakika * 60));

    Serial.print("  Zaman ");
    Serial.print(saat);
    Serial.print(" h ");
    Serial.print(dakika);
    Serial.print(" m ");
    Serial.print(saniye);
    Serial.println(" s ");
    lcd.setCursor(0,1);
    lcd.print(dakika);
    lcd.setCursor(1,1);
    lcd.print("dk");
    lcd.setCursor(3,1);
    lcd.print(saniye);
    lcd.setCursor(5,1);
    lcd.print("sn");
    if (dakika <1 ) {
      digitalWrite(A0,HIGH);
     
      for (int s = 0; s < 200; s++) {
      myStepper1.step(1);
      myStepper2.step(1);
     
     
    }
    for (int s = 0; s < 200; s++) {
      myStepper1.step(-1);
      myStepper2.step(1);
      
    }
    }
    else 
    digitalWrite(A0,LOW);
    

    }
    else  {

       digitalWrite(8,LOW);
       digitalWrite(9,LOW);
       digitalWrite(A0,LOW);
       
       
         setMillis(0);
       
     
   
    
    }
    
    

}





 


  
