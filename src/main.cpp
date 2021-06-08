#include <Arduino.h>

#include "consts.h"
#include "utils.h"

#include <uClock.h>
#include <Bounce2.h>
#include <Mux.h>
#include <Encoder.h>


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>




#include "header.h"
#include "Sampler.h"
Sampler sampler;

#include "Display.h"
Display display;

#include "AudioDeclarations.h"

extern AudioControlSGTL5000 sgtl5000_1;


//instruments
byte patternLength = 8;
const byte minPatternLength = 16;
byte curInstrument = 0;
bool instrumentSteps[MAX_PATTERN_LENGTH][AMOUNT_INSTRUMENTS];




//bpm and midi control
unsigned long bpmCountClock = 0;
double bpm = 127.0;
const byte lastBpmCount = 4;
double lastBpms[lastBpmCount] = {0.0, 0.0, 0.0, 0.0};
int lastBpmIndex = 0;
bool externalMidi = false;

byte step = 0;
byte patternOffset = 0;
byte midiStep = 0;
const byte midiStepsPerStep = 6; //http://midi.teragonaudio.com/tech/midispec/seq.htm


//inputs
byte stepButtonPins[AMOUNT_STEP_BUTTONS] = {32, 31, 29, 28, 27, 26, 25, 24};
Bounce2::Button stepButtons[AMOUNT_STEP_BUTTONS];
byte instrumentButtonPins[AMOUNT_INSTRUMENTS];
Bounce2::Button instrumentButtons[AMOUNT_INSTRUMENTS];
Encoder encoder(1, 3);
long encoderPos = -999;
Bounce2::Button encoderClick = Bounce2::Button();


using namespace admux;
//Mux mux1(Pin(A0, INPUT, PinType::Analog), Pinset(8, 9, 10, 11));
//Mux mux2(Pin(A0, INPUT, PinType::Analog), Pinset(8, 9, 10, 11));
//Mux mux3(Pin(A0, INPUT, PinType::Analog), Pinset(8, 9, 10, 11));
//Mux muxs[3] = {mux1, mux2, mux3};


//outputs
const byte stepLedPins[AMOUNT_STEP_BUTTONS] = {};

void setup() {
    display.init();
    for (int i = 0; i < MAX_PATTERN_LENGTH; i++) {
        instrumentSteps[i][1] = true;
        if ((i + 2) % 4 == 0) {
            instrumentSteps[i][2] = true;
        }
        if (i % 4 == 0) {
            instrumentSteps[i][0] = true;
        }
    }

    AudioMemory(100);


    sgtl5000_1.enable();
    sgtl5000_1.volume(0.7);

    // put your init code here, to run once:
//    usbMIDI.setHandleClock(midiClock);

    setupStepButtons();
//    setupInstrumentButtons();
    encoderClick.attach(17, INPUT_PULLUP);
    encoderClick.interval(5);
    encoderClick.setPressedState(LOW);

    sampler.init();

    uClock.setDrift(1);
    uClock.init();
    uClock.setClock96PPQNOutput(ClockOut96PPQN);
    uClock.setTempo((float) bpm);
    uClock.start();
    bpmCountClock = micros();

    initMixersFx();

    delay(100);
}

void setupInstrumentButtons() {
    for (byte i = 0; i < AMOUNT_INSTRUMENTS; i++) {
        Bounce2::Button b = Bounce2::Button();
        b.attach(instrumentButtonPins[i], INPUT_PULLUP);
        b.interval(5);
        b.setPressedState(LOW);
        instrumentButtons[i] = b;
    }
}

void setupStepButtons() {
    for (byte i = 0; i < AMOUNT_STEP_BUTTONS; i++) {
        Bounce2::Button b = Bounce2::Button();
        b.attach(stepButtonPins[i], INPUT_PULLUP);
        b.interval(5);
        b.setPressedState(LOW);
        stepButtons[i] = b;
    }
}


