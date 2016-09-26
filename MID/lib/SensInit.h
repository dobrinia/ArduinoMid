//
// Created by Angel Zaprianov on 16.9.2016 г..
//

#ifndef ARDUINOMID_SENSINIT_H
#define ARDUINOMID_SENSINIT_H


//
// Read Tachometer
#include "sens/RpmSens.h"
//
// Read SpeedHub
#include "sens/VssSens.h"
//
//
#include "sens/EcuSens.h"
//
// Screen back-light sensor
#include "sens/DimSens.h"
//
// Temperature
#include "sens/TmpSens.h"
//
// Adding Alphine emulator
#include "sens/SensStrn.h"
//
// Read inside temperature
#include "DispInfo.h"
//void handleBackLight(){
//
//}

void sensorsInit() {
    //
    // No Interrupts
    cli();
    //
    // Sense Basic car sensors ;)
    sensRpm();
    sensVss();
    sensEcu();
    //
    // Sens Extra
    sensAvr();
    sensTmp();
    sensCon();

    sensStr(); // Sens steering

    sensDim(); // Dim display
    //
    // Interrupts
    sei();
}

#endif //ARDUINOMID_SENSINIT_H
