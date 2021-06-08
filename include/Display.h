//
// Created by dennis on 23-04-21.
//

#ifndef TEENSYDRUM_DISPLAY_H
#define TEENSYDRUM_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "consts.h"

class Display {
private:
    Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

    void displaySteps();

    void displayLoadingScreen();

public:
    void init() {
        if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
            Serial.println(F("SSD1306 allocation failed"));
            for (;;); // Don't proceed, loop forever
        }
        display.clearDisplay();
        displayLoadingScreen();
        display.display();
    }

    void update();
};


#endif //TEENSYDRUM_DISPLAY_H
