// Controls Lab 3 //
// Donnellan - 01/27/26 //
// This code is primarily based on ISR code from Lecture Slides Phase A Part 3, code is commented accordingly //
// Any code assisted by Google Gemini Pro will be commented accordingly //

// Define Macros
#define RED 5
#define GREEN 4
#define BUTTON 2
#define TIMER_COMPARE_VALUE 7811 // 16MHz/(1024-2Hz) = 7811 (On 500ms, Off 500ms, 1Hz toggle), proper timing assisted by Google Gemini Pro

// Define Volatiles that will be used in ISR's
volatile int gCounter = 0;
volatile int timeCounter = 0;
volatile bool green = LOW; // Set led initial off
volatile bool red = LOW; // Set led initial off

void setup(){
  // Initialize Comms + ISR
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  
  // Disable Interrupts
  noInterrupts();
  // This section based on Phase A Part 3 slide 56/84 
  // Enable External Interrupt to INT0
  EIMSK |= (1<<INT0); // Enables external interrupts on pin 2
  // Trigger interrupt on any logical change, ISC01 is Falling Edge. Google Gemini Pro helped fix this error as it was initially at ISC00 and not working correctly
  EICRA |= (1<<ISC01);

  // This section based on Phase A Part 3 slide 80/84
  TCCR1A = 0; // Control Register A set to 0
  TCCR1B = 0; // Control Register B set to 0
  TCNT1 = 0; // Sets Timer to 0. Assisted by Google Gemini Pro during error correction
  OCR1A = TIMER_COMPARE_VALUE; // Sets target value to match timer
  TCCR1B |= (1<<WGM12);
  TCCR1B |= (1<<CS12) | (1<<CS10); // CS12 and CS10 set prescalar to 1024. Phase A Part 3 only listed CS12, Gemini Pro suggested using CS10 aswell for proper scaling
  TIMSK1 |= (1<<OCIE1A);

  // Enable Interrupts
  interrupts();
}

// Create ISR for GREEN LED
// ISR name convention taken from Phase A Part 3 slide 79/84
// Task 1: Main Task
ISR(TIMER1_COMPA_vect){
  green = !green; // toggles Green LED
  digitalWrite(GREEN, green); // writes state based on state of Timer
  gCounter++; // adds to counter
}

// Create ISR for RED LED
// ISR name convention taken from Phase A Part 3 slide 57/80
// Task 2: Background task, impacted by external interrupt
ISR(INT0_vect){
  red = !red; // Toggles Red LED based on external interupt from button on pin 2
  digitalWrite(RED, red); // writes state based on state of INT0 ISR
}

// Create Loop
void loop(){
  if(gCounter >= 6){ // gCounter added every 500ms based on prescalar timing, once this is iterated 6 times, timeCounter will add three seconds
    timeCounter += 3;
    Serial.print(" Counter time: ");
    Serial.print(timeCounter);

    // This part added by Google Gemini Pro during error correction, ensures gCounter isn't modified during interrupt
    noInterrupts();
    gCounter = 0;
    interrupts();
  }
}
