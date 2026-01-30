// Lab 2 - Exercise 4 //
// Donnellan - 01/20/2026 //
// Some code assisted by Google Gemini Pro when prompted to help outline the program //
// Code written by Google Gemini Pro commented accordingly //

// Define macros
#define BUTTON 2 // ISR Pin

// Define global arrays
int x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Initially filled array of 10 elements
int y[10]; // output of array size 10
const unsigned long debounce = 200; // create constant debounce time of 200ms

volatile bool readyCalculate = false;

void setup() {
  // Initialize Comms
  Serial.begin(9600);
  pinMode(BUTTON, INPUT_PULLUP); // use INPUT_PULLUP for ISR

  attachInterrupt(digitalPinToInterrupt(BUTTON), isr_filter, FALLING); // use falling edge to avoid button flickering
}

// Loop advice provided by Google Gemini Pro, written by self
void loop() {
  // Check if ISR has flagged data
  if (readyCalculate){
    displayResults();
    readyCalculate = false; // Begin with calculation offs, turns on when ISR is activated
  }
}

// Create interrupt service routine with calculation
// Foundation of ISR written by self, for loop assisted by Google Gemini pro
// Based this ISR off Lab 2 - Exercise 1, which was initially aided by Google Gemini Pro
void isr_filter(){
  static unsigned long int_time = 0;
  if (millis() - int_time > debounce){
    for (int n = 0; n < 10; n++){ // Iterates over each element n in the array and calculates for y[n]
      if (n == 0){
        y[n] = 2* x[n] - 0; // Boundary Condition, instead of x[-1] we set to 0
      }
      else{
        y[n] = 2 * x[n] - x[n - 1]; // Performs calculation
      }
    }
    readyCalculate = true; // Turns on calculation
   }
   int_time = millis();
 }

// Display results of calculation when ISR is activate
void displayResults(){
  for (int i = 0; i<10; i++){ // Iterates over each element in array and prints results
    Serial.print("y["); 
    Serial.print(i); 
    Serial.print("] = ");
    Serial.println(y[i]); }
}
