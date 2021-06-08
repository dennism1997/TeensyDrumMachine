//
// Created by dennis on 30-03-21.
//

#ifndef TEENSYDRUM_SAMPLER_H
#define TEENSYDRUM_SAMPLER_H

#include <Arduino.h>
#include <SD.h>
#include "consts.h"

#include <Audio.h>

class Sampler {
public:
    void playInstrument(byte instrument);
    void init();

private:
    void searchSamples();
    void searchInstrumentSamples(const char* instrument, byte index);
    void addSample(const char* path, byte instrumentIndex);
};


#endif //TEENSYDRUM_SAMPLER_H
