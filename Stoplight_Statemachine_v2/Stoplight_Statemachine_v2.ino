// Make labels for each pin being used
#define LED_NS_RED          7
#define LED_NS_YELLOW       6
#define LED_NS_GREEN        5
#define LED_EW_RED          4
#define LED_EW_YELLOW       3
#define LED_EW_GREEN        2

#define BTN_NS             11
#define BTN_EW              9

#define LED_NS_CROSSWALK   10
#define LED_EW_CROSSWALK    8

#define LED_DEBUG          13

// Make labels for each state the stop light has (each one must have unique id)
#define S_NS_RED            0
#define S_NS_GREEN          1
#define S_NS_YELLOW         2
#define S_EW_RED            3
#define S_EW_GREEN          4
#define S_EW_YELLOW         5

#define S_NS_CROSS_GREEN    6
#define S_NS_CROSS_YELLOW   7
#define S_EW_CROSS_GREEN    8
#define S_EW_CROSS_YELLOW   9

// Declare functions
void All_Off();
void All_Red();
void NS_Green();
void NS_Yellow();
void EW_Green();
void EW_Yellow();
void NS_Cross_Green();
void NS_Cross_Yellow();
void EW_Cross_Green();
void EW_Cross_Yellow();

// Initialize global variables
unsigned long Next_Light_Change = 0;
int Current_State;
int Next_State;

bool NS_Crosswalk_Requested = false;
bool EW_Crosswalk_Requested = false;

bool NS_Btn_State_Last = false;
bool EW_Btn_State_Last = false;

unsigned long Debounce_NS_Btn_Time = 0;
unsigned long Debounce_EW_Btn_Time = 0;

unsigned long NS_Crosswalk_Blink_Start = 0;
unsigned long EW_Crosswalk_Blink_Start = 0;

