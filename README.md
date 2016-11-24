RpiPowerController
==

### Description
* With this sources you can build a power manager for Raspberry Pi boards. This device was build over an Atmel AtTiny85 microcontroller. Programmed using an Arduino Uno acting as ISP programmer. All code was developed using Arduino native IDE.

### Programming AtTiny with an Arduino Uno

* The folling tutorials teach how to programming an atTiny microcontroller just adjusting your Arduino IDE and uploading a ISP sketch to yout Arduino board connecting some pins between Arduino board and atTiny microcontroller.

- http://highlowtech.org/?p=1706

### RaspberryPi Setup
* This device has to be used with PowerBlock installed in the Raspberry side. This sources controls shutdown command and inform the PowerController device when Linux is already started through two Raspberry GPIO pins. To install it in your Raspberry Pi execute the following commands on Raspi bash.

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

![alt tag](https://raw.githubusercontent.com/vpanarello/RpiPowerController/master/img/powerModule_schematic.png)


### Author

Vagner Panarello <<vpanarello@gmail.com>>


### Contribute

* Send comments, suggestions and bug reports to:
https://github.com/vpanarello/RpiPowerController/issues

* Or fork the code on github:
https://github.com/vpanarello/RpiPowerController

