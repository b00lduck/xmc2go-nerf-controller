EESchema Schematic File Version 2
LIBS:nerf-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:xmc2go
LIBS:nerf-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ULN2003-RESCUE-nerf U2
U 1 1 586BD8AB
P 6950 4550
F 0 "U2" H 6950 4650 50  0000 C CNN
F 1 "ULN2003" H 6950 4450 50  0000 C CNN
F 2 "" H 6950 4550 50  0000 C CNN
F 3 "" H 6950 4550 50  0000 C CNN
	1    6950 4550
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 586BD945
P 1500 4150
F 0 "R1" V 1580 4150 50  0000 C CNN
F 1 "36.5k" V 1500 4150 50  0000 C CNN
F 2 "" V 1430 4150 50  0000 C CNN
F 3 "" H 1500 4150 50  0000 C CNN
	1    1500 4150
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 586BDA96
P 1500 4650
F 0 "R2" V 1580 4650 50  0000 C CNN
F 1 "17.8k" V 1500 4650 50  0000 C CNN
F 2 "" V 1430 4650 50  0000 C CNN
F 3 "" H 1500 4650 50  0000 C CNN
	1    1500 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 586BDB70
P 2400 4600
F 0 "#PWR8" H 2400 4350 50  0001 C CNN
F 1 "GND" H 2400 4450 50  0000 C CNN
F 2 "" H 2400 4600 50  0000 C CNN
F 3 "" H 2400 4600 50  0000 C CNN
	1    2400 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 586BDBBA
P 2400 5600
F 0 "#PWR10" H 2400 5350 50  0001 C CNN
F 1 "GND" H 2400 5450 50  0000 C CNN
F 2 "" H 2400 5600 50  0000 C CNN
F 3 "" H 2400 5600 50  0000 C CNN
	1    2400 5600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 586BDBD4
P 1500 4800
F 0 "#PWR3" H 1500 4550 50  0001 C CNN
F 1 "GND" H 1500 4650 50  0000 C CNN
F 2 "" H 1500 4800 50  0000 C CNN
F 3 "" H 1500 4800 50  0000 C CNN
	1    1500 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR2
U 1 1 586BDBF0
P 1500 4000
F 0 "#PWR2" H 1500 3850 50  0001 C CNN
F 1 "+3.3V" H 1500 4140 50  0000 C CNN
F 2 "" H 1500 4000 50  0000 C CNN
F 3 "" H 1500 4000 50  0000 C CNN
	1    1500 4000
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR7
U 1 1 586BDC16
P 2400 4000
F 0 "#PWR7" H 2400 3850 50  0001 C CNN
F 1 "+3.3V" H 2400 4140 50  0000 C CNN
F 2 "" H 2400 4000 50  0000 C CNN
F 3 "" H 2400 4000 50  0000 C CNN
	1    2400 4000
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR9
U 1 1 586BDC35
P 2400 5000
F 0 "#PWR9" H 2400 4850 50  0001 C CNN
F 1 "+3.3V" H 2400 5140 50  0000 C CNN
F 2 "" H 2400 5000 50  0000 C CNN
F 3 "" H 2400 5000 50  0000 C CNN
	1    2400 5000
	1    0    0    -1  
$EndComp
$Comp
L RELAY_2RT K1
U 1 1 586BDCD7
P 8950 3400
F 0 "K1" H 8900 3800 50  0000 C CNN
F 1 "RELAY_2RT" H 9100 2900 50  0000 C CNN
F 2 "" H 8950 3400 50  0000 C CNN
F 3 "" H 8950 3400 50  0000 C CNN
	1    8950 3400
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR22
U 1 1 586BDEA8
P 8350 3650
F 0 "#PWR22" H 8350 3500 50  0001 C CNN
F 1 "+BATT" H 8350 3790 50  0000 C CNN
F 2 "" H 8350 3650 50  0000 C CNN
F 3 "" H 8350 3650 50  0000 C CNN
	1    8350 3650
	0    -1   -1   0   
$EndComp
$Comp
L D D1
U 1 1 586BDF6E
P 8400 3800
F 0 "D1" H 8400 3900 50  0000 C CNN
F 1 "D" H 8400 3700 50  0000 C CNN
F 2 "" H 8400 3800 50  0000 C CNN
F 3 "" H 8400 3800 50  0000 C CNN
	1    8400 3800
	0    1    1    0   
