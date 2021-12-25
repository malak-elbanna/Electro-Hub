#include <LiquidCrystal.h>

//LCD
const int rs = 7, en = 8, d4 = 12, d5 = 11, d6 = 10, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//LEDs
const int FanOn_Led1= 2;
const int Motion_led2 = 3;
const int NightLight_led3 = 4;

//Ultrasonic Sensor
const int triger=6;
const int echo=5;
long duration;
int distance; 
int state1 = 0; 
int state2 = 0; 
int LDR_Status;
int TempSensor_Val;


//LDR and Temperature Sensor
const int LDR_Pin = A0;
const int TempSensor_Pin = A1;

char Incoming_value = 0;


void setup() {

  Serial.begin(9600);

//Introduction Display message
  lcd.begin(16, 2);
  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print("  Welcome all!  ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print("     We are     ");
  lcd.setCursor(0,1);
  lcd.print(" Hyper-Energized ");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Present to you ");
  lcd.setCursor(0,1);
  lcd.print("  Electro-Hub  ");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  To Generate  ");
  lcd.setCursor(0,1);
  lcd.print("   and Save    ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Electric Energy ");
  delay(3000);
  lcd.clear();

 //Pins Setup
  pinMode(LDR_Pin, INPUT);
  pinMode(TempSensor_Pin, INPUT);
  pinMode(FanOn_Led1, OUTPUT);
  pinMode(Motion_led2, OUTPUT);
  pinMode(NightLight_led3, OUTPUT);
  pinMode (triger, OUTPUT);
  pinMode (echo, INPUT);
}


void loop() {


//Ultrasonic Sensor Reading
  digitalWrite (triger,LOW);
  delayMicroseconds (2);

  digitalWrite (triger, HIGH);
  delayMicroseconds (10);
  digitalWrite (triger, LOW);

  duration = pulseIn (echo, HIGH);
  distance = duration/58;

 //Bluetooth Reading
 
  Incoming_value = Serial.read();  

 //LDR Reading

 LDR_Status = analogRead(LDR_Pin);

  TempSensor_Val = analogRead(TempSensor_Pin);
  float mv = ( TempSensor_Val/1024.0)*5000;
  float cel = mv/10;
  

  
  //********************************Fan******************************************//
  
    if(Incoming_value == '1' || cel > 50) 
  {
    digitalWrite(FanOn_Led1,HIGH);
    
    }

     else if(Incoming_value == '4') 
  {
    digitalWrite(FanOn_Led1,LOW);
    
    }

        
//********************************Indoor Light***********************************//

     if( Incoming_value == '2' || distance <= 15 ) 
     {
    digitalWrite(Motion_led2,HIGH);
    state1 = 1 ;

     }

     else if( Incoming_value == '5' ) 
    {
    digitalWrite(Motion_led2,LOW);
    state1 = 0 ;
    }

     if( state1 == 1 )
     {  
    lcd.setCursor(0,0);
    lcd.print("Indoor Light ON ");
     }

    else if( state1 == 0 )
    {
    lcd.setCursor(0,0);
    lcd.print("Indoor Light OFF");
    }
    
//********************************Outdoor Light***********************************//




     if (LDR_Status <= 20){

       digitalWrite(NightLight_led3,HIGH);
       state2 = 1 ;  
       }


    else if (LDR_Status > 20)
       {
      digitalWrite(NightLight_led3,LOW);
      state2 = 0 ;
      }


    if( state2 == 1 )
     {  
    lcd.setCursor(0,1);
    lcd.print("Outdoor Light ON ");
     }

    else if( state2 == 0 )
    {
    lcd.setCursor(0,1);
    lcd.print("OutdoorLight OFF");
    }  
       }
