// Make labels for each pin being used
#define LED_NS_RED          7
#define LED_NS_YELLOW       6
#define LED_NS_GREEN        5
#define LED_EW_RED          4
#define LED_EW_YELLOW       3
#define LED_EW_GREEN        2

#define LED_DEBUG          13

// Make labels for each state the stop light has (each one must have unique id)
#define S_NS_RED            0
#define S_NS_GREEN          1
#define S_NS_YELLOW         2
#define S_EW_RED            3
#define S_EW_GREEN          4
#define S_EW_YELLOW         5

// Declare functions
void All_Off();
void All_Red();
void NS_Green();
void NS_Yellow();
void EW_Green();
void EW_Yellow();

// Initialize global variables
unsigned long Next_Light_Change = 0;
int Current_State;
int Next_State;

// The setup routine runs once (when the board turns on, when you press reset, or when
// you program the board) 
void setup() {
    // Set pins with LEDs connected to outputs
    pinMode(LED_NS_RED, OUTPUT);
    pinMode(LED_NS_YELLOW, OUTPUT);
    pinMode(LED_NS_GREEN, OUTPUT);
    pinMode(LED_EW_RED, OUTPUT);
    pinMode(LED_EW_YELLOW, OUTPUT);
    pinMode(LED_EW_GREEN, OUTPUT);

    pinMode(LED_DEBUG, OUTPUT);

    // Turn all lights off
    All_Off();

    // Initial state variables
    Current_State = S_NS_RED;
    Next_State = S_NS_GREEN;

    // Wait a sec
    delay(1000);
}

// The loop routine runs repeatedly after the setup routine has ended
void loop() {

    // Check if time to change state
    if (millis() >= Next_Light_Change) {
        Current_State = Next_State; // Change current state to next state

        // Both ways red
        if (Current_State == S_NS_RED) {            // Check if current state
            Next_State = S_NS_GREEN;                // Set next state
            All_Red();                              // Change Lights (calls function)
            Next_Light_Change = millis() + 1000;    // Schedual next state change
        }
        // North South green
        else if (Current_State == S_NS_GREEN) {
            Next_State = S_NS_YELLOW;
            NS_Green();
            Next_Light_Change = millis() + 5000;
        }
        // North South yellow
        else if (Current_State == S_NS_YELLOW) {
            Next_State = S_EW_RED;
            NS_Yellow();
            Next_Light_Change = millis() + 2000;
        }
        // Both ways red
        else if (Current_State == S_EW_RED) {
            Next_State = S_EW_GREEN;
            All_Red();
            Next_Light_Change = millis() + 1000;
        }
        // East West green
        else if (Current_State == S_EW_GREEN) {
            Next_State = S_EW_YELLOW;
            EW_Green();
            Next_Light_Change = millis() + 5000;
        }
        // East West yellow
        else if (Current_State == S_EW_YELLOW) {
            Next_State = S_NS_RED;
            EW_Yellow();
            Next_Light_Change = millis() + 2000;
        }
        // State Error Catch
        else {
            Next_State = S_NS_RED; // reset state machine
            All_Off();
        }
    }

    // Blink Debug LED (to prove multitasking)
    if (millis() / 500 % 2 == 0) {
        digitalWrite(LED_DEBUG, HIGH);
    } else {
        digitalWrite(LED_DEBUG, LOW);
    }
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
