/*
 *  Raspberry PI PowerController (Arduino attiny85)
 *
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

#include "powerled.h"
#include "interface.h"
#include "SimpleTimer.h"

#define OUT_LED 1

#define RPI_FAILURE_TIMEOUT_MINUTES     180000L   // defined for 3 minutes
#define AFTER_RPI_SHUTDOWN_POWEROFF_MS  8000      // 8 secounds little wait until power off
#define RE_TURN_ON_TIME_MS              3000      // 3 secounds wait to re turnon when the power switch was let "on" state when device was shutting down

Powerled pl;
Interface hw;
SimpleTimer st;

bool systemIsUp = false;
bool systemTurnedOn = false;
bool rpiBootUpDetectionFailure = false;


// External oriented events function

void rpiBootTimeOut() {
  if (systemIsUp == false && systemTurnedOn == true) {
    rpiBootUpDetectionFailure = true;
    systemIsUp = true;
    pl.setState(LED_ON);
  }  
}

void turnedOn() {
  if ( ~systemTurnedOn ) {
    
    systemTurnedOn = true;
    
    pl.setFrequency(LED_CYCLE_1S);
    pl.setState(LED_BLINKING);
    RPI_SHUTDOWN_REQUEST_CLEAR;
    POWER_SUPPLY_ON;
    
    st.setTimeout(RPI_FAILURE_TIMEOUT_MINUTES, &rpiBootTimeOut);
  }
}

void turnedOff() {
  if ( systemTurnedOn ) {
    
    systemTurnedOn = false;
    
    pl.setFrequency(LED_CYCLE_256MS);
    pl.setState(LED_BLINKING);
    RPI_SHUTDOWN_REQUEST;
    if (rpiBootUpDetectionFailure == true) turnPowerSupplyOff();
  }
}

void rpiUp() {
  if (systemTurnedOn == true && systemIsUp == false) {
    systemIsUp = true;
    rpiBootUpDetectionFailure = false;
    pl.setState(LED_ON);
  }
}

void turnPowerSupplyOff() {
  pl.setState(LED_OFF);
  RPI_SHUTDOWN_REQUEST_CLEAR;
  POWER_SUPPLY_OFF;
  systemIsUp = false;
  rpiBootUpDetectionFailure = false;
  
  if (systemTurnedOn == true) {
    systemTurnedOn = false;
    st.setTimeout(RE_TURN_ON_TIME_MS, &turnedOn);
  }
}

void rpiDown() {
    systemIsUp = false;
    st.setTimeout(AFTER_RPI_SHUTDOWN_POWEROFF_MS, &turnPowerSupplyOff);
}





void setup() {
  pl = Powerled(OUT_LED);
  
  // set callback functions
  hw.setFunctionTurnedOff(&turnedOff);
  hw.setFunctionTurnedOn(&turnedOn);
  hw.setRpiGoDown(&rpiDown);
  hw.setRpiGoUp(&rpiUp);
}

void loop() {
  pl.thread();
  hw.thread();
  st.thread();
}
