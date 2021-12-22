//Aayushi Sharma
//sharma.aayus@northeastern.edu
//Novemeber 9, 2021
//Thermostat

#include <LiquidCrystal.h>                  //the liquid crystal library contains commands for printing to the display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    // tell the RedBoard what pins are connected to the display
int contrast_level= 90;

const int redLED = 8;
const int blueLED = 7;
//potentiometer pin
const int potPin = A1;  
//variable to read potientimeter input                    
int potSensorRead = analogRead(potPin) * 0.004882813;
float potDegreesC = (potSensorRead - 0.5) * 100.0;       //convert the voltage to a temperature in degrees Celsius
float potDegreesF = potDegreesC * (9.0 / 5.0) + 32.0; //convert the voltage to a temperature in degrees 

  //the voltage measured from the TMP36
float voltage = analogRead(A0) * 0.004882813;   //convert the analog reading, which varies from 0 to 1023, back to a voltage value from 0-5 volts

float degreesC = (voltage - 0.5) * 100.0;       //convert the voltage to a temperature in degrees Celsius
float degreesF = degreesC * (9.0 / 5.0) + 32.0; //convert the voltage to a temperature in degrees Fahrenheit

  
void setup() {
  analogWrite(9, contrast_level);
  lcd.begin(16, 2);                         //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                              //clear the display
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(9,OUTPUT); 
  
}

void loop() {
//welcome message funtion
 welcome();
  
for (int i = 0; i<1000; i++){     //for 1 second
  //if less than potientiometer && less than potentiometer - 1
  if ((degreesF < potDegreesF) && (degreesF < potDegreesF - 1)){
  heat();
  }
 
  //if else greater than potientiomenter reading && greater than poteniometer + 1
  if ((degreesF > potDegreesF) && (degreesF > potDegreesF + 1)){
  digitalWrite(blueLED, HIGH);
  cool();
  }
  
  //else turn off and refresh
  else{
  refresh();
  }
  
}
lcd.clear();
delay(1000);//delay for 1 second between each reading (this makes the display less noisy)
}



void welcome(){
   lcd.setCursor(0, 0); 
  lcd.print("Welcome to the");
  lcd.setCursor(0, 1); 
  lcd.print("Thermostat!"); // welcome message
  
  delay(1000);

  lcd.clear();


  lcd.setCursor(0, 0);                      //set the cursor to the lower left position
  lcd.print("Degrees F: ");                 //Print a label for the data
  lcd.print(degreesF);                      //print the degrees Fahrenheit

  
  //potientiometer reading
  lcd.setCursor(0,1);
  lcd.print("Set to: ");
  lcd.print(potDegreesF);

  delay(1000); 
  lcd.clear();
}

//heat function
void heat(){
  digitalWrite(redLED, HIGH);
  
  lcd.setCursor(0,0);
  lcd.print("HEAT ON!");
  lcd.setCursor(0,1);
  lcd.print(potDegreesF);
}

//cool function
void cool(){
  lcd.setCursor(0,0);
  lcd.print("COOL ON!");
  lcd.setCursor(0,1);
  lcd.print(potDegreesF);
}

//refresh funtion 
void refresh(){
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
  lcd.clear();
}