void loop() {
    readButtons();

//    setValues();

//    while (usbMIDI.read()) {
//        if (!externalMidi) {
//            externalMidi = true;
//            Serial.println("external midi mode");
//            uClock.stop();
//            step = 0;
//            midiStep = 0;
//            patternOffset = 0;
//        }
//        // ignore incoming messages
//    }
}

void setValues() {
    //  setGains();
    //  setMasterFilter();
    //  setReverb();
}

void setGains() {
//    for (byte i = 0; i < AMOUNT_INSTRUMENTS; i++) {
//        float analogGain = (mux1.read(i) / 8) / 127.0f;
//        float gainLevel = analogGain / 4.0f;
//        if (i < 4) {
//            mixer1.gain(i, gainLevel);
//        } else {
//            mixer2.gain(i, gainLevel);
//        }
//    }
//
//    mixerMaster.gain(0, mux1.read(0) / 1023.0f);
}

void setMasterFilter() {
//    float masterFilterFreq = (mux2.read(0) / 8) / 127.0f;
//    if (masterFilterFreq > 10) {
//        float q = map(masterFilterFreq, 0, 127, 707, 2000) / 1000.0f;
//        float freq = logspace(20, 20000, masterFilterFreq, 127);
//        //  filterMaster.frequency(masterFilterFreq);
//        filterMaster.frequency(freq);
//        filterMaster.resonance(q);
//    } else {
//        filterMaster.frequency(0);
//    }
}

void setReverb() {
//    float reverbWet = mux1.read(0) / 1023.0f;
//    if (reverbWet > 0.03) {
//        mixerReverb.gain(0, 1.0f - reverbWet);
//        mixerReverb.gain(1, reverbWet);
//    } else {
//        mixerReverb.gain(0, 1.0);
//        mixerReverb.gain(1, 0.0);
//    }
//
//    float roomsize = (mux1.read(0) / 8) / 127.0;
//    freeverb1.roomsize(roomsize);
//    float damping = (mux1.read(0) / 8) / 127.0;
//    freeverb1.damping(damping);
}

void readButtons() {
//    for (byte i = 0; i < AMOUNT_INSTRUMENTS; i++) {
//        instrumentButtons[i].update();
//        if (instrumentButtons[i].pressed()) {
//            curInstrument = i;
//        }
//    }

    for (byte i = 0; i < AMOUNT_STEP_BUTTONS; i++) {
        auto & button = stepButtons[i];
        button.update();
        if (button.pressed()) {
            int index = i + patternOffset;
            instrumentSteps[index][curInstrument] = !instrumentSteps[index][curInstrument];
        }
    }

    long newEncPos = encoder.read();
    if (newEncPos < encoderPos) {
    	encoderPos = newEncPos;
    } else if (newEncPos > encoderPos) {
    	encoderPos = newEncPos;
    }
    encoderClick.update();
    if (encoderClick.pressed()) {
    	
    }
}

void handleStep() {
//    Serial.println(step);
    step++;
    if (step >= patternLength) {
        // 4 beats are done
        step = 0;
        if (externalMidi) {
            calculateBpm();
        }

        patternOffset = (patternOffset + AMOUNT_STEP_BUTTONS) % patternLength;
    }
    display.update();
    playSounds();
    //  setLEDs();
    //  Serial.println(peak1.read());
}

void playSounds() {
    byte stepIndex = step + patternOffset;
    for (byte instrument = 0; instrument < AMOUNT_INSTRUMENTS; instrument++) {
        if (instrumentSteps[stepIndex][instrument]) {
            sampler.playInstrument(instrument);
        }
    }
}

void setLEDs() {
    for (byte i = 0; i < AMOUNT_STEP_BUTTONS; i++) {
        if (i == (step + patternOffset) % AMOUNT_STEP_BUTTONS && instrumentSteps[step + patternOffset][curInstrument]) {
            digitalWrite(stepLedPins[i], LOW);
        } else if (i == (step + patternOffset) % AMOUNT_STEP_BUTTONS ||
                   instrumentSteps[step + patternOffset][curInstrument]) {
            digitalWrite(stepLedPins[i], HIGH);
        } else {
            digitalWrite(stepLedPins[i], LOW);
        }
    }
}


