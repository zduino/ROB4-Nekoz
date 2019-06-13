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
                onPress();
                Debounce_Btn_Time = millis() + 20;   // Set time to ignore button bouncing
            }
        }
    }

    Btn_State_Last = Btn_State;
}

void onPress() {
    if (Playing_Game) {

    }
    else {
        digitalWrite(LED_RED, LOW);


        Playing_Game = true;
        Game_Start = millis();
    }
}

void displayScore() {
    unsigned long diff = abs( (Game_Stop - Game_Start) - GOAL_TIME );

    if (diff < 1000) {
        digitalWrite(LED_RED, LOW);

    }
    else if (diff < 2000) {

        digitalWrite(LED_BLUE, LOW);
    }
    else {
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_YELLOW, LOW);

    }
}
