// Lab 2 - Exercise 1 //
// Donnellan - 01/21/26 //
// Initial Comment: This exercise is version Lab 2 - Exercise 1.2 written 01/21/26 //
// Version 1.1 written 01/16/26 used Google Gemini Pro extensively to write and understand ISR design //
// This version is written without reference to Version 1.1 //
// Reference to Google Gemini Pro should still be made as 1.1 was written with it, and was studied in order to write this code without it //

// define macros
#define RED 5
#define GREEN 4
#define BUTTON_1 2 // ISR pin
#define BUTTON_2 3 // ISR pin 

// define global vals
volatile unsigned int gCounter1 = 0; // Intialize button counter 1 at 0 for ISR
volatile unsigned int gCounter2 = 0; // Initialize Button counter 2 at 0 for ISR

const unsigned int debounce = 200; // Constant debounce of 200ms

void setup() {
  // Initialize comms
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUTTON_1, INPUT_PULLUP); // INPUT_PULLUP for ISR
  pinMode(BUTTON_2, INPUT_PULLUP); // INPUT_PULLUP for ISR

  // Attach Interrupts for each button
  attachInterrupt(digitalPinToInterrupt(BUTTON_1), isr_1, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_2), isr_2, FALLING);
}

void loop() {
  // Initialize LEDs off
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);

  // If statements // 
  // If both buttons have equal presses, set both LEDs on (in place of blue) //
  if (gCounter1 == gCounter2 && gCounter1 > 0){
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    Serial.print("Button count is the same");
  }
  // If button one is pressed more than button two, light up red //
  if (gCounter1 > gCounter2){
    digitalWrite(RED, HIGH);
  }
  // If button 2 is pressed more than button one, light up green //
  if (gCounter2 > gCounter1){
    digitalWrite(GREEN, HIGH);
  }
  // Print button counts
  Serial.print("Count 1 = "); Serial.print(gCounter1);
  Serial.print(" | Count 2 = "); Serial.print(gCounter2);

  // delay LED timing by 1 second
  delay(1000);
}

// Create ISR functions //
// ISR 1 controls button 1, detects if button one is pressed and adds to its counter
void isr_1(){
  static unsigned int int_count1 = 0; // Local variable within ISR
  if (millis() - int_count1 > debounce){
    gCounter1++;
    int_count1 = millis();
  }
}

// ISR 2 controls button 2, detects if button two is pressed and adds to its counter
void isr_2(){
  static unsigned int int_count2 = 0; // Local variable within ISR
  if (millis() - int_count2 > debounce){
    gCounter2++;
    int_count2 = millis();
  }
}
