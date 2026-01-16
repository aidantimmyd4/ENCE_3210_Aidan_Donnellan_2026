// Lab 1 - Exercise 4 //
// Donnellan - 01/14/26 //
// Microprocessors hat was used, no blue LED was available //
// Referenced Lauren Ooghe's Exercise 4 to assist in writing this code //

// Define Macros
#define RED 5
#define GREEN 4
#define ARRAY_SIZE 10

char myArray[ARRAY_SIZE] = {'R', 'R', 'G', 'G', 'B', 'B', 'B', 'G', 'R', 'G'};

void setup() {
  // Initialize comms
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  // Create counters used in loops
  int detectR = 0; // 'R' detection
  int detectG = 0; // 'G' detection
  int detectB = 0; // 'B' detection

  // Create loops that light an LED everytime a letter is detected //
  // Assisted by google gemini pro for digitalWrite assignment in for loop //
  for(int i = 0; i <= ARRAY_SIZE; i++){
    if(letterArray[i] == 'R'){
      detectR++; // adds to 'R' counter
      // Lights red LED when 'R' is detected, delays 500ms, then turns off
      digitalWrite(RED, HIGH);
      delay(500);
      digitalWrite(RED, LOW);
    }
    else if(letterArray[i] == 'G'){
      detectG++; // adds to 'G' counter
      // Lights gree LED when 'G' is detected, delays 500ms, then turns off
      digitalWrite(GREEN, HIGH);
      delay(500);
      digitalWrite(GREEN, LOW);
    }
    else if(letterArray[i] == 'B'){
      detectB++; // adds to 'B' counter
      // Lights both red and green LED when 'B' is detected, delays 500ms, then turns off
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, HIGH);
      delay(500);
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, LOW);
    }

    delay(100); // delay for 100ms after array is indexed
  }

  // Prints each number of occurances detected //
  Serial.print("R occurances: ");
  Serial.println(detectR);
  Serial.print("G occurances: ");
  Serial.println(detectG);
  Serial.print("B occurances: ");
  Serial.println(detectB);
}

void loop() {
  // put your main code here, to run repeatedly:

}
