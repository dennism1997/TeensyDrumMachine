//
// Created by dennis on 30-03-21.
//

#ifndef TEENSYDRUM_AUDIODECLARATIONS_H
#define TEENSYDRUM_AUDIODECLARATIONS_H
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//<editor-fold desc="Audio Cords">
// GUItool: begin automatically generated code
AudioPlayMemory          playMem6; //xy=178,453
AudioPlayMemory          playMem7; //xy=178,494
AudioPlayMemory          playMem8; //xy=178,534
AudioPlayMemory          playMem5; //xy=179,411
AudioPlayMemory          playMem2; //xy=180,282
AudioPlayMemory          playMem3; //xy=180,323
AudioPlayMemory          playMem4; //xy=180,363
AudioPlayMemory          playMem1;       //xy=181,240
AudioMixer4              mixer2; //xy=432,477
AudioMixer4              mixer1;         //xy=434,306
AudioMixer4              mixer3; //xy=440,592
AudioMixer4              mixer5; //xy=440,745
AudioMixer4              mixer6; //xy=440,820
AudioMixer4              mixer4; //xy=441,664
AudioMixer4              mixerDelay; //xy=586,792
AudioMixer4              mixerReverb; //xy=591,640
AudioMixer4              mixerPreFx; //xy=613,384
AudioFilterStateVariable delayFilter;        //xy=758,799
AudioFilterStateVariable reverbFilter;        //xy=778.0000610351562,679
AudioFilterStateVariable filterMaster;        //xy=781,392
AudioEffectDelay         delayFx;         //xy=916,802
AudioEffectFreeverb      freeverb1;      //xy=926.444580078125,694.111083984375
AudioMixer4              mixerFx;         //xy=1180,605
AudioMixer4              mixerMaster;         //xy=1364,382
AudioAmplifier           volumeAmp;           //xy=1552,443
AudioOutputI2S           i2s1;           //xy=1737,478
AudioAnalyzePeak         peak1;          //xy=1742,361
AudioConnection          patchCord1(playMem6, 0, mixer2, 1);
AudioConnection          patchCord2(playMem6, 0, mixer4, 1);
AudioConnection          patchCord3(playMem6, 0, mixer6, 1);
AudioConnection          patchCord4(playMem7, 0, mixer2, 2);
AudioConnection          patchCord5(playMem7, 0, mixer4, 2);
AudioConnection          patchCord6(playMem7, 0, mixer6, 2);
AudioConnection          patchCord7(playMem8, 0, mixer2, 3);
AudioConnection          patchCord8(playMem8, 0, mixer4, 3);
AudioConnection          patchCord9(playMem8, 0, mixer6, 3);
AudioConnection          patchCord10(playMem5, 0, mixer2, 0);
AudioConnection          patchCord11(playMem5, 0, mixer4, 0);
AudioConnection          patchCord12(playMem5, 0, mixer6, 0);
AudioConnection          patchCord13(playMem2, 0, mixer1, 1);
AudioConnection          patchCord14(playMem2, 0, mixer3, 1);
AudioConnection          patchCord15(playMem2, 0, mixer5, 1);
AudioConnection          patchCord16(playMem3, 0, mixer1, 2);
AudioConnection          patchCord17(playMem3, 0, mixer3, 2);
AudioConnection          patchCord18(playMem3, 0, mixer5, 2);
AudioConnection          patchCord19(playMem4, 0, mixer1, 3);
AudioConnection          patchCord20(playMem4, 0, mixer3, 3);
AudioConnection          patchCord21(playMem4, 0, mixer5, 3);
AudioConnection          patchCord22(playMem1, 0, mixer1, 0);
AudioConnection          patchCord23(playMem1, 0, mixer3, 0);
AudioConnection          patchCord24(playMem1, 0, mixer5, 0);
AudioConnection          patchCord25(mixer2, 0, mixerPreFx, 1);
AudioConnection          patchCord26(mixer1, 0, mixerPreFx, 0);
AudioConnection          patchCord27(mixer3, 0, mixerReverb, 0);
AudioConnection          patchCord28(mixer5, 0, mixerDelay, 0);
AudioConnection          patchCord29(mixer6, 0, mixerDelay, 1);
AudioConnection          patchCord30(mixer4, 0, mixerReverb, 1);
AudioConnection          patchCord31(mixerDelay, 0, delayFilter, 0);
AudioConnection          patchCord32(mixerReverb, 0, reverbFilter, 0);
AudioConnection          patchCord33(mixerPreFx, 0, filterMaster, 0);
AudioConnection          patchCord34(delayFilter, 2, delayFx, 0);
AudioConnection          patchCord35(reverbFilter, 2, freeverb1, 0);
AudioConnection          patchCord36(filterMaster, 2, mixerMaster, 0);
AudioConnection          patchCord37(delayFx, 0, mixerFx, 1);
AudioConnection          patchCord38(freeverb1, 0, mixerFx, 0);
AudioConnection          patchCord39(mixerFx, 0, mixerMaster, 1);
AudioConnection          patchCord40(mixerMaster, volumeAmp);
AudioConnection          patchCord41(volumeAmp, peak1);
AudioConnection          patchCord42(volumeAmp, 0, i2s1, 0);
AudioConnection          patchCord43(volumeAmp, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=183,123
// GUItool: end automatically generated code
//</editor-fold>
#endif //TEENSYDRUM_AUDIODECLARATIONS_H
