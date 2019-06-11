// Make labels for each pin being used
#define LED_NS_RED          7
#define LED_NS_YELLOW       6
#define LED_NS_GREEN        5
#define LED_EW_RED          4
#define LED_EW_YELLOW       3
#define LED_EW_GREEN        2

#define LED_DEBUG          13

// Function declarations
void All_Off();
void All_Red();
void NS_Green();
void NS_Yellow();
void EW_Green();
void EW_Yellow();

// The setup routine runs once (when the board turns on, when you press reset, or when you program the board) 
void setup() {
    // Set pins with LEDs connected as outputs
    pinMode(LED_NS_RED, OUTPUT);
    pinMode(LED_NS_YELLOW, OUTPUT);
    pinMode(LED_NS_GREEN, OUTPUT);
    pinMode(LED_EW_RED, OUTPUT);
    pinMode(LED_EW_YELLOW, OUTPUT);
    pinMode(LED_EW_GREEN, OUTPUT);

    pinMode(LED_DEBUG, OUTPUT);
    
    // Turn all lights off
    All_Off();

    // Wait a sec
    delay(1000);
}

void loop() {
    // Both ways red
    All_Red();
    delay(500);

    // North South green
    NS_Green();
    delay(5000);

    // North South yellow
    NS_Yellow();
    delay(2000);

    // Both ways red
    All_Red();
    delay(500);

    // East West green
    EW_Green();
    delay(5000);

    // East West yellow
    EW_Yellow();
    delay(2000);
}


// Function definitions
void All_Off() {
    digitalWrite(LED_NS_RED, LOW);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, LOW);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, LOW);
}

void All_Red() {
    digitalWrite(LED_NS_RED, HIGH);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, HIGH);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, LOW);
}

void NS_Green() {
    digitalWrite(LED_NS_RED, LOW);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, HIGH);
    digitalWrite(LED_EW_RED, HIGH);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, LOW);
}

void NS_Yellow() {
    digitalWrite(LED_NS_RED, LOW);
    digitalWrite(LED_NS_YELLOW, HIGH);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, HIGH);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, LOW);
}

void EW_Green() {
    digitalWrite(LED_NS_RED, HIGH);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, LOW);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, HIGH);
}

void EW_Yellow() {
    digitalWrite(LED_NS_RED, HIGH);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, LOW);
    digitalWrite(LED_EW_YELLOW, HIGH);
    digitalWrite(LED_EW_GREEN, LOW);
}
