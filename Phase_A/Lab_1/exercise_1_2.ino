// Lab 1 - Exercise 2 //
// Started 01/07/26 - Completed 01/14/26 //
// Code done in class, some corrections made on 01/14/26 //

#include <math.h> // include math library

const int N = 361;
float cosTable[N]; // can put const in or can fill float array as cosTable[361]

void setup() {
  Serial.begin(9600); // Initialize comms
  
  for(int deg = 0; deg <= 360; deg++) // Iterates over each angle in array
  {
    float rad = deg * PI / 180.0; // Converts from degrees to radians
    cosTable[deg] = cos(rad); // saves each calculated value in array
    Serial.println("Degree: Cosine Value");
    Serial.print(deg); // Prints degree value in array
    Serial.print(" : ");
    Serial.println(cosTable[deg], 2); // prints calculated cos value, prints to 2 decimal places
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
