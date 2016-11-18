/*
*  PowerLed - Led with fading effect controller (for Arduino)
*
*        File: powerled.cpp
*  Created on: 09/08/2016
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

Powerled::Powerled () {

}

Powerled::Powerled (uint8_t ledPin) {
  this->intensity = 0;
  this->increment = false;
  this->ledPin = ledPin;
  this->frequency = LED_CYCLE_1S;
  this->nextClock = millis();
  this->state = LED_OFF;

  SET_TO_LOW_PIN(ledPin);
  SET_OUTPUT_PIN(ledPin);

}
Powerled::~Powerled() {
}

// 0: off, 1: on, 2: blink
void Powerled::setState(uint8_t state) {
  this->state = state;
}

void Powerled::setFrequency(uint8_t frequency) {
  this->frequency = frequency;
}

void Powerled::thread() {

  if (millis() > nextClock) {
    nextClock = millis() + this->frequency;

    if (increment && intensity < 255) intensity++;
    else if (!increment && intensity > 0) intensity--;

    analogWrite(ledPin, intensity);

    if (intensity > 254) {
      if (this->state == LED_OFF || this->state == LED_BLINKING) increment = false;
    }
    else if (intensity < 1) {
      if (this->state == LED_ON || this->state == LED_BLINKING) increment = true;
    }
  }
}
