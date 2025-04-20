#define MQ2_A0 A0 
#define RELAY_PIN 3  
#define BUZZER_PIN 5

int gasThreshold = 400;  

void setup() {
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(3, HIGH); 
    digitalWrite(5, LOW);

    Serial.begin(9600);
    Serial.println("Gas Leakage Detector Initialized...");
}

void loop() {
    int gasValue = analogRead(MQ2_A0);  

    Serial.print("Gas Level: ");
    Serial.println(gasValue);

    if (gasValue > gasThreshold) {  
        Serial.println("Gas Detected! Turning Fan and Buzzer ON...");
        digitalWrite(3, LOW); 
        digitalWrite(5, HIGH); 
    } else {
        Serial.println("Gas Levels Normal. Fan and Buzzer OFF.");
        digitalWrite(3, HIGH); 
        digitalWrite(5, LOW); 
    }

    delay(1000);
}

