// Lab 1 - Exercise 3 //
// Donnellan - 01/13/26 //
// Google Gemini Pro used to assist in certain sections of code //

// Define array size
#define ARRAY_SIZE 50

int data[ARRAY_SIZE];

void setup() {
  // initialize comms
  Serial.begin(9600);

  // Fill array with random values from 1-1000
  // Prompted and assisted by Google Gemini Pro
  for (int i = 0; i < ARRAY_SIZE; i++){
    data[i] = random(1, 1000); // iterates over until array is filled with 50 random values
  }

  // Finding second max
  int maxVal = 0; // initialize maxVal at 0
  int secondMax = 0; // initialize second Max at 0

  // For loop creation assisted by Google Gemini Pro
  for (int i = 0; i < ARRAY_SIZE; i++){
    if (data[i] > maxVal){ // loops to see if new value is greater than current maxVal
      secondMax = maxVal; // takes old maxVal and moves to second max
      maxVal = data[i]; // takes new higher value and puts it into maxVal
    }
    else if (data[i] > secondMax && data[i] < maxVal){
      secondMax = data[i]; // detects if there is a value greater than our current secondMax
    }
  }

  // Write secondMax to memory location after array
  data[ARRAY_SIZE] = secondMax; // writes second max to array

  // Print Results
  Serial.print("Second Max: "); // print second max
  Serial.println(secondMax);
  Serial.print("Value stored at end of array: "); 
  Serial.println(data[ARRAY_SIZE]);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