// The setup routine runs once (when the board turns on, when you press reset, or when
// you program the board) 
void setup() {
    // Set up Serial bus
    Serial.begin(9600);
    
    // Set pins with LEDs connected as outputs
    pinMode(LED_NS_RED, OUTPUT);
    pinMode(LED_NS_YELLOW, OUTPUT);
    pinMode(LED_NS_GREEN, OUTPUT);
    pinMode(LED_EW_RED, OUTPUT);
    pinMode(LED_EW_YELLOW, OUTPUT);
    pinMode(LED_EW_GREEN, OUTPUT);

    pinMode(LED_NS_CROSSWALK, OUTPUT);
    pinMode(LED_EW_CROSSWALK, OUTPUT);
    
    pinMode(LED_DEBUG, OUTPUT);

    // Set pins with buttons connected as inputs
    pinMode(BTN_NS, INPUT);
    pinMode(BTN_EW, INPUT);
    
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
    // Read current button states
    bool NS_Btn_State = digitalRead(BTN_NS);
    bool EW_Btn_State = digitalRead(BTN_EW);

    // Check if north south button got pressed
    if (Debounce_NS_Btn_Time <= millis()) {             // Check if button is bouncing
        if (NS_Btn_State == true) {                     // Check if button state is currently being pressed
            if (NS_Btn_State_Last == false) {           // Check if previous button state was not being pressed
                NS_Crosswalk_Requested = true;          // Request crosswalk signal
                Debounce_NS_Btn_Time = millis() + 20;   // Set time to ignore button bouncing
            }
        }
    }
    
    // Check if east west button got pressed
    if (Debounce_EW_Btn_Time <= millis()) {
        if (EW_Btn_State == true) {
            if (EW_Btn_State_Last == false) {
                EW_Crosswalk_Requested = true;
                Debounce_EW_Btn_Time = millis() + 20;
            }
        }
    }
    
    // Check if time to change state
    if (millis() >= Next_Light_Change) {
        Current_State = Next_State; // Change current state to next state

        // Both ways red
        if (Current_State == S_NS_RED) {            // Check if current state
            if (NS_Crosswalk_Requested == true) {   // Check if crosswalk was requested
                NS_Crosswalk_Requested = false;     // Reset request flag
                Next_State = S_NS_CROSS_GREEN;      // Set next state
            }
            else {
                Next_State = S_NS_GREEN;            // Set next state
            }
            Next_Light_Change = millis() + 1000;    // Schedual next state change
        }
        // North South green
        else if (Current_State == S_NS_GREEN) {
            Next_State = S_NS_YELLOW;
            Next_Light_Change = millis() + 5000;
        }
        // North South yellow
        else if (Current_State == S_NS_YELLOW) {
            Next_State = S_EW_RED;
            Next_Light_Change = millis() + 2000;
        }
        // Both ways red
        else if (Current_State == S_EW_RED) {
            if (EW_Crosswalk_Requested == true) {   // Check if crosswalk was requested
                EW_Crosswalk_Requested = false;     // Reset request flag
                Next_State = S_EW_CROSS_GREEN;      // Set next state
            }
            else {
                Next_State = S_EW_GREEN;            // Set next state
            }
            Next_Light_Change = millis() + 1000;
        }
        // East West green
        else if (Current_State == S_EW_GREEN) {
            Next_State = S_EW_YELLOW;
            Next_Light_Change = millis() + 5000;
        }
        // East West yellow
        else if (Current_State == S_EW_YELLOW) {
            Next_State = S_NS_RED;
            Next_Light_Change = millis() + 2000;
        }
        // North South green with crosswalk signal
        else if (Current_State == S_NS_CROSS_GREEN) {
            Next_State = S_NS_CROSS_YELLOW;
            Next_Light_Change = millis() + 5000;
        }
        // North South yellow with crosswalk signal
        else if (Current_State == S_NS_CROSS_YELLOW) {
            Next_State = S_EW_RED;
            Next_Light_Change = millis() + 2000;
            NS_Crosswalk_Blink_Start = millis();
        }
        // East West green with crosswalk signal
        else if (Current_State == S_EW_CROSS_GREEN) {
            Next_State = S_EW_CROSS_YELLOW;
            Next_Light_Change = millis() + 5000;
        }
        // East West yellow with crosswalk signal
        else if (Current_State == S_EW_CROSS_YELLOW) {
            Next_State = S_NS_RED;
            Next_Light_Change = millis() + 2000;
            EW_Crosswalk_Blink_Start = millis();
        }
        // State Error Catch
        else {
            Next_State = S_NS_RED; // reset state machine
            All_Off();
        }
    }

    // Both ways red
    if (Current_State == S_NS_RED) {            // Check if current state
        All_Red();                              // Change Lights (calls function)
    }
    // North South green
    else if (Current_State == S_NS_GREEN) {
        NS_Green();
    }
    // North South yellow
    else if (Current_State == S_NS_YELLOW) {
        NS_Yellow();
    }
    // Both ways red
    else if (Current_State == S_EW_RED) {
        All_Red();
    }
    // East West green
    else if (Current_State == S_EW_GREEN) {
        EW_Green();
    }
    // East West yellow
    else if (Current_State == S_EW_YELLOW) {
        EW_Yellow();
    }
    // North South green
    else if (Current_State == S_NS_GREEN) {
        NS_Green();
    }
    // North South yellow
    else if (Current_State == S_NS_YELLOW) {
        NS_Yellow();
    }
    // North South green with crosswalk signal
    else if (Current_State == S_NS_CROSS_GREEN) {
        NS_Cross_Green();
    }
    // North South yellow with crosswalk signal
    else if (Current_State == S_NS_CROSS_YELLOW) {
        NS_Cross_Yellow();
    }
    // East West green with crosswalk signal
    else if (Current_State == S_EW_CROSS_GREEN) {
        EW_Cross_Green();
    }
    // East West yellow with crosswalk signal
    else if (Current_State == S_EW_CROSS_YELLOW) {
        EW_Cross_Yellow();
    }
    
    // Blink Debug LED (to prove multitasking)
    if (millis() / 500 % 2 == 0) {
        digitalWrite(LED_DEBUG, HIGH);
    } else {
        digitalWrite(LED_DEBUG, LOW);
    }

    // Update previous button states
    NS_Btn_State_Last = NS_Btn_State;
    EW_Btn_State_Last = EW_Btn_State;
}

