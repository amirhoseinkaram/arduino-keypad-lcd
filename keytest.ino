#include <LiquidCrystal.h>
#include <Keypad.h>
//keypad type definition




const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS]=
{
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {23, 25, 27, 29};//connect to the row R1-R4 pinouts of the keypad
byte colPins[COLS] = {31, 33, 35, 37};//connect to the COLS C1-C4 pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );




char KEY[4] = {'5','5','8','8'};//default secret key
char attemp[4] = {0,0,0,0};





LiquidCrystal lcd (47,51,50,52,49,48,53);




int p=6;
int z=0;
char greenled = 10;
char redled = 11;




void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode (greenled,OUTPUT);
  pinMode (redled,OUTPUT);
  lcd.print("ENTER PASS:");
}





void ledaccept()
{
    lcd.clear();
    digitalWrite(greenled,HIGH);
    lcd.print("ACCEPT PASSWORD");
    delay(2000);
    lcd.clear();
    digitalWrite(greenled,LOW);
    lcd.print("ENTER PASS:");
}





void ledreject()
{
    lcd.clear();
    digitalWrite(redled,HIGH);
    lcd.print("REJECT PASSWORD");
    delay(2000);
    digitalWrite(redled,LOW);
    lcd.clear();
    lcd.print("ENTER PASS:");
}





void correctKEY()//do this if the correct KEY is entered
{
  Serial.println(" رمز صحیح است :)");
  ledaccept();
  
}





void incorrectKEY()//do this if the incorrect KEY is entered
{
  
  Serial.println("رمز غلط است :(");
  ledreject();
    
}






void checkKEY()
{
  int correct=0;
  int i;

  
  for ( i = 0; i<4; i++)
  {
    if (attemp[i]==KEY[i])
    {
      correct++;
    }
  }
  if (correct==4)
  {
    correctKEY();
    Serial.println();
  }
  else
  {
    incorrectKEY();
   
  }
  for (int zz=0; zz<4; zz++) //clear previous key input
  {
    attemp[zz]=0;
  }
}





void readKeypad()
{   
  
  char key = keypad.getKey();

  
  if (key != NO_KEY)
  { 

    switch(key)
    {
    case '#':
     z=0;
     Serial.println();
     Serial.println("تلاش مجدد!");
     break;


     
    case '*':
     delay(100); //added debounce
     checkKEY();
     z=0;
     break;


     
     default:  //default yano dar halat koli :)
     Serial.print(key);
     lcd.setCursor(p,1);
     lcd.print("*");
////////////////////////////LCD default     
     
       attemp[z]=key;
       z++;
       
       if (z == 4){
     
      checkKEY();
      z = 0;
      p=5;   //set cursor LCD
      
      
     }
      
    }
    
    p++;     // in loop if (key != NO_KEY)
     
   
  }

} 

void loop() {
  // put your main code here, to run repeatedly
  readKeypad();
}
