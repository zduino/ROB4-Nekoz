
#define MC_L_PWM                6
#define MC_R_PWM                3

#define MC_L_I1                 5
#define MC_L_I2                 7
#define MC_R_I1                 2
#define MC_R_I2                 4

void setMotorSpeed(int L, int R);

void setup() {
    pinMode(MC_L_PWM, OUTPUT);
    pinMode(MC_L_I1, OUTPUT);
    pinMode(MC_L_I2, OUTPUT);
    
    pinMode(MC_R_PWM, OUTPUT);
    pinMode(MC_R_I1, OUTPUT);
    pinMode(MC_R_I2, OUTPUT);
}

void loop() {
    setMotorSpeed(100, 50);
    delay(1000);
    setMotorSpeed(0, 0);
    delay(1000);
}

void setMotorSpeed(int L, int R) {
    L = L * 255 / 100;
    R = R * 255 / 100;

    if (L > 0) {
        digitalWrite(MC_L_I1, HIGH);
        digitalWrite(MC_L_I2, LOW);
    }
    else if (L < 0) {
        digitalWrite(MC_L_I1, LOW);
        digitalWrite(MC_L_I2, HIGH);
    } else {
        digitalWrite(MC_L_I1, LOW);
        digitalWrite(MC_L_I2, LOW);
    }

    analogWrite(MC_L_PWM, L);

    if (R > 0) {
        digitalWrite(MC_R_I1, HIGH);
        digitalWrite(MC_R_I2, LOW);
    }
    else if (R < 0) {
        digitalWrite(MC_R_I1, LOW);
        digitalWrite(MC_R_I2, HIGH);
    } else {
        digitalWrite(MC_R_I1, LOW);
        digitalWrite(MC_R_I2, LOW);
    }

    analogWrite(MC_R_PWM, R);
}