$EndComp
Text Notes 8450 2650 1    60   ~ 0
motor3 brake
Text Notes 8050 2600 1    60   ~ 0
LEDS
$Comp
L XMC2GO X1
U 1 1 586BE346
P 4900 4300
F 0 "X1" H 4950 4350 60  0000 C CNN
F 1 "XMC2GO" H 200 19500 60  0000 C CNN
F 2 "" H 200 19500 60  0001 C CNN
F 3 "" H 200 19500 60  0001 C CNN
	1    4900 4300
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 586BE4BC
P 5750 5550
F 0 "R5" V 5830 5550 50  0000 C CNN
F 1 "33k" V 5750 5550 50  0000 C CNN
F 2 "" V 5680 5550 50  0000 C CNN
F 3 "" H 5750 5550 50  0000 C CNN
	1    5750 5550
	0    -1   -1   0   
$EndComp
$Comp
L R R6
U 1 1 586BE5A5
P 6150 5550
F 0 "R6" V 6230 5550 50  0000 C CNN
F 1 "10k" V 6150 5550 50  0000 C CNN
F 2 "" V 6080 5550 50  0000 C CNN
F 3 "" H 6150 5550 50  0000 C CNN
	1    6150 5550
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR19
U 1 1 586BE5DF
P 6300 5550
F 0 "#PWR19" H 6300 5300 50  0001 C CNN
F 1 "GND" H 6300 5400 50  0000 C CNN
F 2 "" H 6300 5550 50  0000 C CNN
F 3 "" H 6300 5550 50  0000 C CNN
	1    6300 5550
	0    -1   -1   0   
$EndComp
$Comp
L +BATT #PWR16
U 1 1 586BE612
P 5600 5550
F 0 "#PWR16" H 5600 5400 50  0001 C CNN
F 1 "+BATT" H 5600 5690 50  0000 C CNN
F 2 "" H 5600 5550 50  0000 C CNN
F 3 "" H 5600 5550 50  0000 C CNN
	1    5600 5550
	0    -1   -1   0   
$EndComp
Text Notes 4000 2650 0    60   ~ 0
MOSFET gates
Text Notes 6250 2650 0    60   ~ 0
ammo light barrier
$Comp
L +3.3V #PWR14
U 1 1 586BE816
P 5450 4100
F 0 "#PWR14" H 5450 3950 50  0001 C CNN
F 1 "+3.3V" H 5450 4240 50  0000 C CNN
F 2 "" H 5450 4100 50  0000 C CNN
F 3 "" H 5450 4100 50  0000 C CNN
	1    5450 4100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR15
U 1 1 586BE877
P 5450 4250
F 0 "#PWR15" H 5450 4000 50  0001 C CNN
F 1 "GND" H 5450 4100 50  0000 C CNN
F 2 "" H 5450 4250 50  0000 C CNN
F 3 "" H 5450 4250 50  0000 C CNN
	1    5450 4250
	0    -1   -1   0   
$EndComp
Text Notes 5500 2650 0    60   ~ 0
switches
Text Notes 3900 2400 1    60   ~ 0
speed pot
$Comp
L R R3
U 1 1 586BF6D4
P 2000 3950
F 0 "R3" V 2080 3950 50  0000 C CNN
F 1 "22k" V 2000 3950 50  0000 C CNN
F 2 "" V 1930 3950 50  0000 C CNN
F 3 "" H 2000 3950 50  0000 C CNN
	1    2000 3950
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 586BF7B3
P 2000 5000
F 0 "R4" V 2080 5000 50  0000 C CNN
F 1 "22k" V 2000 5000 50  0000 C CNN
F 2 "" V 1930 5000 50  0000 C CNN
F 3 "" H 2000 5000 50  0000 C CNN
	1    2000 5000
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR5
U 1 1 586BF98B
P 2000 3800
F 0 "#PWR5" H 2000 3650 50  0001 C CNN
F 1 "+3.3V" H 2000 3940 50  0000 C CNN
F 2 "" H 2000 3800 50  0000 C CNN
F 3 "" H 2000 3800 50  0000 C CNN
	1    2000 3800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR6
