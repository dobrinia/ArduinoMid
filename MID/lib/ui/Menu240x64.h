//
// Created by Angel Zaprianov on 23.2.2017 г..
//

#ifndef ARDUINO_MID_MENU240X64_H
#define ARDUINO_MID_MENU240X64_H

#include <Arduino.h>
#include "../../MID.h"
#include "../MenuBtn.h"
#include "../MenuBase.h"
#include <MenuBackend.h>


#define MENU_NAME_1 "Home"
#define MENU_NAME_11 "Dash"
#define MENU_NAME_12 "Edit"
#define MENU_NAME_13 "Info"

#define MENU_NAME_121 "VSS"
#define MENU_NAME_122 "RPM"
#define MENU_NAME_123 "DST"
#define MENU_NAME_124 "ECU"

#define MENU_NAME_2 "Trip"
#define MENU_NAME_21 "Race"
#define MENU_NAME_3 "Fuel"
#define MENU_NAME_4 "State"


/**
 *
 */
class Menu240x60 : public MenuUiInterface {

    MenuBackend menu;
    MenuBtn *btn;
    MenuItem
    //
    // Main menu
            mainMenu,
            gagesMenu,
            setupMenu,
            aboutMenu,

            vssSet,
            rpmSet,
            dstSet,
            ecuSet,
    //
    // Trip
            tripMenu,
            raceMenu,
    //
    // Fuel tank
            fuelMenu,
    //
    // States
            statMenu
    //
    // Sprint
//            gamesMenu
    ;


public:
/**
 * Menu constructor
 */
    Menu240x60(MenuBtn &_b) : btn(&_b), menu(menuUseEvent, menuChangeEvent),//  base menu initialization

            //
            // Main menu
                              mainMenu(MenuItem(MENU_NAME_1)),
                              gagesMenu(MenuItem(MENU_NAME_11)),
                              setupMenu(MenuItem(MENU_NAME_12)),

                              vssSet(MenuItem(MENU_NAME_121)),
                              rpmSet(MenuItem(MENU_NAME_122)),
                              dstSet(MenuItem(MENU_NAME_123)),
                              ecuSet(MenuItem(MENU_NAME_124)),

                              aboutMenu(MenuItem(MENU_NAME_13)),
            //
            // Trip menu
                              tripMenu(MenuItem(MENU_NAME_2)),
                              raceMenu(MenuItem(MENU_NAME_21)),
            //
            // Fuels menu
                              fuelMenu(MenuItem(MENU_NAME_3)),
            //
            // Servicing menu
                              statMenu(MenuItem(MENU_NAME_4)) {
    }

    void setup(void) {
        menu.getRoot()
                .add(mainMenu).add(tripMenu).add(fuelMenu).add(statMenu);
        statMenu.add(mainMenu);

        mainMenu.addRight(gagesMenu).addRight(setupMenu).addRight(aboutMenu);
        gagesMenu.add(mainMenu);
        setupMenu.add(vssSet).add(rpmSet).add(dstSet).add(ecuSet);
        ecuSet.add(setupMenu);
        aboutMenu.add(mainMenu);
        aboutMenu.addRight(mainMenu);

        tripMenu.addRight(raceMenu);
        raceMenu.addRight(tripMenu);
        raceMenu.add(tripMenu);

        menu.moveDown();
        MidCursorMenu = 1;

    }

    MenuBackend getMB() {
        return menu;
    }


    void menuChanged(MenuChangeEvent change) {
        //
        // Check is navigation is active
        if (btn->getNavigationState() == 0) {
            return;
        }

        //
        // Resolve
        MenuItem curMenuItem = change.to; //get the destination menu
        const char *curMenuName = curMenuItem.getName();

        Serial.println(curMenuName);


        if (curMenuName == MENU_NAME_1) {
            MidCursorMenu = 1;
            //
            // Sub menu / Dashboard
        } else if (curMenuName == MENU_NAME_11) {
            MidCursorMenu = 11;
            //
            // Settings
        } else if (curMenuName == MENU_NAME_12) {
            MidCursorMenu = 12;
        } else if (curMenuName == MENU_NAME_121) {
            MidCursorMenu = 121;
        } else if (curMenuName == MENU_NAME_122) {
            MidCursorMenu = 122;
        } else if (curMenuName == MENU_NAME_123) {
            MidCursorMenu = 123;
        } else if (curMenuName == MENU_NAME_124) {
            MidCursorMenu = 124;
            //
            // Information
        } else if (curMenuName == MENU_NAME_13) {
            MidCursorMenu = 13;
            //
            // Trip
        } else if (curMenuName == MENU_NAME_2) {
            MidCursorMenu = 2;
        } else if (curMenuName == MENU_NAME_21) {
            MidCursorMenu = 21;
            //
            // Fuel
        } else if (curMenuName == MENU_NAME_3) {
            MidCursorMenu = 3;
            //
            // State
        } else if (curMenuName == MENU_NAME_4) {
            MidCursorMenu = 4;
        }
    }

    void moveUp() {
        menu.moveDown();
        menu.use();

    }

    void moveDw() {
        menu.moveRight();
        menu.use();

    }
};


#endif //ARDUINOMID_MENU240X64_H