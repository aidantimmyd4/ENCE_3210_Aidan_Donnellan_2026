// Lab 2 - Exercise 3 //
// Donnellan - 01/22/26 //
// Comment to code: This code is Version 1.2 of exercise 3 //
// Version 1.1 used Google Gemini Pro to assist, this version aims to write that code without the assistance of Google Gemini Pro //
// Some parts of code use sections of Lab 1 - Exercise 7 //
// All code referenced is commented accordingly //

// Define Macros
#define BLUE 6
#define RED 5
#define GREEN 4
#define BUTTON_1 2 // ISR pin
#define BUTTON_2 3 // ISR pin

int gArray1[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; // Filled array 1
int gArray2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1}; // Filled array 2
long result[10]; // Empty array tha gets filled when calculation is run

volatile int counter = 0; // Tracks button counter mode
volatile bool lastState = false; // detects moment button is pressed

const unsigned int debounce = 200; // Constant debounce of 200ms

void setup() {
  // Initialize Comms
  Serial.begin(9600);
  // Define LED outputs
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);

  // Define button inputs
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  // Attach interrupt to button 1 on Falling edge
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), changeMode, FALLING);
}

// ISR //
// Version 1.2 written by self, referencing Version 1.1 assisted by Google Gemini Pro //
void changeMode(){
  static unsigned int intTime = 0;
  if (millis() - intTime > debounce){
    counter++;
    if (counter > 3) counter = 1;
    lastState = true;
    intTime = millis();
  }
}

// Loop in referrence to Version 1.1 assisted by Google Gemini Pro
void loop() {
  // Intialize loop:
  if (lastState){
    updateLEDS();
    lastState = false;
  }
  // Stop and calculate if button 2 is pressed
  if (digitalRead(BUTTON_2) == HIGH && counter > 0){
    calculate();
  }
}

// This section was aided by Google Gemini Pro, mostly attempted and commented by self //
// This function is taken directly from Lab 1 - Exercise 7 //
void updateLEDS(){ // Call function for updateLEDS within main loop //
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);

  if (counter == 1) digitalWrite(RED, HIGH); // Turns on Red LED when button is pushed once
  if (counter == 2) digitalWrite(GREEN, HIGH); // Turns on Green LED when button is pushed twice
  if (counter == 3) digitalWrite(BLUE, HIGH); // Turns on Blue LED when button is pushed three times  
}

// This function taken directly from Lab 1 - Exercise 7 with some slight modifications //
void calculate(){
  // Turn off LEDs while calculating //
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);

  for (int i = 0; i < 10; i++){ // Iterate over each element in array
    if (counter == 1){
      result[i] = gArray1[i] + gArray2[i]; // button mode 1 adds elements of both arrays
    }
    if (counter == 2){
      result[i] = gArray1[i] - gArray2[i]; // button mode 2 subtracts elements of both arrays
    }
    if (counter == 3){
      result[i] = gArray1[i] * gArray2[i]; // Button mode 3 multiplies elements of boths arryas 
    }

    // Print results to serial monitor
    Serial.print("Index "); Serial.print(i);
    Serial.print(": "); Serial.println(result[i]);
  }

  // Turn on all LEDs when done calculating
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, HIGH);

  while(digitalRead(BUTTON_2) == LOW); // When button 2 is off, delay Led time by 0.5s
  delay(500);
}