void ClockOut96PPQN(uint32_t *tick) {
    if (externalMidi) {
        return;
    }
    midiStep++;
    if (midiStep >= 6) {
        midiStep = 0;
        handleStep();
    }
}

void midiClock() {
    if (!externalMidi) {
        return;
    }
    midiStep++;
    if (midiStep >= midiStepsPerStep) {
        midiStep = 0;
        handleStep();
    }
}

void initMixersFx() {
    mixer1.gain(0, 0.25);
    mixer1.gain(1, 0.25);
    mixer1.gain(2, 0.25);
    mixer1.gain(3, 0.25);

    mixer2.gain(0, 0.25);
    mixer2.gain(1, 0.25);
    mixer2.gain(2, 0.25);
    mixer2.gain(3, 0.25);

    mixer3.gain(0, 0);
    mixer3.gain(1, 0);
    //  mixer3.gain(2, 0);
    mixer3.gain(2, 0.8);
    mixer3.gain(3, 0);

    mixer4.gain(0, 0);
    mixer4.gain(1, 0);
    mixer4.gain(2, 0);
    mixer4.gain(3, 0);

    mixer5.gain(0, 0);
    mixer5.gain(1, 0);
    mixer5.gain(2, 0);
    mixer5.gain(3, 0);

    mixer6.gain(0, 0);
    mixer6.gain(1, 0);
    mixer6.gain(2, 0);
    mixer6.gain(3, 0);


    mixerPreFx.gain(0, 0.5);
    mixerPreFx.gain(1, 0.5);
    mixerReverb.gain(0, 0.5);
    mixerReverb.gain(1, 0.5);
    mixerDelay.gain(0, 0.5);
    mixerDelay.gain(1, 0.5);
    mixerFx.gain(0, 0.5);
    mixerFx.gain(1, 0.5);
    mixerMaster.gain(0, 0.5);
    mixerMaster.gain(1, 0.5);

    volumeAmp.gain(1.0);

    filterMaster.frequency(0.0);
    reverbFilter.frequency(200.0);
    reverbFilter.resonance(0.7);
    delayFilter.frequency(200);
    delayFilter.resonance(0.7);
    setDelayTime(0);

}

void setDelayTime(int analogDelay) {
    double msPerBeat = 60000.0 / bpm;
    double delayTime;
    if (analogDelay < 1023 / 7) { // 1/1
        delayTime = msPerBeat * 4;
    } else if (analogDelay < 2 * 1023 / 7) {
        delayTime = msPerBeat * 2;
    } else if (analogDelay < 3 * 1023 / 7) {
        delayTime = msPerBeat * 3 / 4;
    } else if (analogDelay < 4 * 1023 / 7) {
        delayTime = msPerBeat;
    } else if (analogDelay < 5 * 1023 / 7) {
        delayTime = msPerBeat / 2;
    } else if (analogDelay < 6 * 1023 / 7) {
        delayTime = msPerBeat / 4;
    } else {
        delayTime = msPerBeat / 8;
    }
    delayFx.delay(0, (float) delayTime);
}

void calculateBpm() {
    unsigned long curTime = micros();
    unsigned long diff = curTime - bpmCountClock;
    bpmCountClock = curTime;

    //  double quarterNote = (diff / 16.0);
    //  double bpm = 60000000.0 / quarterNote;
    double newBpm = 240000000.0 / diff;

    lastBpms[lastBpmIndex] = newBpm;
    lastBpmIndex = (lastBpmIndex + 1) % lastBpmCount;
    if (lastBpms[lastBpmCount - 1] > 60.0) {
        double avg = 0.0;
        for (double lastBpm : lastBpms) {
            avg += lastBpm;
        }
        bpm = avg / (double) lastBpmCount;
//        Serial.println(bpm);
    }

}




