#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10   
#define RST_PIN 9   
#define SERVO_PIN 6 

MFRC522 rfid(10, 9);
Servo garageServo;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

String authorizedCardUID = "d3 25 bf 1b"; 

void setup() {
    Serial.begin(9600);
    SPI.begin();
    rfid.PCD_Init();
    garageServo.attach(6);
    garageServo.write(0); 

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Scan RFID to");
    lcd.setCursor(0, 1);
    lcd.print("Open Garage");
}

void loop() {
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
        return;
    }

    String scannedUID = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        scannedUID += String(rfid.uid.uidByte[i], HEX);
        if (i < rfid.uid.size - 1) {
            scannedUID += " ";
        }
    }

    Serial.println("Card UID: " + scannedUID);

    if (scannedUID == authorizedCardUID) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Garage is");
        lcd.setCursor(0, 1);
        lcd.print("Opening...");

        garageServo.write(90); 
        delay(5000);           

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Garage is");
        lcd.setCursor(0, 1);
        lcd.print("Closing...");

        garageServo.write(0); 
        delay(2000);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Scan RFID to");
        lcd.setCursor(0, 1);
        lcd.print("Open Garage");
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access Denied!");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Scan RFID to");
        lcd.setCursor(0, 1);
        lcd.print("Open Garage");
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
}
