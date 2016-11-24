RpiPowerController
==

### Description
* With this sources you can build a power manager for Raspberry Pi boards.

### RaspberryPi Setup
* This device has to be used with PowerBlock installed in the Raspberry side. This sources controls shutdown command and inform the PowerController when linux is started throught 2 raspberry GPIO pins.To install it in your Raspberry Pi execute the following commands on bash.

#### Bash Commands
      $ sudo apt-get update
      $ sudo apt-get upgrade -y</code>
      $ sudo apt-get install -y 
      $ git cmake g++-4.9</code>

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

Send comments, suggestions and bug reports to:

https://github.com/vpanarello/SaturnUSB/issues

Or fork the code on github:

https://github.com/vpanarello/SaturnUSB

