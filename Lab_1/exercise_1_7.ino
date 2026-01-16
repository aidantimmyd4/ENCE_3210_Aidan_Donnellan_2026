// Lab 1 - Exercise 7 //
// Donnellan - 01/15/26 //
// Google Gemini Pro was used extensively in this exercise, sections used by 
// Google gemini pro will be commented accordingly //
// Code was simulated in TinkerCAD //

// Define Macros
#define BLUE 2
#define GREEN 3
#define RED 4
#define BUTTON_1 5
#define BUTTON_2 6

// Create programmer defined arrays
int array1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int array2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
long result[10]; // Gemini suggested this to prevent multiplication overflow

int butCounter = 0; // tracks mode, 0 = None, 1 = add, 2 = sub, 3 = multiply
bool lastState = LOW; // Detects the moment the button is pressed

void setup() {
  // Initialize comms
  Serial.begin(9600);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
}

void loop() {
  // This section was written extensively by Google Gemini Pro, commented by self //
  bool currentState = digitalRead(BUTTON_1); // Reads current state of push button 1

  // Button Logic //
  // Checks if button is HIGH but was low previously  //
  // Prevents counter from skipping if button is held down //
  if (currentState == HIGH && lastState == LOW){
    butCounter++;
    if (butCounter > 3) butCounter = 1; // Cycles back to addition state
    updateLEDS(); // Resets LED back to addition color
    delay(200); // Delays 200ms between switch
  }
  lastState = currentState; // Update for next loop

  // Execution Trigger //
  // If second button is pressed while operation is selected, run math //
  if (digitalRead(BUTTON_2) == HIGH && butCounter > 0){
    calculate();
  }
}

// This section was aided by Google Gemini Pro, mostly attempted and commented by self //
void updateLEDS(){ // Call function for updateLEDS within main loop //
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);

  if (butCounter == 1) digitalWrite(RED, HIGH); // Turns on Red LED when button is pushed once
  if (butCounter == 2) digitalWrite(GREEN, HIGH); // Turns on Green LED when button is pushed twice
  if (butCounter == 3) digitalWrite(BLUE, HIGH); // Turns on Blue LED when button is pushed three times  
}

// This section was written primarily by Google Gemini Pro, commented by self //
void calculate(){ // Call function for calculate in main loop //
  // Turn of LEDs while calculating //
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);

  // Loop through each index of array and calculate according to which operation was selected //
  for (int i = 0; i < 10; i++){
    if (butCounter == 1){
      result[i] = (long)array1[i] + array2[i]; // performs addition based on one button click //
    } else if (butCounter == 2){
      result[i] = (long)array1[i] - array2[i]; // performs subtraction based on two button clicks //
    } else if (butCounter == 3){
      result[i] = (long)array1[i] * array2[i]; // performs multiplication based on three button clicks //
    }

    // Output the result of specific index
    Serial.print("Index "; Serial.print(i); 
    Serial.print(": "); Serial.println(results[i]);
  }

  // Turn on all LEDs when finished
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, HIGH);

  // Waits for user to let go over button so it doesn't run twice
  while(digitalRead(BUTTON_2) == HIGH);
  delay(200);
}
