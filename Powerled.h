/*
 *  PowerLed - Led with fading effect controller (for Arduino)
 *
 *        File: powerled.h
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

#ifndef POWERLED_H_
#define POWERLED_H_

#include "Arduino.h"

#define LED_OFF 0
#define LED_ON 1
#define LED_BLINKING 2


#define LED_CYCLE_256MS 1
#define LED_CYCLE_512MS 2
#define LED_CYCLE_768MS 3
#define LED_CYCLE_1S 4
#define LED_CYCLE_2S 8

#define READ_STATE_PIN(pin)            (PINB >> pin) & 0x01
#define SET_OUTPUT_PIN(pin)            DDRB |= (1 << pin)
#define SET_INPUT_PIN(pin)             DDRB &= ~(1 << pin)
#define SET_TO_HIGH_PIN(pin)           PORTB |= (1 << pin)
#define SET_TO_LOW_PIN(pin)            PORTB &= ~(1 << pin)
#define SET_PULLUP_RESISTOR(pin)       PORTB |= (1 << pin)
#define TOGGLE_OUTPUT_PIN(pin)         PORTB ^= (1 << pin)


class Powerled {

  private:
    uint8_t intensity;
    uint8_t ledPin;
    uint8_t frequency;
    uint8_t state;
    bool increment;
    long nextClock;

  public:
    Powerled (uint8_t);
    Powerled ();

    virtual ~Powerled();

    void setState(uint8_t state);
    void setFrequency(uint8_t frequency);
    void thread();
};

#endif /* POWERLED_H_ */
