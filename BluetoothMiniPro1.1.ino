#include <SoftwareSerial.h>

#define rxPin 0 //define rx data pin
#define txPin 1 //define tx data pin
#define CON_SEC_SLOUCH_NUM 4

// Declare the pins for the Button and the LED
const short buttonPin = 12;
const short RED_LED = 13;
const short GREEN_LED = 6;
const short WRITE_LED = 4;
//create instance of SoftwareSerial
SoftwareSerial bluetooth(rxPin, txPin);

void setup() {
  // Define pin #12 as input and activate the internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  // Define pin #13 as output, for the LED
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  //Setup usb serial connection to computer
  Serial.begin(9600);    //Start hardware Serial

  //Setupt Bluetooth serial connection to android
  bluetooth.begin(9600); //Start software Serial
}

short slouchCounter = 0;
float slouchValues[CON_SEC_SLOUCH_NUM];

void loop() {
  // Read the value of the input. It can either be 1 or 0
  
  if (digitalRead(buttonPin) == LOW) { //Button Pressed
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    slouchValues[slouchCounter] = badPosture();
    slouchCounter++;
    if(slouchCounter == CON_SEC_SLOUCH_NUM){
      for(int i = 0; i < slouchCounter; i++){
        Serial.print(slouchValues[i]);
        Serial.print(',');
      }
      Serial.print("#");
      slouchReset();
    }
  } else { //Button not pressed.
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      //Turn off LED
      //byte index = 0;
  }
  bluetooth.println("bt"); 
  if(bluetooth.available() > 0){
    checkForBTData(bluetooth.read());
  }
      /*
  if (bluetooth.available() > 0) {
  char inChar;
    if (index < 63) {
      inChar = bluetooth.read(); //Read a char
      inData[index] = inChar; //Store char in inData string
      index++;
      if (index == 63) {
        inData[index] = '#'; //Null terminate the string
      }
    }
    if (index < 63) {
      inData[index] = '#';
    }
    for (int i = 0; i < 64; i++){
      Serial.print(inData[i]);
    }
    Serial.print("#");
    delay(2000);

    for (byte i = 0; i < 2; i++) {
      switch (inChar) {
        case '*':
          //Serial.print("You sent a star!\n#");
          break;
        case 'm':
          // Serial.print("You sent an m!\n#");
          break;
        default:
          Serial.print("You sent a ... ");
          Serial.print(inData[i]);
          Serial.print("\n#");
          delay(1000);
  
          break;
      }
    }
  }*/
      delay(1000);    
}

void checkForBTData(char inData){
  switch (inData){
    case '*':
      Serial.print("*#");
      break;
    case 'c':
      Serial.print("c#");
      break;
    default:
      break;
  }
}

void slouchReset(){
  slouchCounter = 0;
  slouchValues[4] = {0};
}

float goodPosture(){
  return (float)random(650,700) / 10.0;
}

float badPosture(){
  return (float)random(550, 649) / 10.0;
}

