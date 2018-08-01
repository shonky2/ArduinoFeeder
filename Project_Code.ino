#include <AccelStepper.h>
#include <LiquidCrystal.h>

#define boPin 7
#define buddyPin 8
#define stepPin 9
#define stepEn A1
#define startPin 10
#define donePin 6

LiquidCrystal lcd(12,11,5,4,3,2);
AccelStepper stepper(1,stepPin);

// int stepCount = 0; For Later Use

int boState = 0;
int buddyState = 0; 

void setup () {
  
  stepper.setMaxSpeed(800);
  stepper.disableOutputs();
  stepper.setAcceleration(200);
  pinMode(stepEn,OUTPUT);
  digitalWrite(stepEn,HIGH);
  
  pinMode(boPin,INPUT_PULLUP);
  pinMode(buddyPin,INPUT_PULLUP);
  pinMode(startPin,OUTPUT);
  pinMode(donePin,OUTPUT);
  digitalWrite(startPin,LOW);
  digitalWrite(donePin,LOW);

  lcd.begin(20, 4);
  homescreen();
  
  }


void loop() {    
  
  boState = digitalRead(boPin);
  buddyState = digitalRead(buddyPin);
  
    if (boState == LOW)  {
    feedBo();
    delay(1000);
  }

    if (buddyState == LOW) {
    feedBuddy();
    delay(1000);
  }
  
}


void feedBo() {

  digitalWrite(stepEn,LOW);
  digitalWrite(startPin,HIGH);

  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Dispensing");
  lcd.setCursor(5,1);
  lcd.print("Bo's Food");
  lcd.setCursor(7,2);
  lcd.print("Please");
  lcd.setCursor(7,3);
  lcd.print("Wait!");

  {
  stepper.move(8000);
    do  {
      stepper.run();
    } 
      while (stepper.distanceToGo() != 0);
        delay(200);     

  }  

  digitalWrite(stepEn,HIGH);
  digitalWrite(startPin,LOW);
  digitalWrite(donePin,HIGH);

  waitscreen();
  
  delay(5000);
  digitalWrite(donePin,LOW);

  homescreen();
  
  }


void feedBuddy()  {

  digitalWrite(stepEn,LOW);
  digitalWrite(startPin,HIGH);

  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Dispensing");
  lcd.setCursor(4,1);
  lcd.print("Buddy's Food");
  lcd.setCursor(7,2);
  lcd.print("Please");
  lcd.setCursor(7,3);
  lcd.print("Wait!");

  {
  stepper.move(4000);
    do  { 
      stepper.run();
    } 
      while (stepper.distanceToGo() != 0);
      delay(200);     
  
  }  

  digitalWrite(stepEn,HIGH);
  digitalWrite(startPin,LOW);
  digitalWrite(donePin,HIGH);
 

  waitscreen();
  
  delay(5000);
  digitalWrite(donePin,LOW);

  homescreen();
  
  }


void homescreen() {

  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Welcome To");
  lcd.setCursor(1,1);
  lcd.print("Hidden Creek Ranch");
  lcd.setCursor(2,2);
  lcd.print("Auto Food System");
  lcd.setCursor(0,3);
  lcd.print("Buddy      Bo's Nose");

  }


void waitscreen() {
  
  lcd.clear();
  
  lcd.setCursor(7,0);
  lcd.print("Done!");
  lcd.setCursor(4,1);
  lcd.print("Please give");
  lcd.setCursor(5,2);
  lcd.print("Him a Pet ");
  lcd.setCursor(6,3);
  lcd.print("From Me");

  }

