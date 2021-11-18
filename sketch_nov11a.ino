// -------- LCD LIBS --------------------------
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
// --------------------------------------------

#define bGreen 7
#define bYellow 6
#define bRed 5
#define lGreen 4
#define lYellow 3
#define lRed 2

String connectionReceived = "A";
bool lr = false, 
ly = false, 
lg = false,
br = false,
by = false,
bg = false;

void setup()
{
  lcd.init(); // lcd init
  lcd.setBacklight(HIGH); // lcd led on
  Serial.begin(9600); // serial activate with baudrate 9600
//  pin declarations
//  LEDs
  pinMode(lRed, OUTPUT);
  pinMode(lYellow, OUTPUT);
  pinMode(lGreen, OUTPUT);
//  Buttons
  pinMode(bRed, INPUT);
  pinMode(bYellow, INPUT);
  pinMode(bGreen, INPUT);
}

void loop()
{
  // ASCENDER OS LEDS
  if(lr){ digitalWrite(lRed, HIGH); } else { digitalWrite(lRed, LOW); }
  if(ly){ digitalWrite(lYellow, HIGH); } else { digitalWrite(lYellow, LOW); }
  if(lg){ digitalWrite(lGreen, HIGH); } else { digitalWrite(lGreen, LOW); }

  // RECONHECE QUANDO UM BOTAO É APERTADO
  if(digitalRead(bRed)){ br = true; }
  if(digitalRead(bYellow)){ by = true; }
  if(digitalRead(bGreen)){ bg = true; }
  
  lcd.setCursor(0,0); lcd.print("send: "); 
  if(br){ Serial.print('R'); lcd.print('R'); br = false; }
  if(by){ Serial.print('Y'); lcd.print('Y'); by = false; }
  if(bg){ Serial.print('G'); lcd.print('G'); bg = false; }
  Serial.print('\n');

  if (Serial.available() > 0) { // verifica se a entrada serial esta disponivel
    connectionReceived = Serial.read(); // faz a leitura da porta serial atribuindo pra string connectionReceived
  }
  if(connectionReceived == "65"){ connectionReceived = 'A'; lr = false; ly = false; lg = false; }
  if(connectionReceived == "66"){ connectionReceived = 'B'; lr = true; ly = false; lg = false; }
  if(connectionReceived == "67"){ connectionReceived = 'C'; lr = false; ly = true; lg = false; }
  if(connectionReceived == "68"){ connectionReceived = 'D'; lr = true; ly = true; lg = false; }
  if(connectionReceived == "69"){ connectionReceived = 'E'; lr = false; ly = false; lg = true; }
  if(connectionReceived == "70"){ connectionReceived = 'F'; lr = true; ly = false; lg = true; }
  if(connectionReceived == "71"){ connectionReceived = 'G'; lr = false; ly = true; lg = true; }
  if(connectionReceived == "72"){ connectionReceived = 'H'; lr = true; ly = true; lg = true; } 
  
  lcd.setCursor(5,1); lcd.print(lr); lcd.print(ly); lcd.print(lg); // lcd print
  
}

// RECONHECE SE ALGUM LED ESTA LIGADO
//  if(!lg && !ly && !lr){ connection = 'A'; }
//  if(!lg && !ly && lr){ connection = 'B'; }
//  if(!lg && ly && !lr){ connection = 'C'; }
//  if(!lg && ly && lr){ connection = 'D'; }
//  if(lg && !ly && !lr){ connection = 'E'; }
//  if(lg && !ly && lr){ connection = 'F'; }
//  if(lg && ly && !lr){ connection = 'G'; }
//  if(lg && ly && lr){ connection = 'H'; }