U 1 1 586BF9C6
P 2000 4850
F 0 "#PWR6" H 2000 4700 50  0001 C CNN
F 1 "+3.3V" H 2000 4990 50  0000 C CNN
F 2 "" H 2000 4850 50  0000 C CNN
F 3 "" H 2000 4850 50  0000 C CNN
	1    2000 4850
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 586BFB36
P 1200 4550
F 0 "C1" H 1225 4650 50  0000 L CNN
F 1 "100n" H 1225 4450 50  0000 L CNN
F 2 "" H 1238 4400 50  0000 C CNN
F 3 "" H 1200 4550 50  0000 C CNN
	1    1200 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 586BFC4B
P 1200 4800
F 0 "#PWR1" H 1200 4550 50  0001 C CNN
F 1 "GND" H 1200 4650 50  0000 C CNN
F 2 "" H 1200 4800 50  0000 C CNN
F 3 "" H 1200 4800 50  0000 C CNN
	1    1200 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR12
U 1 1 586BFDF5
P 6900 1400
F 0 "#PWR12" H 6900 1250 50  0001 C CNN
F 1 "+3.3V" H 6900 1540 50  0000 C CNN
F 2 "" H 6900 1400 50  0000 C CNN
F 3 "" H 6900 1400 50  0000 C CNN
	1    6900 1400
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR11
U 1 1 586BFE34
P 7200 1300
F 0 "#PWR11" H 7200 1050 50  0001 C CNN
F 1 "GND" H 7200 1150 50  0000 C CNN
F 2 "" H 7200 1300 50  0000 C CNN
F 3 "" H 7200 1300 50  0000 C CNN
	1    7200 1300
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR20
U 1 1 586BFF69
P 7950 2750
F 0 "#PWR20" H 7950 2600 50  0001 C CNN
F 1 "+3.3V" H 7950 2890 50  0000 C CNN
F 2 "" H 7950 2750 50  0000 C CNN
F 3 "" H 7950 2750 50  0000 C CNN
	1    7950 2750
	0    1    1    0   
$EndComp
$Comp
L GND #PWR13
U 1 1 586C0044
P 5300 2950
F 0 "#PWR13" H 5300 2700 50  0001 C CNN
F 1 "GND" H 5300 2800 50  0000 C CNN
F 2 "" H 5300 2950 50  0000 C CNN
F 3 "" H 5300 2950 50  0000 C CNN
	1    5300 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR21
U 1 1 586C0144
P 7600 4950
F 0 "#PWR21" H 7600 4700 50  0001 C CNN
F 1 "GND" H 7600 4800 50  0000 C CNN
F 2 "" H 7600 4950 50  0000 C CNN
F 3 "" H 7600 4950 50  0000 C CNN
	1    7600 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR18
U 1 1 586C0172
P 6300 4900
F 0 "#PWR18" H 6300 4650 50  0001 C CNN
F 1 "GND" H 6300 4750 50  0000 C CNN
F 2 "" H 6300 4900 50  0000 C CNN
F 3 "" H 6300 4900 50  0000 C CNN
	1    6300 4900
	1    0    0    -1  
$EndComp
Text Notes 1600 2300 0    60   ~ 0
rpm counters
$Comp
L GND #PWR17
U 1 1 586C1A1C
P 6250 2800
F 0 "#PWR17" H 6250 2550 50  0001 C CNN
F 1 "GND" H 6250 2650 50  0000 C CNN
F 2 "" H 6250 2800 50  0000 C CNN
F 3 "" H 6250 2800 50  0000 C CNN
	1    6250 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4300 1500 4500
Wire Wire Line
	1200 4400 2200 4400
Connection ~ 1500 4400
Wire Wire Line
	2200 5400 2150 5400
Wire Wire Line
	2150 5400 2150 4400
Connection ~ 2150 4400
Wire Wire Line
	8350 3650 8550 3650
Wire Wire Line
	8550 4550 7600 4550
Wire Wire Line
	8550 3750 8550 4550
Wire Wire Line
	8400 3950 8400 4050
Wire Wire Line
	8400 4050 8550 4050
Connection ~ 8550 4050
Wire Wire Line
	8300 3150 8550 3150
Wire Wire Line
	9350 3250 9550 3250
Wire Wire Line
	9550 3250 9550 2900
Wire Wire Line
	9550 2900 8350 2900
Wire Wire Line
	8350 2900 8350 1700
Wire Wire Line
	7700 4150 7600 4150
Wire Wire Line
	7700 2050 7700 4150
Wire Wire Line
	7750 4250 7600 4250
Wire Wire Line
	7750 2100 7750 4250
Wire Wire Line
	7800 4350 7600 4350
Wire Wire Line
	7800 2000 7800 4350
