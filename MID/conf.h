//
// Created by Angel Zaprianov on 29.5.2017 ÃƒÆ’Ã¯Â¿Â½Ãƒâ€šÃ‚Â³..
//

#ifndef ARDUINO_MID_CONF_H
#define ARDUINO_MID_CONF_H

// To active LPG use one of:
//
// Serial communication with LPG
//  Also activates precise consumption calculation
#define ADT_FUEL_SYSTEM_SERIAL // comment to disable
//
// No detection of switch but use LPG
//#define LPG_INSTALLATION // uncomment

/***********************************************************************************************************************
 Car sensing class correction values
/** /
#define CAR_SENS_CUSTOM_CORRECTION   // Values form fast clock speed
// Note current set uses slow clock speed
// to use fast clock use values after "//"
//
// ECU Consumption correction
#define ECU_CORRECTION 346  //      346
//
// Speed correction
#define VSS_CORRECTION 1.5  //      3.767
//
// Revs correction
#define RPM_CORRECTION 75   //      33.767
//
// Distance correction
#define DST_CORRECTION 30766.58 //  15383.29  //   <sens:200> 15383.29
//
#define TRS_CORRECTION 0 // 0.064444 a proximity  6(~6)%
//
//#define VSD_SENS_DEBUG;
#define SCREEN_DEF_LIGHT 75 // 22
//
// Screen default value
#define SCREEN_GO_TO_DEF 15
/**/

/***********************************************************************************************************************
 Car sensing fuel correction values
/** /
//
#define CAR_SENS_CUSTOM_FUELS
//
// Default fuel state
// 0 - benzine
// 1 - propane-butane
#define DEFAULT_FUEL_STATE 0
#define DEFAULT_FUEL_USING 1  // defines default fuel system to use

//
// GASOLINE ENGINE CONFIG
//
// [CONFIRMED not tested over MID] For gas car use 3355 (1/14.7/730*3600)*10000
#define FUEL_BNZ_IFC 3355
#define FUEL_BNZ_CNS 107310 // 14.7*730*10

//
// LPG ENGINE CONFIG
//
//LPG mass/volume is 520-580gr/ltr depending on propane/butane mix

// LPG/air ratio:
// 15.8:1 if 50/50 propane/butate is usedMenu
// 15:1 if 100 propane is usedMenu
// 15.4 if 60/40 propane/butane is usedMenu
// experiments shows that something in middle should be usedMenu eg. 15.4:1 :)

// [CONFIRMED] For lpg(summer >20C) car use 4412 (1/15.4/540*3600)*10000
// // Note: this value is set without detection of fuel switch (mixed with benzine)
#define FUEL_LPG_IFC 4329
#define FUEL_LPG_CNS 83160  // 15.4*540*10 = 83160
#define LPG_SWTC_PIN 7
/**/

/***********************************************************************************************************************
 Car sensing Gears values
/** /
#define CAR_SENS_CUSTOM_GEARS
//
// Gears resolver constants
#define CAR_GEAR_Dia  616
#define CAR_GEAR_Pi  3.14
//
// Car's gears ratio
#define CAR_GEAR_G1  3.73
#define CAR_GEAR_G2  2.14
#define CAR_GEAR_G3  1.41
#define CAR_GEAR_G4  1.12
#define CAR_GEAR_G5  0.89
#define CAR_GEAR_G6  0.81
#define CAR_GEAR_FD   3.74 // Final drive
/**/
#endif //ARDUINO_MID_CONF_H
