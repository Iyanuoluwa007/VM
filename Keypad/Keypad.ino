#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// connect the pins from right to left to pin 2, 3, 4, 5, 6, 7, 8, 9
byte rowPins[ROWS] = {34,35,32,33};  //connect to the row pinouts of the keypad
byte colPins[COLS] = {14,27,26,25};  //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  char key = keypad.getKey();
    // just print the pressed key
   if (key){
    Serial.print("Key ");
    Serial.print(key);
    Serial.println(" is pressed");
    //delay(1000);
  } 
/*  
  // this checks if 4 is pressed, then do something. Here  we print the text but you can control something.
  if (key =='4'){
    // do something here is 4 is pressed
    Serial.println("Key 4 is pressed -> Action");
  }
  */
}