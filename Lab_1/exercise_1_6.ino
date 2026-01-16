// Lab 1 - Exercise 6 //
// Donnellan - 01/15/26 //
// Google Gemini Pro used extensively to help write this code, sections will be commented accordingly //
// Code was simulated in TinkerCAD //

// Define Macros
#define BLUE 2
#define GREEN 3
#define RED 4
#define BUTTON 5

// Define global variables // 
// This section was written by Google Gemini Pro //
bool isRunning = false; // Sees if LED sequence is active or off
int lastState = LOW; // stores previous state

void setup() {
  // Initialize Comms
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON, INPUT);
}

// Helper Function: Written by Google Gemini Pro, used to set LED states //
void setLEDs(int r, int g, int b){
  digitalWrite(RED, r);
  digitalWrite(GREEN, g);
  digitalWrite(BLUE, b);
}

// Main loop, this section was primarily written by Google Gemini Pro with modifications from programmer //
void loop() {
  // Read if BUTTON is HIGH or LOW
  int currentState = digitalRead(BUTTON);

  // Toggle Logic
  if (currentState == HIGH && lastState == LOW){
    isRunning = !isRunning; // Flips state, if HIGH, goes to LOW
    if (!isRunning) setLEDs(0, 0, 0); // if button is pressed to LOW, all LEDs turn off

    delay(250); // debounce delay
  }

  // Save current button state
  lastState = currentState;

  // LED Sequence Execution // 
  if (isRunning){
    setLEDs(1, 0, 0); if(checkStop()) return; // R
    setLEDs(1, 1, 0); if(checkStop()) return; // RG
    setLEDs(1, 1, 1); if(checkStop()) return; // RGB
    setLEDs(0, 1, 1); if(checkStop()) return; // GB
    setLEDs(0, 0, 1); if(checkStop()) return; // B
    setLEDs(1, 0, 1); if(checkStop()) return; // RB
  }
}

// Helper Interrupt //
// If button is pressed, whole thing stops //
// This section was written by Google Gemini Pro as it mentioned this function works better than a simple delay //
bool checkStop(){
  for(int i = 0; i < 50; i++){
    int bState = digitalRead(BUTTON);
    // Detect if button is pressed mid LED sequence //
    if(bState == HIGH && lastState == LOW){
      isRunning = false;
      return true;
    }
    lastButtonState = bState;
    delay(10);
  }
  return false;
}
