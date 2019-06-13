// Make labels for each pin being used
#define BTN_TOP            11
#define BTN_BOTTOM         9

// Initialize global variables
bool BtnTopStateLast    = false;
bool BtnBottomStateLast = false;

int Counter = 0;

unsigned long DebounceTopTime = 0;
unsigned long DebounceBottomTime = 0;

// The setup routine runs once (when the board turns on, when you press reset, or when
// you program the board)
void setup() {
  // Set pins with buttons connected as inputs
  pinMode(BTN_TOP, INPUT);
  pinMode(BTN_BOTTOM, INPUT);
  
  // Set up Serial bus
  Serial.begin(9600);
}

// The loop routine runs repeatedly after the setup routine has ended
void loop() {
    // Read current button states
    bool btnTopState = digitalRead(BTN_TOP);
    bool btnBottomState = digitalRead(BTN_BOTTOM);

    // Check if top button got pressed
    if (DebounceTopTime <= millis()) {
        if (btnTopState == true) {
            if (BtnTopStateLast == false) {
                Counter = Counter + 1; // increase counter by 1
                Serial.println(Counter);
                DebounceTopTime = millis() + 20;
            }
        }
    }
    
    // Check if bottom button got pressed
    if (DebounceBottomTime <= millis()) {
        if (btnBottomState == true) {
            if (BtnBottomStateLast == false) {
                Counter = Counter - 1; // decrease counter by 1
                Serial.println(Counter);
                DebounceBottomTime = millis() + 20;
            }
        }
    }

    // Update previous button states
    BtnTopStateLast = btnTopState;
    BtnBottomStateLast = btnBottomState;
}
