const int buttonPin = 2;   
int buttonState = 0;        // Current state of the button
int lastButtonState = HIGH; // Previous state of the button
bool nameBlinking = false;  // Flag to track if the name is currently blinking
int charIndex = 0;          // Index of the character being blinked

char inputName[100];        // Buffer to store user input
int inputIndex = 0;         // Index for reading user input

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Use INPUT_PULLUP for internal pull-up resistor
  Serial.begin(9600);
  Serial.println("Enter the name you want to blink in Morse code (a-z, space):");
}

//procedure for dot
void dot() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

//procedure for dash
void dash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

//morse code encryption
void morse_encryption(char name) {
  switch (name) {
    case 'a':
      dot();
      dash();
      break;
    case 'b':
      dash();
      dot();
      dot();
      dot();
      break;
    case 'c':
      dash();
      dot();
      dash();
      dot();
      break;
    case 'd':
      dash();
      dot();
      dot();
      break;
    case 'e':
      dot();
      break;
    case 'f':
      dot();
      dot();
      dash();
      dot();
      break;
    case 'g':
      dash();
      dash();
      dot();
      break;
    case 'h':
      dot();
      dot();
      dot();
      dot();
      break;
    case 'i':
      dot();
      dot();
      break;
    case 'j':
      dot();
      dash();
      dash();
      dash();
      break;
    case 'k':
      dash();
      dot();
      dash();
      break;
    case 'l':
      dot();
      dash();
      dot();
      dot();
      break;
    case 'm':
      dash();
      dash();
      break;
    case 'n':
      dash();
      dot();
      break;
    case 'o':
      dash();
      dash();
      dash();
      break;
    case 'p':
      dot();
      dash();
      dash();
      dot();
      break;
    case 'q':
      dash();
      dash();
      dot();
      dash();
      break;
    case 'r':
      dot();
      dash();
      dot();
      break;
    case 's':
      dot();
      dot();
      dot();
      break;
    case 't':
      dash();
      break;
    case 'u':
      dot();
      dot();
      dash();
      break;
    case 'v':
      dot();
      dot();
      dot();
      dash();
      break;
    case 'w':
      dot();
      dash();
      dash();
      break;
    case 'x':
      dash();
      dot();
      dot();
      dash();
      break;
    case 'y':
      dash();
      dot();
      dash();
      dash();
      break;
    case 'z':
      dash();
      dash();
      dot();
      dot();
      break;
    default:
      // Ignore unknown characters
      break;
  }
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    nameBlinking = !nameBlinking; // Toggle the blinking flag
    charIndex = 0; // Reset the character index
  }

  lastButtonState = buttonState;

  if (nameBlinking) {
    if (inputName[charIndex] != '\0') {
      char y = inputName[charIndex];
      morse_encryption(y);
      delay(1000); // Pause between characters

      charIndex++;
    } else {
      nameBlinking = false; // End of input name, stop blinking
    }
  } else {
    // Turn off the LED if not blinking
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Read user input from Serial Monitor
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();
    if (incomingChar == '\n' || inputIndex >= sizeof(inputName) - 1) {
      inputName[inputIndex] = '\0'; // Null-terminate the string
      inputIndex = 0; // Reset input index
      Serial.print("name ");
      Serial.print(inputName);
      Serial.print(" blinking");
      nameBlinking = true; // Start blinking the input name
    } else {
      inputName[inputIndex] = incomingChar;
      inputIndex++;
    }
  }
}
