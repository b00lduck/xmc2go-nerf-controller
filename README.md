# XMC2GO XMC1100 Nerf controller

## Dependencies

### ARM gcc toolchain

Put to your PATH:
 - arm-none-eabi-gcc
 - arm-none-eabi-as
 - arm-none-eabi-ld
 - arm-none-eabi-objc


### XMC libraries

You will need to put the "XMC_Peripheral_Library_v2.1.8" into the root folder.
Due to unclear licensing i omitted this folder in the repository.

### JLink

In order to flash you need JLink (i.e. JLink_Linux_V612_x86_64 on linux). Put JLinkExe to your PATH.

## Build

make clean && make && sudo make flash

## Resource usage breakdown

### Timers

 - CCU40 PWM flywheel motor 1
 - CCU41 PWM flywheel motor 2
 - CCU42 PWM pusher motor
 - CCU43 -
 
   
### GPIO  
 
 - P0_0  Light barrier ammo
 - P0_5  Button 1
 - P0_6  PWM flywheel motor 1 (AF CCU40)
 - P0_7  PWM flywheel motor 2 (AF CCU41)
 - P0_8  PWM pusher motor     (AF CCU42) 
 - P0_9  braking relay pusher motor
 - P0_14 LED3
 - P0_15 LED4
   
 - P1_0  XMC2GO LED2
 - P1_1  XMC2GO LED1
 
 - P2_0  Button 2
 - P2_6  speed potentiometer (ADC G0 CH0)
 - P2_7  Tachometer fylwheel 1
 - P2_9  Battery voltage sense (ADC G0 CH2) 
 - P2_10 Tachometer fylwheel 2
 - P2_11 Button 3
 
## Schematics

coming soon

## Bill of materials

 1x XMC2GO (Infineon XMC1100 board)
 3x IRF3708 (Logic-Level MOSFET for 3.3V Logic)
 10x 100nF ceramic
 3x Schottky flyback diode (i.E. BYS 21-45)
 2x CNY70 
 1x LM358N
 1x photoelectric barrier (TEMIC K153P)
 ?x Resistors
 ?x Chokes

 1x 12v Relay (one pole single throw) 6A DC
 
 1x DC Motor "Honeybadger"
 2x DC Motor "Rhino"
 1x 3s LiPo battery pack
 1x Fuse holder with 6.3A T fuse
 1x Power switch
 some 1,5mm² wires (red and black) for power lines
 some colored thin wires for signalling
 
 
