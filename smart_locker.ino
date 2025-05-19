#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo lockServo;

const String password = "1234";
String input = "";

void setup() {
  lcd.begin(16, 2);
  lcd.print("Enter Password");
  lockServo.attach(6);
  lockServo.write(0);
  pinMode(7, OUTPUT); // Buzzer
}

void loop() {
  char key = getKey(); // Simulated function for keypad
  if (key) {
    input += key;
    lcd.setCursor(0, 1);
    lcd.print(input);
    if (input.length() == 4) {
      if (input == password) {
        lcd.clear();
        lcd.print("Access Granted");
        lockServo.write(90); // Unlock
        delay(5000);
        lockServo.write(0); // Lock again
      } else {
        lcd.clear();
        lcd.print("Wrong Password");
        digitalWrite(7, HIGH);
        delay(1000);
        digitalWrite(7, LOW);
      }
      input = "";
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print("Enter Password");
    }
  }
}
