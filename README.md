RpiPowerController
==

### Description

* With this sources you can build a power manager for Raspberry Pi boards. This device provide adicional control over Raspberry Pi power supply. On-Off switch when turned off invoke a shutdown command from linux before turning off power supply avoiding RPI file system to be corrupted.
This device was build over an Atmel AtTiny85 microcontroller. Programmed using an Arduino Uno acting as ISP programmer. All code was developed using Arduino native IDE. The link bellow demonstrats this device working.

- https://youtu.be/1K5IrAtzlaw

### Programming Microcontroller AtTiny with an Arduino Uno as ISP Programmer

* First of all clone this repository in your computer and using your Arduino IDE (my version was 1.6.5) open the file "sketch_nov16a.ino". All other parallel classes you be load together.

* Second, you have to configure your IDE, compile and flash it into an attiny85 microcontroller. In the tools menu of IDE you have to set the board as "ATtiny25/45/85", processor as ATtiny85, clock as 1MHz and programmer as "Arduino as ISP". This sources were tested using an atTiny85 running 1MHz without an external cristal oscilator. It is normal atTinys factory configuration. I recommend to use there configurations. If you have another config, you must change it in the ATtiny85 fuses configurations.

* I stronghly recomend you to follow tutorial below. There are a lot of additional information that will teach you to do this correctly.

- http://highlowtech.org/?p=1706
- https://www.youtube.com/watch?v=_ZL-YNOH_jA

* Third, Later the sources are already cloned, the IDE configured and your Arduino Uno is ready and connected to your ATtiny85 microcontroller. You can compile the sources and flash it into ATtiny. After this the microcontroller can be attached in the rest of circuit.


### RaspberryPi Setup

* This device has to me attached with an Raspberry Pi with already installed PowerBlock sources. PowerBlock sources were developed by third parties and adicional information can be find direct on this repository "https://github.com/petrockblog/PowerBlock"

* PowerBlock sources invoke shutdown linux command and inform the PowerController device when Linux is already started through two Raspberry pins (GPIO 17, 18) pins 11, 12. To install it in your Raspberry Pi execute the following commands on Raspi bash.

#### Bash Commands
      $ sudo apt-get update
      $ sudo apt-get upgrade -y
      $ sudo apt-get install -y 
      $ git cmake g++-4.9

      $ git clone git://github.com/petrockblog/PowerBlock.git
      $ cd PowerBlock
      $ make
      $ sudo make install
      $ sudo make installservice


### Schematics

![alt tag](https://raw.githubusercontent.com/vpanarello/RpiPowerController/master/img/powerModule_schematic_v2.png)

### Part list

* 1 - atTiny85 microcontroller
* 1 - IC 78L05 - 5V voltage regulator (TO-92)
* 1 - LM2596 Step Down Power Module DC-DC
"http://www.instructables.com/id/The-Introduction-of-LM2596-Step-Down-Power-Module-/"

* 2 - BC548 - NPN Transistors

* 1 - LED

* 1 - 10uF > 25V
* 1 - 1uF > 16V
* 1 - 100nF

* 1- 100 Kohm
* 1 - 47 Kohm
* 1 - 14 Kohm
* 2 - 10 Kohm
* 1 - 5 Kohm
* 1 - 4.7 Kohm
* 1 - 3.3 Kohm
* 1 - 220 ohm

### Assembly

* BE CAREFUL - The power module output have to be connect direct in the 5V and GND Pins of Raspberry GPIO. Before connect it you have to adjust the module output to get voltage of 5V. I recommend to put some hot glue in module trimmer pot to avoid over voltage accidents. You also have to pay attention of the correct pins of Raspberry Pi. Due 3.3V Raspberry logic levels, making a wrong pin connection can permanently damage your Raspberry Pi.


### Author

Vagner Panarello <<vpanarello@gmail.com>>


### Contribute

* Send comments, suggestions and bug reports to:
https://github.com/vpanarello/RpiPowerController/issues

* Or fork the code on github:
https://github.com/vpanarello/RpiPowerController

