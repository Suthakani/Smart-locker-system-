#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo lockerServo;
const int servoPin = 9;
const int buzzer = 10;

const String openPassword = "1234";
const String closePassword = "4321";
String inputPassword = "";
bool isOpen = false;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A4, A5, 6, 7};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.begin(16, 2);
  lockerServo.attach(servoPin);
  delay(200);

  // Force start in closed position
  lockerServo.write(0);  // First open (Wokwi reset trick)
  delay(300);
  lockerServo.detach();
  delay(200);
  lockerServo.attach(servoPin);
  lockerServo.write(90);   // Then close
  delay(300);

  pinMode(buzzer, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      lcd.clear();

      if (!isOpen && inputPassword == openPassword) {
        lockerServo.write(0); // Open
        lcd.print("Locker Opened");
        isOpen = true;
      }
      else if (isOpen && inputPassword == closePassword) {
        lockerServo.write(90); // Close
        lcd.print("Locker Closed");
        isOpen = false;
      }
      else {
        lcd.print("Wrong Password");
        tone(buzzer, 1000);
        delay(1000);
        noTone(buzzer);
      }

      delay(1500);
      lcd.clear();
      lcd.print("Enter Password:");
      inputPassword = "";
    }
    else if (key == '*') {
      inputPassword = "";
      lcd.clear();
      lcd.print("Enter Password:");
    }
    else {
      inputPassword += key;
      lcd.setCursor(0, 1);
      lcd.print(inputPassword);
    }
  }
}
