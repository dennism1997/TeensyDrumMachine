//
// Created by dennis on 23-04-21.
//

#include "../include/Display.h"

extern bool instrumentSteps[MAX_PATTERN_LENGTH][AMOUNT_INSTRUMENTS];
extern byte step;
extern byte curInstrument;
extern byte patternOffset;

void Display::update() {
    display.clearDisplay();
    displaySteps();
    display.display();
}

void Display::displaySteps() {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.cp437(true);

    for (byte i = 0; i < AMOUNT_STEP_BUTTONS; i++) {
//        byte index = (i + patternOffset) % AMOUNT_STEP_BUTTONS;
        int index = i;
        if (index == step) {
            display.print("x");
        } else if (instrumentSteps[index][curInstrument]) {
            display.print("o");
        } else {
            display.print(".");
        }
    }
    display.setCursor(0, 20);
    display.print(patternOffset);
    display.print(":");
    display.print(step);
}


void Display::displayLoadingScreen() {
    display.setCursor(0,0);
    display.setTextSize(3);
    display.write("TeensyDrum 1.0");
}