#include "LedControl.h"
#include <pgmspace.h> // For PROGMEM to store font in flash

// Define the ESP32-C3 pins connected to the MAX7219
// Note that the ones here are NOT recommended ones and are merely the ones used by the author
// const int DIN_PIN = 1;
// const int CLK_PIN = 3;
// const int CS_PIN  = 2;

const int NUM_DEVICES = 4;
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, NUM_DEVICES);

// --- FONT DATA  ---
const byte FONT[][5] PROGMEM = { 
  {0x00, 0x00, 0x00, 0x00, 0x00}, // Space
  {0x00, 0x00, 0x5F, 0x00, 0x00}, // !
  {0x00, 0x07, 0x00, 0x07, 0x00}, // "
  {0x14, 0x7F, 0x14, 0x7F, 0x14}, // #
  {0x24, 0x2A, 0x7F, 0x2A, 0x12}, // $
  {0x23, 0x13, 0x08, 0x64, 0x62}, // %
  {0x36, 0x49, 0x55, 0x22, 0x50}, // &
  {0x00, 0x05, 0x03, 0x00, 0x00}, // '
  {0x00, 0x1C, 0x22, 0x41, 0x00}, // (
  {0x00, 0x41, 0x22, 0x1C, 0x00}, // )
  {0x14, 0x08, 0x3E, 0x08, 0x14}, // *
  {0x08, 0x08, 0x3E, 0x08, 0x08}, // +
  {0x00, 0x50, 0x30, 0x00, 0x00}, // ,
  {0x08, 0x08, 0x08, 0x08, 0x08}, // -
  {0x00, 0x60, 0x60, 0x00, 0x00}, // .
  {0x20, 0x10, 0x08, 0x04, 0x02}, // /
  {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
  {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
  {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
  {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
  {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
  {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
  {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
  {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
  {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
  {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
  {0x00, 0x36, 0x36, 0x00, 0x00}, // :
  {0x00, 0x56, 0x36, 0x00, 0x00}, // ;
  {0x08, 0x14, 0x22, 0x41, 0x00}, // <
  {0x14, 0x14, 0x14, 0x14, 0x14}, // =
  {0x00, 0x41, 0x22, 0x14, 0x08}, // >
  {0x02, 0x01, 0x51, 0x09, 0x06}, // ?
  {0x32, 0x49, 0x79, 0x41, 0x3E}, // @
  {0x7E, 0x11, 0x11, 0x11, 0x7E}, // A
  {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
  {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
  {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
  {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
  {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
  {0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
  {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
  {0x00, 0x41, 0x7F, 0x41, 0x00}, // I
  {0x20, 0x40, 0x41, 0x3F, 0x01}, // J
  {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
  {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
  {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
  {0x7F, 0x04, 0x08, 0x10, 0x7F}, // N
  {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
  {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
  {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
  {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
  {0x46, 0x49, 0x49, 0x49, 0x31}, // S
  {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
  {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
  {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
  {0x3F, 0x40, 0x38, 0x40, 0x3F}, // W
  {0x63, 0x14, 0x08, 0x14, 0x63}, // X
  {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
  {0x61, 0x51, 0x49, 0x45, 0x43}  // Z
};

byte getCharColumn(char character, int col) {
  if (col < 0 || col > 4) return 0x00;
  int charIndex = character - 32;
  if (charIndex < 0 || charIndex >= (sizeof(FONT) / sizeof(FONT[0]))) {
    charIndex = 0; // Default to space
  }
  return pgm_read_byte(&(FONT[charIndex][col]));
}

String message = "HELLO WORLD!! ESP32-C3";
const int CHAR_WIDTH = 5;
const int CHAR_SPACING = 1;
const int TOTAL_CHAR_PIXEL_WIDTH = CHAR_WIDTH + CHAR_SPACING;

const int MAX_MESSAGE_LEN = 50;
byte messageBuffer[MAX_MESSAGE_LEN * TOTAL_CHAR_PIXEL_WIDTH];
int messageBufferLen = 0;

int scrollOffset; 
unsigned long lastScrollTime = 0;
int scrollDelay = 75; // Milliseconds (speed)

const int DISPLAY_WIDTH_COLUMNS = NUM_DEVICES * 8;

void setup() {
  for (int i = 0; i < NUM_DEVICES; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 5); // Brightness (0-15)
    lc.setScanLimit(i, 7); 
    lc.clearDisplay(i);
  }

  buildMessageBuffer();
  scrollOffset = -DISPLAY_WIDTH_COLUMNS; 
}

void buildMessageBuffer() {
  messageBufferLen = 0;
  for (int i = 0; i < message.length(); i++) {
    char c = toupper(message.charAt(i));
    for (int col = 0; col < CHAR_WIDTH; col++) {
      if (messageBufferLen < sizeof(messageBuffer)) {
        messageBuffer[messageBufferLen++] = getCharColumn(c, col);
      }
    }
    for (int s = 0; s < CHAR_SPACING; s++) {
      if (messageBufferLen < sizeof(messageBuffer)) {
        messageBuffer[messageBufferLen++] = 0x00; // Blank column
      }
    }
  }
}

void displayMarquee() {
  for (int screenCol = 0; screenCol < DISPLAY_WIDTH_COLUMNS; screenCol++) {
    int device = screenCol / 8;
    int deviceCol = screenCol % 8;

    int currentMessageCol = scrollOffset + screenCol;
    byte colData = 0x00;

    if (currentMessageCol >= 0 && currentMessageCol < messageBufferLen) {
      colData = messageBuffer[currentMessageCol];
    }
    
    lc.setColumn(device, 7 - deviceCol, colData); 
  }
}

void loop() {
  if (millis() - lastScrollTime > scrollDelay) {
    lastScrollTime = millis();

    displayMarquee();
    scrollOffset++; // Increment to scroll text from RIGHT to LEFT visually
    
    if (scrollOffset >= messageBufferLen) {
      scrollOffset = -DISPLAY_WIDTH_COLUMNS; // Reset to re-enter from the right
    }
  }
}
