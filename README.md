# MAX7219-ESP32-C3-Marquee
ESP32-C3 &amp; MAX7219 Scrolling Marquee Text (4-Chain)

This project demonstrates how to create a scrolling marquee text display using an ESP32-C3 microcontroller and a chain of four MAX7219 8x8 LED dot matrix modules. While I - the author - have used the GPIOs 1, 2, and 3 these are commented out and need to be edited.

## Features

*   Displays scrolling text (right-to-left) on a 32x8 LED matrix (4 chained MAX7219 modules).
*   Customizable message text.
*   Adjustable scroll speed.
*   Includes a basic 5x7 pixel font embedded in the code (PROGMEM).
*   Implemented in C++ for the Arduino framework.

## Hardware Requirements

*   **Microcontroller:** ESP32-C3 Development Board (e.g., ESP32-C3-DevKit-RUST-1 which was my case).
*   **Display:** 4 x MAX7219 8x8 LED dot matrix modules (the common type that can be daisy-chained).
*   **Power Supply:** An external 5V power supply capable of providing sufficient current for all four MAX7219 modules. 
*   **Jumper Wires:** For connecting the components.

## Software Requirements

*   **Arduino IDE** (with ESP32 core installed).
*   **`LedControl` Library:** By Eberhard Fahle.
    *   Install via Arduino IDE: `Sketch` -> `Include Library` -> `Manage Libraries...` -> Search for "LedControl" and install.

## Wiring Connections
**Note on GPIO1 (TXD0):**
GPIO1 is typically used as `TXD0` for the default UART0 on the ESP32-C3. This UART is used for programming and `Serial.print()` output. Using GPIO1 for the MAX7219 DIN pin might interfere with Serial Monitor functionality or cause issues during code upload if the MAX7219 is actively driven. GPI01 was choosen because I was missing a bigger header. I advise you **not** to use it.


## Setup and Usage

1.  **Connect Hardware:** Wire the ESP32-C3, MAX7219 modules, and power supply according to the "Wiring Connections" section.
2.  **Install Library:** Ensure the `LedControl` library is installed in your Arduino IDE.
3.  **Open Code:** Open the `.ino` sketch file in the Arduino IDE.
4.  **Board Selection:** Select your ESP32-C3 board from the `Tools` -> `Board` menu.
5.  **Customize:**
    *   Modify the `String message = "YOUR TEXT HERE  ";` line to change the scrolling text. Add trailing spaces for a gap before repetition.
    *   Adjust `int scrollDelay = 75;` to change the scrolling speed (lower value = faster).
    *   Replace the consts DIN_PIN, CLK_PIN and CS_PIN with the correct values and uncomment
6.  **Upload:** Compile and upload the sketch to your ESP32-C3.