Wire Wire Line
	7850 4450 7600 4450
Wire Wire Line
	7850 1950 7850 4450
Wire Wire Line
	6300 4550 6200 4550
Wire Wire Line
	6200 4550 6200 5150
Wire Wire Line
	6200 5150 4150 5150
Wire Wire Line
	4150 5150 4150 4250
Wire Wire Line
	4150 4250 4350 4250
Wire Wire Line
	4350 4400 4200 4400
Wire Wire Line
	4200 4400 4200 5100
Wire Wire Line
	4200 5100 6150 5100
Wire Wire Line
	6150 5100 6150 4350
Wire Wire Line
	6150 4350 6300 4350
Wire Wire Line
	6300 4450 6100 4450
Wire Wire Line
	6100 4450 6100 5050
Wire Wire Line
	6100 5050 4250 5050
Wire Wire Line
	4250 5050 4250 4550
Wire Wire Line
	4250 4550 4350 4550
Wire Wire Line
	5900 5550 6000 5550
Wire Wire Line
	5450 4700 5950 4700
Connection ~ 5950 5550
Wire Wire Line
	4200 3800 4350 3800
Wire Wire Line
	4200 1000 4200 3800
Wire Wire Line
	4100 3950 4350 3950
Wire Wire Line
	4000 4100 4350 4100
Wire Wire Line
	4000 950  4000 4100
Wire Wire Line
	6500 3950 5450 3950
Wire Wire Line
	6500 850  6500 3950
Wire Wire Line
	5800 4400 5450 4400
Wire Wire Line
	4350 4700 4300 4700
Wire Wire Line
	4300 4700 4300 3150
Wire Wire Line
	4300 3150 5600 3150
Wire Wire Line
	5600 3150 5600 1450
Wire Wire Line
	3800 4850 4350 4850
Wire Wire Line
	3800 1150 3800 4850
Wire Wire Line
	2800 5300 5450 5300
Wire Wire Line
	5450 5300 5450 4850
Wire Wire Line
	5450 4550 5500 4550
Wire Wire Line
	5500 4550 5500 5250
Wire Wire Line
	5500 5250 2950 5250
Wire Wire Line
	2950 5250 2950 4300
Wire Wire Line
	2950 4300 2800 4300
Wire Wire Line
	1850 4200 2200 4200
Wire Wire Line
	1750 5200 2200 5200
Wire Wire Line
	2000 5200 2000 5150
Wire Wire Line
	2000 4200 2000 4100
Wire Wire Line
	1850 2700 1850 4200
Connection ~ 2000 4200
Wire Wire Line
	1750 1850 1750 5200
Connection ~ 2000 5200
Wire Wire Line
	1200 4800 1200 4700
Wire Wire Line
	5500 1350 5500 2950
Wire Wire Line
	5500 2950 5300 2950
Wire Wire Line
	6300 4650 6300 4900
Connection ~ 6300 4750
Connection ~ 6300 4650
Wire Wire Line
	5700 3800 5450 3800
Wire Wire Line
	5450 3550 6150 3550
Wire Wire Line
	6150 3550 6150 4250
Wire Wire Line
	6150 4250 6300 4250
Wire Wire Line
	4350 3550 4350 3350
Wire Wire Line
	4350 3350 6200 3350
Wire Wire Line
	6200 3350 6200 4150
Wire Wire Line
	6200 4150 6300 4150
Wire Wire Line
	5950 4700 5950 5550
Wire Wire Line
	6450 900  6450 2800
Wire Wire Line
	6450 2800 6250 2800
Wire Wire Line
	5700 1550 5700 3800
Wire Wire Line
	5800 1650 5800 4400
$Comp
L GND #PWR4
U 1 1 586C3D56
P 1200 1750
F 0 "#PWR4" H 1200 1500 50  0001 C CNN
F 1 "GND" H 1200 1600 50  0000 C CNN
F 2 "" H 1200 1750 50  0000 C CNN
F 3 "" H 1200 1750 50  0000 C CNN
	1    1200 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 1750 2450 1750
$Comp
L LM358N U1
U 1 1 586C4511
P 2500 4300
F 0 "U1" H 2500 4500 50  0000 L CNN
F 1 "LM358N" H 2500 4100 50  0000 L CNN
F 2 "" H 2500 4300 50  0000 C CNN
F 3 "" H 2500 4300 50  0000 C CNN
	1    2500 4300
	1    0    0    -1  
