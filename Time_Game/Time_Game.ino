// Make labels for each pin being used
#define LED_RED             4
#define LED_YELLOW          3
#define LED_GREEN           2
#define LED_BLUE            8

#define BTN                 9

#define GOAL_TIME       5000

// Initialize global variables
unsigned long Game_Start = 0;
unsigned long Game_Stop = 0;

unsigned long Debounce_Btn_Time = 0;
bool Btn_State_Last = false;

bool Playing_Game = false;

// Declare functions
void onPress();
void displayScore();


void setup() {
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(BTN, INPUT);
    
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
}

void loop() {
    bool Btn_State = digitalRead(BTN);
    
    if (Debounce_Btn_Time <= millis()) {             // Check if button is bouncing
        if (Btn_State == true) {                     // Check if button state is currently being pressed
            if (Btn_State_Last == false) {           // Check if previous button state was not being pressed
                onP // call event function onPress
                Debounce_Btn_Time = millis() + 20;   // Set time to ignore button bouncing
            }
        }
    }

    Btn_State_Last = Btn_State;
}

void onPress() {
    if (Playing_Game) { // if you are playing the game
        =// record time game ends
        (); // display the score
        Playing_Game = false; // end the game
    }
    else {
        // turn blue LED on
        digitalWrite(LED_RED, );
        digitalWrite(LED_YELLOW, );
        digitalWrite(LED_GREEN, );
        digitalWrite(LED_BLUE, );

        = true; // begin the game
        Game_Start = millis(); // record time game starts
    }
}

void displayScore() {
    long diff = abs( (long)(Game_Stop - Game_Start) - GOAL_TIME );

    if (diff < 500) {
        // light green
        digitalWrite(LED_RED, );
        digitalWrite(LED_YELLOW, );
        digitalWrite(LED_GREEN, );
        digitalWrite(LED_BLUE, LOW);
    }
    else if (diff < 1000) {
        // light yellow
        digitalWrite(LED_RED, );
        digitalWrite(LED_YELLOW, );
        digitalWrite(LED_GREEN, );
        digitalWrite(LED_BLUE, LOW);
    }
    else {
        // light red
        digitalWrite(LED_RED, );
        digitalWrite(LED_YELLOW, );
        digitalWrite(LED_GREEN, );
        digitalWrite(LED_BLUE, LOW);
    }
}
