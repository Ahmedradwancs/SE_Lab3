// Lab 3

// Define pin numbers for LEDs
#define LED_W 11  // White LED
#define LED_G 10  // Green LED
#define LED_Y 9   // Yellow LED
#define LED_R 8   // Red LED

// Define pin numbers for switches
#define SWITCH1 4  // Switch 1 (Controls LED-W and LED-R)
#define SWITCH2 3  // Switch 2 (Controls LED-G and LED-Y)
#define SWITCH3 2  // Switch 3 (Controls sound/buzzer)

// Define pin numbers for sensors and sound output
#define SOUND 12           // Buzzer/Sound output
#define TEMP_SENSOR A0     // Temperature sensor (Analog input)
#define LDR_SENSOR A1      // Light sensor (LDR - Analog input)
#define PHOTO_INTERRUPT 5  // Photo interrupter sensor (Digital input)

// Runs once when the board is powered on or reset
void setup() {
    // Initialize LED pins as outputs
    pinMode(LED_R, OUTPUT);
    pinMode(LED_Y, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_W, OUTPUT);

    // Initialize switch pins as inputs
    pinMode(SWITCH1, INPUT);
    pinMode(SWITCH2, INPUT);
    pinMode(SWITCH3, INPUT);

    // Initialize sensor and sound pins
    pinMode(SOUND, OUTPUT);
    pinMode(TEMP_SENSOR, INPUT);
    pinMode(LDR_SENSOR, INPUT);
    pinMode(PHOTO_INTERRUPT, INPUT);

    // Initialize Serial Monitor for debugging
    Serial.begin(9600);

    // Run initial LED blinking sequence
    initialBlink();

    // Ensure Green LED is OFF at startup
    digitalWrite(LED_G, LOW); 
}

// Main loop (runs continuously)
void loop() {
    checkSwitch1();         // Handle Switch 1 (LED-W & LED-R)
    checkSwitch2();         // Handle Switch 2 (LED-G & LED-Y blinking)
    checkSwitch3();         // Handle Switch 3 (Buzzer)
    readTemperature();      // Read temperature sensor and display
    checkLDR();             // Handle Light Sensor (LDR)
    checkPhotoInterrupter();// Handle Photo Interrupter sensor
}

// Initial LED blink sequence at startup
void initialBlink() {
    digitalWrite(LED_W, HIGH); // Turn ON White LED
    delay(1000);
    digitalWrite(LED_W, LOW);  // Turn OFF White LED
    delay(1000);

    // Blink Red LED 10 times
    for (int i = 0; i < 10; i++) {
        digitalWrite(LED_R, HIGH);
        delay(1000);
        digitalWrite(LED_R, LOW);
        delay(1000);
    }

    // Turn ON Yellow LED for 5 seconds
    digitalWrite(LED_Y, HIGH);
    delay(5000);
    digitalWrite(LED_Y, LOW);

    // Turn ON Green LED for 1 second
    digitalWrite(LED_G, HIGH);
    delay(1000);
}

// Function to check Switch 1 state
// If Switch 1 is pressed (LOW), turn ON both LED-W and LED-R
void checkSwitch1() {
    if (digitalRead(SWITCH1) == LOW) { 
        digitalWrite(LED_W, HIGH);
        digitalWrite(LED_R, HIGH);
    } else {
        digitalWrite(LED_W, LOW);
        digitalWrite(LED_R, LOW);
    }
}

// Function to check Switch 2 state
// If Switch 2 is pressed (LOW), blink LED-G and LED-Y 5 times
void checkSwitch2() {
    if (digitalRead(SWITCH2) == LOW) {
        for (int i = 0; i < 5; i++) {
            digitalWrite(LED_G, HIGH);
            digitalWrite(LED_Y, HIGH);
            delay(500);
            digitalWrite(LED_G, LOW);
            digitalWrite(LED_Y, LOW);
            delay(500);
        }
    }
}

// Function to check Switch 3 state
// If Switch 3 is pressed (LOW), turn ON buzzer for 1 second
void checkSwitch3() {
    if (digitalRead(SWITCH3) == LOW) {
        digitalWrite(SOUND, HIGH); // Activate buzzer
        delay(1000);
    } else {
        digitalWrite(SOUND, LOW);  // Deactivate buzzer
        delay(1000);
    }
}

// Function to read temperature sensor and display value in Celsius
void readTemperature() {
    int rawValue = analogRead(TEMP_SENSOR); // Read raw sensor value (0-1023)
    float voltage = rawValue * 5.0 / 1023.0; // Convert raw value to voltage
    float temperature = voltage * 100.0; // Convert voltage to Celsius

    // Print temperature to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    delay(1000);
}

// Function to check Light Sensor (LDR)
// If light level is low, turn ON LED-W
void checkLDR() {
    int ldrValue = analogRead(LDR_SENSOR); // Read LDR value
    Serial.print("LDR Value: ");
    Serial.println(ldrValue); // Print value to Serial Monitor

    if (ldrValue < 500) { // If it's dark, turn ON LED-W
        digitalWrite(LED_W, HIGH);
    } else {
        digitalWrite(LED_W, LOW);
    }
    delay(500);
}

// Function to check Photo Interrupter sensor
// If object detected, turn ON buzzer and print message
void checkPhotoInterrupter() {
    if (digitalRead(PHOTO_INTERRUPT) == HIGH) {
        digitalWrite(SOUND, HIGH); // Activate buzzer
        Serial.println("Object detected in Photo Interrupter!");
    } else {
        digitalWrite(SOUND, LOW); // Deactivate buzzer
    }
    delay(500);
}