$EndComp
$Comp
L LM358N U1
U 2 1 586C49AA
P 2500 5300
F 0 "U1" H 2500 5500 50  0000 L CNN
F 1 "LM358N" H 2500 5100 50  0000 L CNN
F 2 "" H 2500 5300 50  0000 C CNN
F 3 "" H 2500 5300 50  0000 C CNN
	2    2500 5300
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X05 P?
U 1 1 5873CC42
P 7650 1500
F 0 "P?" H 7650 1800 50  0000 C CNN
F 1 "CONN_02X05" H 7650 1200 50  0000 C CNN
F 2 "" H 7650 300 50  0000 C CNN
F 3 "" H 7650 300 50  0000 C CNN
	1    7650 1500
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X07 P?
U 1 1 5873CD01
P 2700 1550
F 0 "P?" H 2700 1950 50  0000 C CNN
F 1 "CONN_02X07" V 2700 1550 50  0000 C CNN
F 2 "" H 2700 350 50  0000 C CNN
F 3 "" H 2700 350 50  0000 C CNN
	1    2700 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 1700 7900 1700
Wire Wire Line
	7400 1700 7350 1700
Wire Wire Line
	7350 1700 7350 1900
Wire Wire Line
	7350 1900 8300 1900
Wire Wire Line
	8300 1900 8300 3150
Wire Wire Line
	7950 1600 7950 2750
Wire Wire Line
	7950 1600 7900 1600
Wire Wire Line
	7850 1950 7300 1950
Wire Wire Line
	7300 1950 7300 1600
Wire Wire Line
	7300 1600 7400 1600
Wire Wire Line
	7750 2100 8000 2100
Wire Wire Line
	8000 2100 8000 1500
Wire Wire Line
	8000 1500 7900 1500
Wire Wire Line
	7800 2000 7250 2000
Wire Wire Line
	7250 2000 7250 1500
Wire Wire Line
	7250 1500 7400 1500
Wire Wire Line
	7700 2050 8050 2050
Wire Wire Line
	8050 2050 8050 1400
Wire Wire Line
	8050 1400 7900 1400
Wire Wire Line
	7200 1300 7400 1300
Wire Wire Line
	7900 1300 7900 1150
Wire Wire Line
	7900 1150 3800 1150
Wire Wire Line
	7400 1400 6900 1400
Wire Wire Line
	1850 2700 3100 2700
Wire Wire Line
	3100 2700 3100 1850
Wire Wire Line
	3100 1850 2950 1850
Wire Wire Line
	1750 1850 2450 1850
Wire Wire Line
	4200 1000 2300 1000
Wire Wire Line
	2300 1000 2300 1250
Wire Wire Line
	2300 1250 2450 1250
Wire Wire Line
	4000 950  2250 950 
Wire Wire Line
	2950 1250 4100 1250
Wire Wire Line
	4100 1250 4100 3950
Wire Wire Line
	2250 950  2250 1350
Wire Wire Line
	2250 1350 2450 1350
Wire Wire Line
	5500 1350 2950 1350
Wire Wire Line
	5600 1450 2950 1450
Wire Wire Line
	5700 1550 2950 1550
Wire Wire Line
	5800 1650 2950 1650
Wire Wire Line
	6450 900  2200 900 
Wire Wire Line
	2200 900  2200 1450
Wire Wire Line
	2200 1450 2450 1450
Wire Wire Line
	6500 850  2150 850 
Wire Wire Line
	2150 850  2150 1550
Wire Wire Line
	2150 1550 2450 1550
Wire Wire Line
	2450 1650 1200 1650
Wire Wire Line
	1200 1650 1200 1600
$Comp
L +BATT #PWR?
U 1 1 5873F61F
P 1200 1600
F 0 "#PWR?" H 1200 1450 50  0001 C CNN
F 1 "+BATT" H 1200 1740 50  0000 C CNN
F 2 "" H 1200 1600 50  0000 C CNN
F 3 "" H 1200 1600 50  0000 C CNN
	1    1200 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5873F704
P 3350 1750
F 0 "#PWR?" H 3350 1500 50  0001 C CNN
F 1 "GND" H 3350 1600 50  0000 C CNN
F 2 "" H 3350 1750 50  0000 C CNN
F 3 "" H 3350 1750 50  0000 C CNN
	1    3350 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 1750 3350 1750
$EndSCHEMATC
