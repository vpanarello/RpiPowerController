/*
 *  Raspberry PI PowerController (Arduino attiny85)
 *
 *        File: Interface.h
 *  Created on: 16/11/2016
 *      Author: Vagner Panarello (vpanarello@gmail.com)
 *
 *
 *
 * This library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser
 * General Public License along with this library; if not,
 * write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "Arduino.h"

// pinout function mapping & constants

#define OUT_RPI                        0   // chip pin 5
#define IN_RPI                         3   // chip pin 2 
#define IN_SWITCH                      2   // chip pin 7 (HIGH is OFF)
#define OUT_POWER_CONTROL              4   // chip pin 3

#define DEBOUNCING_TIMEOUT_MS          100

// general purpose macros

#define READ_STATE_PIN(pin)            (PINB >> pin) & 0x01
#define SET_OUTPUT_PIN(pin)            DDRB |= (1 << pin)
#define SET_INPUT_PIN(pin)             DDRB &= ~(1 << pin)
#define SET_TO_HIGH_PIN(pin)           PORTB |= (1 << pin)
#define SET_TO_LOW_PIN(pin)            PORTB &= ~(1 << pin)
#define SET_PULLUP_RESISTOR(pin)       PORTB |= (1 << pin)
#define TOGGLE_OUTPUT_PIN(pin)         PORTB ^= (1 << pin)

#define DISABLE_PIN_CHANGE_INTERRUPT   GIMSK &= ~(1 << PCIE)
#define ENABLE_PIN_CHANGE_INTERRUPT    GIMSK |= (1 << PCIE)
#define MAP_PIN_CHANGE_INTERRUPT(pin)  PCMSK |= (1 << pin) // Pin Change Mask

// specific purpose macros

#define POWER_SUPPLY_ON                SET_TO_HIGH_PIN(OUT_POWER_CONTROL)
#define POWER_SUPPLY_OFF               SET_TO_LOW_PIN(OUT_POWER_CONTROL)

#define RPI_SHUTDOWN_REQUEST           SET_TO_HIGH_PIN(OUT_RPI)
#define RPI_SHUTDOWN_REQUEST_CLEAR     SET_TO_LOW_PIN(OUT_RPI)

#define IS_RPI_SYSTEM_UP               ~READ_STATE_PIN(IN_RPI)
#define IS_MAIN_SWITCH_ON              ~READ_STATE_PIN(IN_SWITCH)



class Interface {

  private:

    // variables
    static Interface *thisInstance;
    long callbackTimeout;

    bool lastStateRpi = false;
    bool lastStateSwitch = false;

    // pointers
    void (*pointerCallback)(void);

    void (*functionTurnedOff)(void);
    void (*functionTurnedOn)(void);
    void (*rpiGoDown)(void);
    void (*rpiGoUp)(void);

    // methods
    void pinChanceIntHandler();
    ;

  public:
    // constructor
    Interface();

    // regular methods
    static inline void pinChangeInterrupt();
    void functionToReturn(void);
    static void containerToCallback(void);

    // setCallbacks methods
    void setCallback(void (*pointerFunction)(void), long _delay);

    void setFunctionTurnedOff(void (*funcPointer)(void));
    void setFunctionTurnedOn(void (*funcPointer)(void));
    void setRpiGoDown(void (*funcPointer)(void));
    void setRpiGoUp(void (*funcPointer)(void));

    void thread();

};

#endif /* INTERFACE_H_ */