// Function definitions
void All_Off() {
    digitalWrite(LED_NS_RED, LOW);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, LOW);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, LOW);

    digitalWrite(LED_NS_CROSSWALK, LOW);
    digitalWrite(LED_EW_CROSSWALK, LOW);
}

void All_Red() {
    digitalWrite(LED_NS_RED, HIGH);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, HIGH);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, LOW);

    digitalWrite(LED_NS_CROSSWALK, LOW);
    digitalWrite(LED_EW_CROSSWALK, LOW);
}

void NS_Green() {
    digitalWrite(LED_NS_RED, LOW);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, HIGH);
    digitalWrite(LED_EW_RED, HIGH);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, LOW);

    digitalWrite(LED_NS_CROSSWALK, LOW);
    digitalWrite(LED_EW_CROSSWALK, LOW);
}

void NS_Yellow() {
    digitalWrite(LED_NS_RED, LOW);
    digitalWrite(LED_NS_YELLOW, HIGH);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, HIGH);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, LOW);

    digitalWrite(LED_NS_CROSSWALK, LOW);
    digitalWrite(LED_EW_CROSSWALK, LOW);
}

void EW_Green() {
    digitalWrite(LED_NS_RED, HIGH);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, LOW);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, HIGH);

    digitalWrite(LED_NS_CROSSWALK, LOW);
    digitalWrite(LED_EW_CROSSWALK, LOW);
}

void EW_Yellow() {
    digitalWrite(LED_NS_RED, HIGH);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, LOW);
    digitalWrite(LED_EW_YELLOW, HIGH);
    digitalWrite(LED_EW_GREEN, LOW);

    digitalWrite(LED_NS_CROSSWALK, LOW);
    digitalWrite(LED_EW_CROSSWALK, LOW);
}

void NS_Cross_Green() {
    digitalWrite(LED_NS_RED, LOW);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, HIGH);
    digitalWrite(LED_EW_RED, HIGH);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, LOW);

    digitalWrite(LED_NS_CROSSWALK, HIGH);
    digitalWrite(LED_EW_CROSSWALK, LOW);
}

void NS_Cross_Yellow() {
    digitalWrite(LED_NS_RED, LOW);
    digitalWrite(LED_NS_YELLOW, HIGH);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, HIGH);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, LOW);

    if ((millis() - NS_Crosswalk_Blink_Start) / 200 % 2 == 0) {
        digitalWrite(LED_NS_CROSSWALK, HIGH);
        digitalWrite(LED_EW_CROSSWALK, LOW);
    }
    else {
        digitalWrite(LED_NS_CROSSWALK, LOW);
        digitalWrite(LED_EW_CROSSWALK, LOW);
    }
}

void EW_Cross_Green() {
    digitalWrite(LED_NS_RED, HIGH);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, LOW);
    digitalWrite(LED_EW_YELLOW, LOW);
    digitalWrite(LED_EW_GREEN, HIGH);

    digitalWrite(LED_NS_CROSSWALK, LOW);
    digitalWrite(LED_EW_CROSSWALK, HIGH);
}

void EW_Cross_Yellow() {
    digitalWrite(LED_NS_RED, HIGH);
    digitalWrite(LED_NS_YELLOW, LOW);
    digitalWrite(LED_NS_GREEN, LOW);
    digitalWrite(LED_EW_RED, LOW);
    digitalWrite(LED_EW_YELLOW, HIGH);
    digitalWrite(LED_EW_GREEN, LOW);

    if ((millis() - EW_Crosswalk_Blink_Start) / 200 % 2 == 0) {
        digitalWrite(LED_NS_CROSSWALK, LOW);
        digitalWrite(LED_EW_CROSSWALK, HIGH);
    }
    else {
        digitalWrite(LED_NS_CROSSWALK, LOW);
        digitalWrite(LED_EW_CROSSWALK, LOW);
    }
}
