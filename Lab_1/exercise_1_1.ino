// Lab 1 - Exercise 1 //
// Donnellan - 01/15/26 //
// Code based on in class practice and Phase A part 2 slides //
// Arduino UNO R3 does not have the memory capacity, array is too big for the cpu)

#define ARRAY_SIZE 512

unsigned long result[ARRAY_SIZE]; // unsigned long is 4 bytes wide

unsigned long twice_square(unsigned int value)
{
  return 2*(unsigned long)value*(unsigned long)value; // calculation of twice squared
}

void setup() {
  // Initialize Comms //
  Serial.begin(9600);

  for(int i=0; i<ARRAY_SIZE; i++) // Iterate over each index in array // 
  {
    result[i] = twice_square(i);
    // Print Results
    Serial.print(i);
    Serial.print(":");
    Serial.println(result[i]);
  }
}

void loop(){
}
