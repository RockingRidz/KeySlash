#include <Keyboard.h>
#include <Mouse.h>

// Pin Definitions for your 3 macro keys
const int KEY_CODEX = 2;
const int KEY_GOOGLE = 3;
const int KEY_YOUTUBE = 4;

// Pin Definitions for the Vertical Rotary Encoder (Volume Wheel)
const int ENCODER_CLK = 5; // A Phase pin
const int ENCODER_DT = 6;  // B Phase pin
const int ENCODER_SW = 7;  // Push button switch (Mute)

int lastClkState;

void setup() {
  // Initialize USB HID controls
  Keyboard.begin();

  // Configure button pins with internal pull-ups
  pinMode(KEY_CODEX, INPUT_PULLUP);
  pinMode(KEY_GOOGLE, INPUT_PULLUP);
  pinMode(KEY_YOUTUBE, INPUT_PULLUP);

  // Configure Rotary Encoder pins
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  lastClkState = digitalRead(ENCODER_CLK);
}

void loop() {
  // 1. Press Key 1 to open Codex / VS Code
  if (digitalRead(KEY_CODEX) == LOW) {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    delay(200);
    
    Keyboard.print("code");
    Keyboard.write(KEY_RETURN);
    delay(1000);
  }

  // 2. Press Key 2 to open Google Chrome
  if (digitalRead(KEY_GOOGLE) == LOW) {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    delay(200);

    Keyboard.print("https://www.google.com");
    Keyboard.write(KEY_RETURN);
    delay(1000);
  }

  // 3. Press Key 3 to open YouTube
  if (digitalRead(KEY_YOUTUBE) == LOW) {
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    delay(100);
    Keyboard.releaseAll();
    delay(200);

    Keyboard.print("https://www.youtube.com");
    Keyboard.write(KEY_RETURN);
    delay(1000);
  }

  // 4. Handle Rotary Encoder (Volume Up / Down)
  int currentClkState = digitalRead(ENCODER_CLK);
  if (currentClkState != lastClkState && currentClkState == LOW) {
    if (digitalRead(ENCODER_DT) == HIGH) {
      // Turned Clockwise -> Volume Up
      // Note: Consumer control media keys can be used depending on your core library setup
      Keyboard.write(KEY_MEDIA_VOLUME_UP); 
    } else {
      // Turned Counter-Clockwise -> Volume Down
      Keyboard.write(KEY_MEDIA_VOLUME_DOWN);
    }
  }
  lastClkState = currentClkState;

  // 5. Handle Encoder Button Press (Mute Toggle)
  if (digitalRead(ENCODER_SW) == LOW) {
    Keyboard.write(KEY_MEDIA_MUTE);
    delay(300); // Debounce delay
  }

  delay(10);
}
