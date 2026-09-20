#include <Arduino.h>
#include <Keyboard.h>

// Pin Definitions for Key Matrix (adjust rows and columns to match your hardware wiring)
const int NUM_ROWS = 4;
const int NUM_COLS = 4;

const byte ROW_PINS[NUM_ROWS] = {9, 8, 7, 6}; // Connect to row pinouts
const byte COL_PINS[NUM_COLS] = {5, 4, 3, 2}; // Connect to column pinouts

// Keymap definition (Characters sent when keys are pressed)
char keymap[NUM_ROWS][NUM_COLS] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'0', '.', '=', '+'}
};

bool lastKeyState[NUM_ROWS][NUM_COLS];

void setup() {
  // Initialize Control Keys and Keyboard library
  Keyboard.begin();

  // Initialize Row and Column Pins
  for (int r = 0; r < NUM_ROWS; r++) {
    pinMode(ROW_PINS[r], INPUT_PULLUP);
  }
  
  for (int c = 0; c < NUM_COLS; c++) {
    pinMode(COL_PINS[c], OUTPUT);
    digitalWrite(COL_PINS[c], HIGH);
  }

  // Set initial states to unpressed (HIGH with pull-up)
  for (int r = 0; r < NUM_ROWS; r++) {
    for (int c = 0; c < NUM_COLS; c++) {
      lastKeyState[r][c] = HIGH;
    }
  }
}

void loop() {
  // Scan Key Matrix
  for (int c = 0; c < NUM_COLS; c++) {
    digitalWrite(COL_PINS[c], LOW); // Pull column down

    for (int r = 0; r < NUM_ROWS; r++) {
      bool currentState = digitalRead(ROW_PINS[r]);

      // Check if button state changed (pressed)
      if (currentState == LOW && lastKeyState[r][c] == HIGH) {
        // Send keystroke over USB HID
        Keyboard.press(keymap[r][c]);
        delay(50); // Debounce delay
      } 
      // Check if button released
      else if (currentState == HIGH && lastKeyState[r][c] == LOW) {
        Keyboard.release(keymap[r][c]);
        delay(50);
      }

      lastKeyState[r][c] = currentState;
    }

    digitalWrite(COL_PINS[c], HIGH); // Reset column
  }

  delay(10); // Loop polling delay
}
