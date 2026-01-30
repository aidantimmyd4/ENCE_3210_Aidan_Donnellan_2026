// Lab 1 - Exercise 5 //
// Donnellan - 01/13/26 //
// Google Gemini Pro used for some elements of code //

#define ARRAY_1 50 // random sized array, user can change
#define PATTERN_SIZE 3 // three value pattern array that will get stored in ARRAY_1
#define RED 5
#define GREEN 4

// Defining global variables
int gdata[ARRAY_1]; // this will get filled with random values
int gpattern[PATTERN_SIZE] = {5, 10, 15}; // Pattern defined in the code by programmer

void setup() {
  // initialize comms and pinouts
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  // Generate random values for Array_1
  for (int i=0; i < ARRAY_1; i++){
    gdata[i] = random(0, 50); // Generates a random value between 0 and 49 that will be stored in our array
  }

  // define an int for number of occurances
  int occurances = 0;
  
  // Pattern Detection. This portion is written by Google Gemini Pro, prompted and commented by self
  for (int i = 0; i <= ARRAY_1 - PATTERN_SIZE; i++){
     if (gdata[i] == gpattern[0] && gdata [i+1] == gpattern[1] && gdata[i+2] == gpattern[2]){
      occurances++; // gdata[i], gdata[i+1], gdata[i+2] allow cpu to look ahead in the array
      // we do ARRAY_1 - Pattern size because if i went to 49, gdata[i+1] and gdata[i+2] would try
      // to read gdata[50] and gdata[51], since the array only goes to 49, a memory error would be caused
     }
  }

  if (occurances > 0){ // if occurances > 0, Green will light up
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
  }
  else{ // if occurances = 0, Red will light up
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
  }
  Serial.print("Occurances found: "); // Prints # of occurances found
  Serial.println(occurances);
}

void loop() {
  // put your main code here, to run repeatedly:

}
