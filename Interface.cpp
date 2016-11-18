/*
 *  Raspberry PI PowerController (Arduino attiny85)
 *
 *        File: Interface.cpp
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

#include "interface.h"

Interface *Interface::thisInstance = 0;

ISR (PCINT0_vect) {
  Interface::pinChangeInterrupt();
}
void Interface::pinChangeInterrupt() {
  if (thisInstance) thisInstance->pinChanceIntHandler();
}

Interface::Interface () {
  SET_INPUT_PIN(IN_RPI);
  SET_INPUT_PIN(IN_SWITCH);
  SET_PULLUP_RESISTOR(IN_RPI);
  SET_PULLUP_RESISTOR(IN_SWITCH);

  POWER_SUPPLY_OFF;
  SET_OUTPUT_PIN(OUT_POWER_CONTROL);
  RPI_SHUTDOWN_REQUEST_CLEAR;
  SET_OUTPUT_PIN(OUT_RPI);

  MAP_PIN_CHANGE_INTERRUPT(IN_RPI);
  MAP_PIN_CHANGE_INTERRUPT(IN_SWITCH);

  ENABLE_PIN_CHANGE_INTERRUPT;

  thisInstance = this; // here set an this instance object reference for static member methods
}

// method timeout functionalities

void Interface::containerToCallback(void) {
  thisInstance->functionToReturn();
}

void Interface::functionToReturn(void) {

  bool turnedOn = IS_MAIN_SWITCH_ON;
  bool rpiIsUp = IS_RPI_SYSTEM_UP;

  if (turnedOn != this->lastStateSwitch) {
    if (IS_MAIN_SWITCH_ON) functionTurnedOn();
    else functionTurnedOff();
    this->lastStateSwitch = turnedOn;
  }

  if (rpiIsUp != this->lastStateRpi) {
    if (IS_RPI_SYSTEM_UP) rpiGoUp();
    else rpiGoDown();
    this->lastStateRpi = rpiIsUp;
  }
}

void Interface::setCallback(void (*pointerFunction)(void), long _delay) {
  this->pointerCallback = pointerFunction;
  this->callbackTimeout = millis() +  _delay;
}


// CallBack definition methods

void Interface::setFunctionTurnedOff(void (*funcPointer)(void)) {
  this->functionTurnedOff = funcPointer;
}
void Interface::setFunctionTurnedOn(void (*funcPointer)(void)) {
  this->functionTurnedOn = funcPointer;
}
void Interface::setRpiGoDown(void (*funcPointer)(void)) {
  this->rpiGoDown = funcPointer;
}
void Interface::setRpiGoUp(void (*funcPointer)(void)) {
  this->rpiGoUp = funcPointer;
}


// other methods

void Interface::pinChanceIntHandler() {
  if (!(this->pointerCallback)) this->setCallback(Interface::containerToCallback, DEBOUNCING_TIMEOUT_MS);
}

void Interface::thread() {
  if (millis() > this->callbackTimeout && this->pointerCallback) {
    this->pointerCallback();
    this->pointerCallback = 0;
  }
}

