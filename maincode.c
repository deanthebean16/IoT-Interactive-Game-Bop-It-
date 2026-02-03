#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Servo myservo;  // create servo object to control a servo
int servoPin = 2;

// Pin definitions
int BUTT = 19;
int lvl1 = 18;
int lvl2 = 5;
int lvl3 = 23;

void setup() {
  Serial.begin(115200);
  
  pinMode(BUTT, INPUT_PULLDOWN);
  pinMode(lvl1, OUTPUT);
  pinMode(lvl2, OUTPUT);
  pinMode(lvl3, OUTPUT);
  
  Dabble.begin("deanLOL");

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Hello, world!");
  display.display();

  // Allow allocation of all timers for ESP32 PWM
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myservo.attach(servoPin, 500, 2500); 
  myservo.setPeriodHertz(50);
}

void loop() {
  // Get inputs from Dabble app
  Dabble.processInput();

  int choice = random(1, 4);

  // --- CHOICE 1: Physical Button ---
  if (choice == 1) {
    digitalWrite(lvl1, HIGH);
    
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Button");
    display.display();
    
    myservo.write(135);

    // Wait for physical button press
    while (digitalRead(BUTT) != 0) {
      delay(10);
    }
    digitalWrite(lvl1, LOW);
  }

  // --- CHOICE 2: Dabble Triangle ---
  else if (choice == 2) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Triangle");
    display.display();

    digitalWrite(lvl2, HIGH);
    myservo.write(110);

    // Wait for Dabble Gamepad Triangle
    while (!GamePad.isTrianglePressed()) {
      Dabble.processInput();
      delay(10);
    }
    digitalWrite(lvl2, LOW);
  }

  // --- CHOICE 3: Dabble Circle ---
  else if (choice == 3) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Circle");
    display.display();

    digitalWrite(lvl3, HIGH);
    myservo.write(90);

    // Wait for Dabble Gamepad Circle
    while (!GamePad.isCirclePressed()) {
      Dabble.processInput();
      delay(10);
    }
    digitalWrite(lvl3, LOW);
  }
}
