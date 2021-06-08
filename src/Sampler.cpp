//
// Created by dennis on 30-03-21.
//

#include "Sampler.h"

#include "samples/AudioSampleHihatclosedw.h"
#include "samples/AudioSampleHihatopen1wa.h"
#include "samples/AudioSampleKick.h"

extern AudioPlayMemory          playMem6; //xy=178,453
extern AudioPlayMemory          playMem7; //xy=178,494
extern AudioPlayMemory          playMem8; //xy=178,534
extern AudioPlayMemory          playMem5; //xy=179,411
extern AudioPlayMemory          playMem2; //xy=180,282
extern AudioPlayMemory          playMem3; //xy=180,323
extern AudioPlayMemory          playMem4; //xy=180,363
extern AudioPlayMemory          playMem1;       //xy=181,240

char instrumentPaths[AMOUNT_INSTRUMENTS][MAX_SAMPLES][60];

void Sampler::playInstrument(byte instrument) {
    switch (instrument) {
        case 0:
            playMem1.play(AudioSampleKick);
            break;
        case 1:
            playMem2.play(AudioSampleHihatclosedw);
            break;
        case 2:
            playMem3.play(AudioSampleHihatopen1wa);
            break;
    }
}

void Sampler::init() {
    const byte SD_Pin = 10;

    if (!SD.begin(SD_Pin)) {
        Serial.println("Card failed, or not present");
        for (;;); // Don't proceed, loop forever
    }
    searchSamples();

}

void Sampler::searchSamples() {
    searchInstrumentSamples("/kick", 0);
    searchInstrumentSamples("/HH_C", 1);
    searchInstrumentSamples("/HH_O", 2);
}

void Sampler::addSample(const char *path, byte instrumentIndex) {
    for (byte i = 0; i < MAX_SAMPLES; i++) {
        if (instrumentPaths[instrumentIndex][i][0] == '\0') {
            strcpy(instrumentPaths[instrumentIndex][i], path);
            break;
        }
    }
}

void Sampler::searchInstrumentSamples(const char* instrument, byte index) {
    File dir = SD.open(instrument);
    File file;
    char path[60];

    while (true) {
        file = dir.openNextFile();
        if (!file) {
            break;
        }
        strcpy(path, instrument);
        strcat(path, "/");
        strcat(path, file.name());
        addSample(path, index);
        file.close();
        Serial.println(path);

    }
    dir.close();
}