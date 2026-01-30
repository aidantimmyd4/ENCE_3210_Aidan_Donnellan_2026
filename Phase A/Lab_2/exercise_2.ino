// Lab 2 - Exercise 2 //
// Donnellan - 01/19/26 //
// Extension of Lab 1 - Exercise 6 //
// Some code assisted by Google Gemini Pro, code is commented accordingly //
// Simulated on Tinkercad //

// Define Macros
#define BLUE 3
#define GREEN 4
#define RED 5
#define BUTTON 2

// Define global variables // 
// This section was written by Google Gemini Pro //
volatile bool isRunning = false; // sees if loop is active or turned off
volatile unsigned long int_time = 0; // Interrupt time
const unsigned long debounce = 200; // Create constant debounce time of 200ms

void setup() {
  // Initialize Comms
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // INPUT_PULLUP used for ISR

  attachInterrupt(digitalPinToInterrupt(BUTTON), toggle, FALLING); // Falling edge used to prevent button flicker
}

// Interrupt based on Lab 2 - Exercise 1 initally provided by Google Gemini Pro
void toggle(){
  if(millis() - int_time > debounce){
    isRunning = !isRunning; // each time button is pressed, isRunning will go between true and false, initialized at false
  }
  int_time = millis();
}

// Helper Function: Written by Google Gemini Pro, used to set LED states //
// This section of code was taken directly from Lab 1 - Exercise 6 //
void setLEDs(int r, int g, int b){
  digitalWrite(RED, r);
  digitalWrite(GREEN, g);
  digitalWrite(BLUE, b);
}

// Main loop //
// This portion of code was assisted via advice on how to go about the loop by Google Gemini Pro, but written by self //
// Loop was compacted for less lines of code //
// isRunning is set initially at false, once button is pressed loop begins and LED sequence runs until button is pressed again
void loop() {
  // LED Sequence Execution // 
  if (isRunning){setLEDs(1, 0, 0); delay(500); // Begins LED sequence if loop is running, delays for 0.5s before switching to next portion of sequence
    if(!isRunning){setLEDs(0,0,0); return;} // if button is pressed, ISR activates and turns off loop
    setLEDs(1, 1, 0); delay(500);
    if(!isRunning){setLEDs(0,0,0); return;}
    setLEDs(1, 1, 1); delay(500);
    if(!isRunning){setLEDs(0,0,0); return;}
    setLEDs(0, 1, 1); delay(500);
    if(!isRunning){setLEDs(0,0,0); return;}
    setLEDs(0, 0, 1); delay(500);
    if(!isRunning){setLEDs(0,0,0); return;}
    setLEDs(1, 0, 1); delay(500);
    if(!isRunning){setLEDs(0,0,0); return;}
    else{ setLEDs(0,0,0);
    } 
  }
}
