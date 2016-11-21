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

Powerled pl;
Interface hw;
SimpleTimer st;

bool systemIsUp = false;
bool systemTurnedOn = false;
bool rpiFlagProblem = false;



// Time oriented functions

void rpiFlagProblemMode() {
  if (systemIsUp == false && systemTurnedOn == true) {
    rpiFlagProblem = true;
    pl.setState(LED_ON);
  }
  
}

void turnPowerSupplyOff() {
  pl.setState(LED_OFF);
  RPI_SHUTDOWN_REQUEST_CLEAR;
  POWER_SUPPLY_OFF;
  
  systemIsUp = false;
  systemTurnedOn = false;
  rpiFlagProblem = false;
}

// External oriented events function

#define RPI_FAILURE_TIMEOUT_MINUTES     180000L   // defined for 3 minutes
#define AFTER_RPI_SHUTDOWN_POWEROFF_MS  8000      // 8 secounds little wait until power off

void turnedOn() {
  if ( ~systemTurnedOn ) {
    pl.setFrequency(LED_CYCLE_1S);
    pl.setState(LED_BLINKING);
    RPI_SHUTDOWN_REQUEST_CLEAR;
    POWER_SUPPLY_ON;

    systemIsUp = false;
    systemTurnedOn = true;
    rpiFlagProblem = false;

    st.setTimeout(RPI_FAILURE_TIMEOUT_MINUTES, &rpiFlagProblemMode);
  }
}

void rpiUp() {
  if (systemTurnedOn) pl.setState(LED_ON);

    systemIsUp = true;
    rpiFlagProblem = false;
}

void turnedOff() {
  if ( systemTurnedOn ) {
    pl.setFrequency(LED_CYCLE_256MS);
    pl.setState(LED_BLINKING);
    RPI_SHUTDOWN_REQUEST;
    systemTurnedOn = false;
    if (rpiFlagProblem == true) turnPowerSupplyOff();
  }
}

void rpiDown() {
  if ( systemIsUp ) {
    systemIsUp = false;
    st.setTimeout(AFTER_RPI_SHUTDOWN_POWEROFF_MS, &turnPowerSupplyOff);
  }
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
