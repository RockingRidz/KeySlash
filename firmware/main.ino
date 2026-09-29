#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keyboard.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int switchPins[] = {D0, D1, D2, D3};
const int encoderA = D4;
const int encoderB = D5;
const int encoderBtn = D6;

volatile int encoderPos = 0;
int lastEncoderState;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();

  for(int i = 0; i < 4; i++) {
    pinMode(switchPins[i], INPUT_PULLUP);
  }

  pinMode(encoderA, INPUT_PULLUP);
  pinMode(encoderB, INPUT_PULLUP);
  pinMode(encoderBtn, INPUT_PULLUP);
  
  lastEncoderState = digitalRead(encoderA);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while(1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("Macropad Ready"));
  display.display();
  delay(500);
}

void loop() {
  for(int i = 0; i < 4; i++) {
    if(digitalRead(switchPins[i]) == LOW) {
      display.clearDisplay();
      display.setCursor(0,0);
      display.print(F("Switch "));
      display.print(i + 1);
      display.println(F(" Pressed"));
      display.display();

      if(i == 0) Keyboard.write('a');
      else if(i == 1) Keyboard.write('b');
      else if(i == 2) Keyboard.write('c');
      else if(i == 3) Keyboard.write('d');
      
      delay(200);
    }
  }

  int currentEncoderState = digitalRead(encoderA);
  if (currentEncoderState != lastEncoderState && currentEncoderState == HIGH) {
    if (digitalRead(encoderB) != currentEncoderState) {
      encoderPos++;
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.releaseAll();
    } else {
      encoderPos--;
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.releaseAll();
    }
    
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(F("Encoder: "));
    display.println(encoderPos);
    display.display();
  }
  lastEncoderState = currentEncoderState;

  if(digitalRead(encoderBtn) == LOW) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(F("Encoder Clicked"));
    display.display();
    
    Keyboard.write(' ');
    delay(200);
  }
}
