//
// Created by dennis on 29-03-21.
//

#ifndef TEENSYDRUM_HEADER_H
#define TEENSYDRUM_HEADER_H

#include "consts.h"
#include "AudioDeclarations.h"


void setGains();
void setValues();
double logspace(double start, double stop, int n, int N);
void calculateBpm();
void setDelayTime(int analogDelay);
void initMixersFx();
void midiClock();
void ClockOut96PPQN(uint32_t * tick);
void setLEDs();
void playSounds();
void handleStep();
void readButtons();
void setReverb();
void setMasterFilter();
void setupStepButtons();
void setupInstrumentButtons();
#endif //TEENSYDRUM_HEADER_H
