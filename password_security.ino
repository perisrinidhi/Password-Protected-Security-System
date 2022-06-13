/* PASSWORD PROTECTED SECURITY SYSTEM */

/* Components required:
1. Arduino Uno
2. 4x4 Keypad
3. 16x2 LCD
4. Piezo Buzzer */

/**********************************************/
#include<Keypad.h> //To operate keypad
#include<Wire.h> //To connect wires btw arduino & lcd
#include<LiquidCrystal.h> //To operate lcd display

LiquidCrystal lcd(13,12,11,10,9,8);

char myKey;
const byte ROWS=4;//Connect to rowpins of keypad
const byte COLS=4;//Connect to column pins of keypad
const int piezo=19;

char keys [ROWS] [COLS]={{'1','2','3'},
                         {'4','5','6'},
                         {'7','8','9'},
                         {'*','0','#'}};

byte rowPins[ROWS]={7,6,5,4};
byte colPins[COLS]={3,2,1,0};

String password="7557";
String entry="";

Keypad myKeypad=Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);//Initialize keypad

//makeKeymap(keys)initializes the internal keymap to be equal to user defined keymap
//rowPins and colPins are arduino pins to which rows & columns of keypad are connected
//ROWS & COLS are no of rows & columns of the keypad

void setup()
{
  pinMode(piezo,OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("WELCOME");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Enter Passcode");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() 
{
   myKey= myKeypad.getKey();//getKey() is used to read the values from keypad and display it on lcd 
   
   //Accepts input in the form of asterisk
   if(myKey)
   {
    if(entry.length()<4) //entry.length() returns length of the string in characters
    {
      lcd.print("*");
      entry+=myKey; 
    }
   }

   if(entry.length()==4)
   {
      delay(1500);
      if(password==entry)
      {
        lcd.setCursor(0,3);
        lcd.print("Successful Entry");
        tone(piezo,500); //tone(pin_number,frequency),This generates a noise
        delay(100);
        noTone(piezo);//Stops the generation of noise
        delay(1500);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Access Permitted");
        delay(1500);
        lcd.clear();
        lcd.setCursor(0,0);
      }

      else
      {
        lcd.setCursor(0,3);
        lcd.print("Wrong Passcode");
        tone(piezo,1000);
        delay(800);
        tone(piezo,1000);
        delay(800);
        noTone(piezo); 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Access Denied");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
      }
      delay(1500);
      entry="";
      lcd.print("Enter Passcode");
      lcd.setCursor(0,3);
      
      
   }
}
