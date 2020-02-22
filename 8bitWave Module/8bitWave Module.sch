EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "8BIT WAVE"
Date ""
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L mounting:Mounting M1
U 1 1 5E3B603D
P 10775 550
F 0 "M1" H 10775 650 50  0001 C CNN
F 1 "Mounting" H 10775 475 50  0001 C CNN
F 2 "mounting:M3" H 10775 550 50  0001 C CNN
F 3 "" H 10775 550 50  0001 C CNN
	1    10775 550 
	1    0    0    -1  
$EndComp
$Comp
L mounting:Mounting M2
U 1 1 5E3B604F
P 10900 550
F 0 "M2" H 10900 650 50  0001 C CNN
F 1 "Mounting" H 10900 475 50  0001 C CNN
F 2 "mounting:M3" H 10900 550 50  0001 C CNN
F 3 "" H 10900 550 50  0001 C CNN
	1    10900 550 
	1    0    0    -1  
$EndComp
$Comp
L mounting:Mounting M3
U 1 1 5E3B605A
P 11025 550
F 0 "M3" H 11025 650 50  0001 C CNN
F 1 "Mounting" H 11025 475 50  0001 C CNN
F 2 "mounting:M3" H 11025 550 50  0001 C CNN
F 3 "" H 11025 550 50  0001 C CNN
	1    11025 550 
	1    0    0    -1  
$EndComp
$Comp
L mounting:Mounting M4
U 1 1 5E3B6065
P 11150 550
F 0 "M4" H 11150 650 50  0001 C CNN
F 1 "Mounting" H 11150 475 50  0001 C CNN
F 2 "mounting:M3" H 11150 550 50  0001 C CNN
F 3 "" H 11150 550 50  0001 C CNN
	1    11150 550 
	1    0    0    -1  
$EndComp
$Comp
L arduino_nano:Arduino_Nano A1
U 1 1 5E3B6403
P 6700 3550
F 0 "A1" H 6500 4575 50  0000 R CNN
F 1 "Arduino Nano" H 6500 4500 50  0000 R CNN
F 2 "Modules:Arduino_Nano" H 6850 2600 50  0001 L CNN
F 3 "" H 6700 2550 50  0001 C CNN
	1    6700 3550
	-1   0    0    -1  
$EndComp
$Comp
L switches:SW_SPST SW1
U 1 1 5E3B6481
P 9425 4175
F 0 "SW1" H 9425 4300 50  0000 C CNN
F 1 "UP" H 9425 4075 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS" H 9425 4175 50  0001 C CNN
F 3 "" H 9425 4175 50  0001 C CNN
	1    9425 4175
	-1   0    0    -1  
$EndComp
$Comp
L switches:SW_SPST SW2
U 1 1 5E3B64CB
P 9425 4525
F 0 "SW2" H 9425 4650 50  0000 C CNN
F 1 "DOWN" H 9425 4425 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS" H 9425 4525 50  0001 C CNN
F 3 "" H 9425 4525 50  0001 C CNN
	1    9425 4525
	-1   0    0    -1  
$EndComp
$Comp
L switches:SW_SPST SW3
U 1 1 5E3B64F8
P 9425 4875
F 0 "SW3" H 9425 5000 50  0000 C CNN
F 1 "STOP" H 9425 4775 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS" H 9425 4875 50  0001 C CNN
F 3 "" H 9425 4875 50  0001 C CNN
	1    9425 4875
	-1   0    0    -1  
$EndComp
$Comp
L switches:SW_SPST SW4
U 1 1 5E3B6550
P 9425 5225
F 0 "SW4" H 9425 5350 50  0000 C CNN
F 1 "PLAY" H 9425 5125 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS" H 9425 5225 50  0001 C CNN
F 3 "" H 9425 5225 50  0001 C CNN
	1    9425 5225
	-1   0    0    -1  
$EndComp
$Comp
L switches:SW_SPST SW5
U 1 1 5E3B65A5
P 9425 5575
F 0 "SW5" H 9425 5700 50  0000 C CNN
F 1 "ROOT" H 9425 5475 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_Tactile_SPST_Angled_PTS645Vx39-2LFS" H 9425 5575 50  0001 C CNN
F 3 "" H 9425 5575 50  0001 C CNN
	1    9425 5575
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5E3B6768
P 9150 5650
F 0 "#PWR01" H 9150 5400 50  0001 C CNN
F 1 "GND" H 9150 5500 50  0000 C CNN
F 2 "" H 9150 5650 50  0001 C CNN
F 3 "" H 9150 5650 50  0001 C CNN
	1    9150 5650
	-1   0    0    -1  
$EndComp
Text Label 9950 4175 2    60   ~ 0
UP
Text Label 9950 4525 2    60   ~ 0
DOWN
Text Label 9950 4875 2    60   ~ 0
STOP
Text Label 9950 5225 2    60   ~ 0
PLAY
Text Label 9950 5575 2    60   ~ 0
ROOT
Entry Wire Line
	10075 5675 9975 5575
Entry Wire Line
	10075 5325 9975 5225
Entry Wire Line
	10075 4975 9975 4875
Entry Wire Line
	10075 4625 9975 4525
Entry Wire Line
	10075 4275 9975 4175
Text Label 5875 3550 0    60   ~ 0
UP
Entry Wire Line
	5750 3650 5850 3550
Text Label 5875 3650 0    60   ~ 0
DOWN
Entry Wire Line
	5750 3750 5850 3650
Text Label 5875 3750 0    60   ~ 0
STOP
Entry Wire Line
	5750 3850 5850 3750
Text Label 5875 3850 0    60   ~ 0
PLAY
Entry Wire Line
	5750 3950 5850 3850
Entry Wire Line
	7650 4250 7550 4150
$Comp
L I2C_OLED:0.96_I2C_OLED IC1
U 1 1 5E3B718A
P 8900 1700
F 0 "IC1" H 8900 1525 60  0000 C CNN
F 1 "0.96_I2C_OLED" H 8875 1650 43  0000 C CNN
F 2 "i2c_oled:0.96_I2C_OLED" H 8900 2325 60  0001 C CNN
F 3 "" H 8900 2325 60  0001 C CNN
	1    8900 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5E3B72AB
P 8450 1450
F 0 "#PWR02" H 8450 1200 50  0001 C CNN
F 1 "GND" H 8450 1300 50  0000 C CNN
F 2 "" H 8450 1450 50  0001 C CNN
F 3 "" H 8450 1450 50  0001 C CNN
	1    8450 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 5E3B7508
P 6150 950
F 0 "#PWR03" H 6150 800 50  0001 C CNN
F 1 "+3.3V" H 6150 1090 50  0000 C CNN
F 2 "" H 6150 950 50  0001 C CNN
F 3 "" H 6150 950 50  0001 C CNN
	1    6150 950 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR04
U 1 1 5E3B7697
P 6600 2400
F 0 "#PWR04" H 6600 2250 50  0001 C CNN
F 1 "+3.3V" H 6600 2540 50  0000 C CNN
F 2 "" H 6600 2400 50  0001 C CNN
F 3 "" H 6600 2400 50  0001 C CNN
	1    6600 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5E3B772F
P 6500 2550
F 0 "#PWR05" H 6500 2400 50  0001 C CNN
F 1 "+5V" H 6500 2690 50  0000 C CNN
F 2 "" H 6500 2550 50  0001 C CNN
F 3 "" H 6500 2550 50  0001 C CNN
	1    6500 2550
	1    0    0    -1  
$EndComp
NoConn ~ 6800 2550
NoConn ~ 6200 3350
NoConn ~ 6200 2950
NoConn ~ 6200 3050
NoConn ~ 7200 2950
NoConn ~ 7200 3050
Text Label 5875 4050 0    60   ~ 0
SCL
Entry Wire Line
	5750 4150 5850 4050
Text Label 5875 3950 0    60   ~ 0
SDA
Entry Wire Line
	5750 4050 5850 3950
Text Label 9950 1075 2    60   ~ 0
SCL
Entry Wire Line
	10075 1175 9975 1075
Text Label 9950 1175 2    60   ~ 0
SDA
Entry Wire Line
	10075 1275 9975 1175
$Comp
L microsd_adapter:SD A2
U 1 1 5E3C12EA
P 8150 3050
F 0 "A2" H 8400 3525 60  0000 C CNN
F 1 "MicroSD Card Adapter" V 8250 3200 60  0000 C CNN
F 2 "sd_card_adapter:MicroSD_Card_Adapter" H 8150 3050 60  0001 C CNN
F 3 "" H 8150 3050 60  0001 C CNN
	1    8150 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5E3C13AD
P 8975 3350
F 0 "#PWR06" H 8975 3100 50  0001 C CNN
F 1 "GND" H 8975 3200 50  0000 C CNN
F 2 "" H 8975 3350 50  0001 C CNN
F 3 "" H 8975 3350 50  0001 C CNN
	1    8975 3350
	1    0    0    -1  
$EndComp
Entry Wire Line
	10075 3150 9975 3050
Entry Wire Line
	10075 3050 9975 2950
Entry Wire Line
	10075 2950 9975 2850
Entry Wire Line
	10075 2850 9975 2750
$Comp
L power:+5V #PWR07
U 1 1 5E3C1C63
P 8975 2425
F 0 "#PWR07" H 8975 2275 50  0001 C CNN
F 1 "+5V" H 8975 2565 50  0000 C CNN
F 2 "" H 8975 2425 50  0001 C CNN
F 3 "" H 8975 2425 50  0001 C CNN
	1    8975 2425
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5E3C1F67
P 6700 4700
F 0 "#PWR08" H 6700 4450 50  0001 C CNN
F 1 "GND" H 6700 4550 50  0000 C CNN
F 2 "" H 6700 4700 50  0001 C CNN
F 3 "" H 6700 4700 50  0001 C CNN
	1    6700 4700
	1    0    0    -1  
$EndComp
Text Label 7525 4150 2    60   ~ 0
MISO
Entry Wire Line
	7650 4150 7550 4050
Text Label 7525 4050 2    60   ~ 0
MOSI
Entry Wire Line
	7650 4050 7550 3950
Text Label 7525 3950 2    60   ~ 0
CS
Entry Wire Line
	7650 4350 7550 4250
Text Label 7525 4250 2    60   ~ 0
SCK
Text Label 9950 2750 2    60   ~ 0
CS
Text Label 9950 2850 2    60   ~ 0
SCK
Text Label 9950 3050 2    60   ~ 0
MISO
Text Label 9950 2950 2    60   ~ 0
MOSI
NoConn ~ 6200 4150
NoConn ~ 6200 4250
Entry Wire Line
	7650 3750 7550 3650
Text Label 7525 3650 2    60   ~ 0
ROOT
$Comp
L audio_jack:2.5mm_audio J1
U 1 1 5E3C4A62
P 4575 4450
F 0 "J1" H 4525 4625 50  0000 C CNN
F 1 "REM" H 4575 4375 50  0000 C CNN
F 2 "audio_jack:2.5mm_audio" H 4825 4550 50  0001 C CNN
F 3 "" H 4825 4550 50  0001 C CNN
	1    4575 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5E3C4CA7
P 4850 4525
F 0 "#PWR09" H 4850 4275 50  0001 C CNN
F 1 "GND" H 4850 4375 50  0000 C CNN
F 2 "" H 4850 4525 50  0001 C CNN
F 3 "" H 4850 4525 50  0001 C CNN
	1    4850 4525
	1    0    0    -1  
$EndComp
NoConn ~ 4775 4350
Entry Wire Line
	5500 4750 5600 4850
Text Label 5475 4750 2    60   ~ 0
REM
Entry Wire Line
	7650 3650 7550 3550
Text Label 7525 3550 2    60   ~ 0
REM
Entry Wire Line
	7650 3950 7550 3850
Text Label 7525 3850 2    60   ~ 0
SOUND
Entry Wire Line
	5500 5275 5600 5375
$Comp
L Device:R R3
U 1 1 5E3C68AA
P 4850 5275
F 0 "R3" V 4930 5275 50  0000 C CNN
F 1 "4k7" V 4850 5275 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4780 5275 50  0001 C CNN
F 3 "" H 4850 5275 50  0001 C CNN
	1    4850 5275
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5E3C6BDB
P 4625 5800
F 0 "#PWR010" H 4625 5550 50  0001 C CNN
F 1 "GND" H 4625 5650 50  0000 C CNN
F 2 "" H 4625 5800 50  0001 C CNN
F 3 "" H 4625 5800 50  0001 C CNN
	1    4625 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5E3C6C5D
P 4625 5450
F 0 "C4" H 4635 5520 50  0000 L CNN
F 1 "4.7nF" H 4635 5370 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 4625 5450 50  0001 C CNN
F 3 "" H 4625 5450 50  0001 C CNN
	1    4625 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5E3C6D77
P 4400 5275
F 0 "R2" V 4480 5275 50  0000 C CNN
F 1 "4k7" V 4400 5275 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4330 5275 50  0001 C CNN
F 3 "" H 4400 5275 50  0001 C CNN
	1    4400 5275
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5E3C6DDD
P 4175 5450
F 0 "C3" H 4185 5520 50  0000 L CNN
F 1 "4.7nF" H 4185 5370 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 4175 5450 50  0001 C CNN
F 3 "" H 4175 5450 50  0001 C CNN
	1    4175 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E3C6E95
P 3950 5275
F 0 "R1" V 4030 5275 50  0000 C CNN
F 1 "4k7" V 3950 5275 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3880 5275 50  0001 C CNN
F 3 "" H 3950 5275 50  0001 C CNN
	1    3950 5275
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5E3C6EA4
P 3725 5450
F 0 "C2" H 3735 5520 50  0000 L CNN
F 1 "4.7nF" H 3735 5370 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 3725 5450 50  0001 C CNN
F 3 "" H 3725 5450 50  0001 C CNN
	1    3725 5450
	1    0    0    -1  
$EndComp
Text Label 5475 5275 2    60   ~ 0
SOUND
$Comp
L Device:C_Small C1
U 1 1 5E3C7B70
P 3550 5275
F 0 "C1" V 3500 5150 50  0000 L CNN
F 1 "100nF" V 3650 5150 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 3550 5275 50  0001 C CNN
F 3 "" H 3550 5275 50  0001 C CNN
	1    3550 5275
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5E3C831F
P 3350 5500
F 0 "R4" V 3430 5500 50  0000 C CNN
F 1 "4k7" V 3350 5500 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3280 5500 50  0001 C CNN
F 3 "" H 3350 5500 50  0001 C CNN
	1    3350 5500
	-1   0    0    1   
$EndComp
$Comp
L 8bitWave-Module-rescue:POT RV1
U 1 1 5E3C8FB4
P 3050 5275
F 0 "RV1" V 2875 5275 50  0000 C CNN
F 1 "10k" V 2950 5275 50  0000 C CNN
F 2 "Potentiometers:Potentiometer_Triwood_RM-065" H 3050 5275 50  0001 C CNN
F 3 "" H 3050 5275 50  0001 C CNN
	1    3050 5275
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper_NO_Small JP2
U 1 1 5E3CAB3D
P 3950 5075
F 0 "JP2" H 3950 5155 50  0000 C CNN
F 1 "NO_FILTER" H 3960 5015 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 3950 5075 50  0001 C CNN
F 3 "" H 3950 5075 50  0001 C CNN
	1    3950 5075
	-1   0    0    1   
$EndComp
$Comp
L linear:LM386 U1
U 1 1 5E3CBAD8
P 2400 5025
F 0 "U1" H 2400 5025 50  0000 L CNN
F 1 "LM386" H 2500 5150 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm_Socket_LongPads" H 2500 5125 50  0001 C CNN
F 3 "" H 2600 5225 50  0001 C CNN
	1    2400 5025
	-1   0    0    -1  
$EndComp
$Comp
L Device:CP_Small C8
U 1 1 5E3CC6E7
P 2400 5575
F 0 "C8" H 2410 5645 50  0000 L CNN
F 1 "10uF" H 2410 5495 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D4.0mm_P2.00mm" H 2400 5575 50  0001 C CNN
F 3 "" H 2400 5575 50  0001 C CNN
	1    2400 5575
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper_NO_Small JP1
U 1 1 5E3CC956
P 2200 5575
F 0 "JP1" H 2200 5655 50  0000 C CNN
F 1 "GAIN" H 2210 5515 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2200 5575 50  0001 C CNN
F 3 "" H 2200 5575 50  0001 C CNN
	1    2200 5575
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 5E3CE5A0
P 2500 3975
F 0 "#PWR011" H 2500 3825 50  0001 C CNN
F 1 "+5V" H 2500 4115 50  0000 C CNN
F 2 "" H 2500 3975 50  0001 C CNN
F 3 "" H 2500 3975 50  0001 C CNN
	1    2500 3975
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C7
U 1 1 5E3CF2C3
P 2225 4550
F 0 "C7" V 2175 4350 50  0000 L CNN
F 1 "100uF" V 2275 4275 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.00mm" H 2225 4550 50  0001 C CNN
F 3 "" H 2225 4550 50  0001 C CNN
	1    2225 4550
	0    1    1    0   
$EndComp
$Comp
L Device:CP_Small C6
U 1 1 5E3CF9CD
P 2225 4300
F 0 "C6" V 2175 4100 50  0000 L CNN
F 1 "10uF" V 2275 4050 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D4.0mm_P2.00mm" H 2225 4300 50  0001 C CNN
F 3 "" H 2225 4300 50  0001 C CNN
	1    2225 4300
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5E3CFD8D
P 2225 4050
F 0 "C5" V 2175 3850 50  0000 L CNN
F 1 "100nF" V 2275 3775 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 2225 4050 50  0001 C CNN
F 3 "" H 2225 4050 50  0001 C CNN
	1    2225 4050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5E3D02D2
P 1525 4650
F 0 "#PWR012" H 1525 4400 50  0001 C CNN
F 1 "GND" H 1525 4500 50  0000 C CNN
F 2 "" H 1525 4650 50  0001 C CNN
F 3 "" H 1525 4650 50  0001 C CNN
	1    1525 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 5575 9225 5575
Wire Wire Line
	9150 4175 9150 4525
Wire Wire Line
	9150 5225 9225 5225
Connection ~ 9150 5575
Wire Wire Line
	9150 4875 9225 4875
Connection ~ 9150 5225
Wire Wire Line
	9150 4525 9225 4525
Connection ~ 9150 4875
Wire Wire Line
	9150 4175 9225 4175
Connection ~ 9150 4525
Wire Wire Line
	9625 5575 9975 5575
Wire Wire Line
	9625 5225 9975 5225
Wire Wire Line
	9625 4875 9975 4875
Wire Wire Line
	9625 4525 9975 4525
Wire Wire Line
	9625 4175 9975 4175
Wire Wire Line
	6200 3550 5850 3550
Wire Wire Line
	6200 3650 5850 3650
Wire Wire Line
	6200 3750 5850 3750
Wire Wire Line
	6200 3850 5850 3850
Wire Wire Line
	7200 4150 7550 4150
Wire Wire Line
	8450 1175 8450 1450
Wire Wire Line
	8375 1175 8450 1175
Wire Wire Line
	8675 1175 8675 1250
Wire Wire Line
	8825 625  8825 1075
Wire Wire Line
	6600 2550 6600 2400
Wire Wire Line
	6200 4050 5850 4050
Wire Wire Line
	6200 3950 5850 3950
Wire Wire Line
	8975 1075 9425 1075
Wire Wire Line
	9125 1175 9600 1175
Wire Wire Line
	9125 875  9125 1175
Wire Wire Line
	8975 975  8975 1075
Wire Wire Line
	9550 3050 9975 3050
Wire Wire Line
	9550 2950 9975 2950
Wire Wire Line
	9550 2850 9975 2850
Wire Wire Line
	9550 2750 9975 2750
Wire Wire Line
	6600 4550 6600 4625
Wire Wire Line
	6600 4625 6700 4625
Wire Wire Line
	6700 4550 6700 4625
Connection ~ 6700 4625
Wire Wire Line
	7200 4050 7550 4050
Wire Wire Line
	7200 3950 7550 3950
Wire Wire Line
	7200 4250 7550 4250
Wire Bus Line
	10075 1275 10075 1175
Wire Bus Line
	10075 1225 10150 1225
Wire Bus Line
	10150 4975 10075 4975
Wire Bus Line
	10075 3000 10150 3000
Wire Wire Line
	7200 3650 7550 3650
Wire Bus Line
	7650 4050 7725 4050
Wire Bus Line
	5675 3875 5675 6275
Wire Bus Line
	5675 6275 10150 6275
Wire Bus Line
	7725 4975 5675 4975
Wire Wire Line
	4775 4450 4850 4450
Wire Wire Line
	4850 4450 4850 4525
Wire Wire Line
	4375 4550 4375 4750
Wire Wire Line
	4375 4750 5500 4750
Wire Wire Line
	7200 3550 7550 3550
Wire Wire Line
	7200 3850 7550 3850
Wire Bus Line
	7725 4050 7725 4975
Wire Wire Line
	5000 5275 5075 5275
Wire Wire Line
	4550 5275 4625 5275
Wire Wire Line
	4625 5275 4625 5350
Connection ~ 4625 5275
Wire Wire Line
	4100 5275 4175 5275
Wire Wire Line
	4175 5275 4175 5350
Connection ~ 4175 5275
Wire Wire Line
	3650 5275 3725 5275
Wire Wire Line
	3725 5275 3725 5350
Connection ~ 3725 5275
Wire Wire Line
	3350 5725 3350 5650
Wire Wire Line
	2775 5725 3050 5725
Wire Wire Line
	4625 5550 4625 5725
Wire Wire Line
	4175 5550 4175 5725
Connection ~ 4175 5725
Wire Wire Line
	3725 5550 3725 5725
Connection ~ 3725 5725
Connection ~ 4625 5725
Wire Wire Line
	3200 5275 3350 5275
Wire Wire Line
	3350 5075 3350 5275
Connection ~ 3350 5275
Connection ~ 3350 5725
Wire Wire Line
	3050 5425 3050 5725
Wire Wire Line
	3350 5075 3850 5075
Wire Wire Line
	4050 5075 5075 5075
Wire Wire Line
	5075 5075 5075 5275
Connection ~ 5075 5275
Wire Wire Line
	2700 5125 2775 5125
Wire Wire Line
	2775 5125 2775 5400
Connection ~ 3050 5725
Wire Wire Line
	2700 4925 3050 4925
Wire Wire Line
	3050 4925 3050 5125
Wire Wire Line
	2400 5325 2400 5475
Wire Wire Line
	2500 5325 2500 5400
Wire Wire Line
	2500 5400 2775 5400
Connection ~ 2775 5400
Wire Wire Line
	2300 5325 2300 5400
Wire Wire Line
	2300 5400 2200 5400
Wire Wire Line
	2200 5400 2200 5475
Wire Wire Line
	2200 5675 2200 5750
Wire Wire Line
	2200 5750 2400 5750
Wire Wire Line
	2400 5750 2400 5675
Wire Wire Line
	2400 4550 2400 4725
Wire Wire Line
	2400 4550 2325 4550
Wire Wire Line
	2325 4050 2500 4050
Wire Wire Line
	2500 3975 2500 4050
Connection ~ 2500 4050
Wire Wire Line
	2325 4300 2500 4300
Connection ~ 2500 4300
Wire Wire Line
	1525 4050 1525 4300
Wire Wire Line
	1525 4550 1725 4550
Wire Wire Line
	1525 4300 2125 4300
Connection ~ 1525 4550
Wire Wire Line
	1525 4050 2125 4050
Connection ~ 1525 4300
$Comp
L audio_jack:TRS_3.5mm J2
U 1 1 5E3D2244
P 4125 6725
F 0 "J2" H 4125 7015 50  0000 C CNN
F 1 "EAR" H 4025 6525 50  0000 L CNN
F 2 "audio_jack:Tayda_3.5mm_stereo_TRS_jack_A-853" H 4375 6825 50  0001 C CNN
F 3 "" H 4375 6825 50  0001 C CNN
	1    4125 6725
	1    0    0    -1  
$EndComp
Wire Bus Line
	5675 3875 5750 3875
$Comp
L Device:C_Small C9
U 1 1 5E3D3471
P 1500 5200
F 0 "C9" H 1510 5270 50  0000 L CNN
F 1 "10pF" H 1510 5120 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D4.7mm_W2.5mm_P5.00mm" H 1500 5200 50  0001 C CNN
F 3 "" H 1500 5200 50  0001 C CNN
	1    1500 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5E3D38E7
P 1500 5450
F 0 "R5" V 1580 5450 50  0000 C CNN
F 1 "100" V 1500 5450 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1430 5450 50  0001 C CNN
F 3 "" H 1500 5450 50  0001 C CNN
	1    1500 5450
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5E3D42D1
P 1500 5600
F 0 "#PWR013" H 1500 5350 50  0001 C CNN
F 1 "GND" H 1500 5450 50  0000 C CNN
F 2 "" H 1500 5600 50  0001 C CNN
F 3 "" H 1500 5600 50  0001 C CNN
	1    1500 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C10
U 1 1 5E3D471B
P 1925 5025
F 0 "C10" V 1875 4825 50  0000 L CNN
F 1 "100uF" V 1975 4750 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D5.0mm_P2.50mm" H 1925 5025 50  0001 C CNN
F 3 "" H 1925 5025 50  0001 C CNN
	1    1925 5025
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 5100 1500 5025
Wire Wire Line
	1250 5025 1500 5025
Connection ~ 1500 5025
NoConn ~ 4325 6525
NoConn ~ 4325 6625
NoConn ~ 4325 6825
Wire Wire Line
	2025 5025 2100 5025
$Comp
L power:GND #PWR014
U 1 1 5E3D6718
P 3925 7000
F 0 "#PWR014" H 3925 6750 50  0001 C CNN
F 1 "GND" H 3925 6850 50  0000 C CNN
F 2 "" H 3925 7000 50  0001 C CNN
F 3 "" H 3925 7000 50  0001 C CNN
	1    3925 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3925 7000 3925 6925
$Comp
L Device:Jumper_NC_Dual JP3
U 1 1 5E3D8BB4
P 4625 6250
F 0 "JP3" H 4675 6150 50  0000 L CNN
F 1 "AMPLIFY" H 4625 6350 50  0000 C BNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 4625 6250 50  0001 C CNN
F 3 "" H 4625 6250 50  0001 C CNN
	1    4625 6250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5075 6250 4875 6250
Wire Wire Line
	4375 6250 1250 6250
Wire Wire Line
	1250 6250 1250 5025
Wire Wire Line
	4625 6350 4625 6725
Wire Wire Line
	4625 6725 4325 6725
$Comp
L I2C_OLED:0.91_I2C_OLED IC2
U 1 1 5E3DAC3C
P 7650 900
F 0 "IC2" H 7700 725 60  0000 C CNN
F 1 "0.91_I2C_OLED" H 7725 800 43  0000 C CNN
F 2 "i2c_oled:0.91_I2C_OLED" H 7650 1525 60  0001 C CNN
F 3 "" H 7650 1525 60  0001 C CNN
	1    7650 900 
	-1   0    0    -1  
$EndComp
Connection ~ 8450 1175
Wire Wire Line
	8375 1075 8825 1075
Connection ~ 8825 1075
Wire Wire Line
	8375 975  8975 975 
Connection ~ 8975 1075
Wire Wire Line
	8375 875  9125 875 
Connection ~ 9125 1175
Wire Bus Line
	10150 6275 10150 1225
$Comp
L Device:R R6
U 1 1 5E3CE04C
P 5000 3100
F 0 "R6" V 5080 3100 50  0000 C CNN
F 1 "220" V 5000 3100 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4930 3100 50  0001 C CNN
F 3 "" H 5000 3100 50  0001 C CNN
	1    5000 3100
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5E3CE2EF
P 4575 3175
F 0 "#PWR015" H 4575 2925 50  0001 C CNN
F 1 "GND" H 4575 3025 50  0000 C CNN
F 2 "" H 4575 3175 50  0001 C CNN
F 3 "" H 4575 3175 50  0001 C CNN
	1    4575 3175
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4575 3175 4575 3100
Wire Wire Line
	4575 3100 4650 3100
$Comp
L Device:LED_Small D1
U 1 1 5E3CE73B
P 4750 3100
F 0 "D1" H 4700 3225 50  0000 L CNN
F 1 "POWER" H 4625 3025 50  0000 L CNN
F 2 "LEDs:LED_D5.0mm" V 4750 3100 50  0001 C CNN
F 3 "" V 4750 3100 50  0001 C CNN
	1    4750 3100
	1    0    0    1   
$EndComp
Entry Wire Line
	7650 3550 7550 3450
Text Label 7525 3450 2    60   ~ 0
POWER
Wire Wire Line
	7200 3450 7550 3450
Entry Wire Line
	5600 3200 5500 3100
Text Label 5475 3100 2    60   ~ 0
POWER
Wire Wire Line
	5150 3100 5500 3100
Entry Wire Line
	7650 3250 7550 3150
Text Label 7525 3150 2    60   ~ 0
D2
Wire Wire Line
	7200 3150 7550 3150
Entry Wire Line
	7650 3350 7550 3250
Wire Wire Line
	7200 3250 7550 3250
Entry Wire Line
	7650 3450 7550 3350
Text Label 7525 3350 2    60   ~ 0
D4
Wire Wire Line
	7200 3350 7550 3350
Wire Bus Line
	5600 4525 5675 4525
$Comp
L conn:Conn_01x07 J3
U 1 1 5E3D299E
P 4950 2125
F 0 "J3" H 4950 2525 50  0000 C CNN
F 1 "EXTENSION" V 5050 2125 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07_Pitch2.54mm" H 4950 2125 50  0001 C CNN
F 3 "" H 4950 2125 50  0001 C CNN
	1    4950 2125
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5E3D3470
P 5225 2500
F 0 "#PWR016" H 5225 2250 50  0001 C CNN
F 1 "GND" H 5225 2350 50  0000 C CNN
F 2 "" H 5225 2500 50  0001 C CNN
F 3 "" H 5225 2500 50  0001 C CNN
	1    5225 2500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5225 2500 5225 2425
Wire Wire Line
	5225 2425 5150 2425
Entry Wire Line
	5600 2025 5500 1925
Text Label 5475 2125 2    60   ~ 0
D2
Wire Wire Line
	5150 1925 5500 1925
Entry Wire Line
	5600 2125 5500 2025
Wire Wire Line
	5150 2025 5500 2025
Entry Wire Line
	5600 2225 5500 2125
Text Label 5475 2025 2    60   ~ 0
D4
Wire Wire Line
	5150 2125 5500 2125
Entry Wire Line
	5600 2325 5500 2225
Wire Wire Line
	5150 2225 5500 2225
Entry Wire Line
	5600 2425 5500 2325
Wire Wire Line
	5150 2325 5500 2325
Text Label 5475 2325 2    60   ~ 0
SCL
Text Label 5475 2225 2    60   ~ 0
SDA
Text Notes 1675 4850 0    60   ~ 0
Noise\n-reduction
Entry Wire Line
	7650 3850 7550 3750
Text Label 7525 3750 2    60   ~ 0
D8
Wire Wire Line
	7200 3750 7550 3750
Text Label 5475 1925 2    60   ~ 0
D8
Text Label 7525 3250 2    60   ~ 0
USER
$Comp
L Device:R R7
U 1 1 5E3E1B83
P 5000 3500
F 0 "R7" V 5080 3500 50  0000 C CNN
F 1 "220" V 5000 3500 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4930 3500 50  0001 C CNN
F 3 "" H 5000 3500 50  0001 C CNN
	1    5000 3500
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5E3E1B89
P 4575 3575
F 0 "#PWR017" H 4575 3325 50  0001 C CNN
F 1 "GND" H 4575 3425 50  0000 C CNN
F 2 "" H 4575 3575 50  0001 C CNN
F 3 "" H 4575 3575 50  0001 C CNN
	1    4575 3575
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4575 3575 4575 3500
Wire Wire Line
	4575 3500 4650 3500
$Comp
L Device:LED_Small D2
U 1 1 5E3E1B91
P 4750 3500
F 0 "D2" H 4700 3625 50  0000 L CNN
F 1 "USER" H 4625 3425 50  0000 L CNN
F 2 "LEDs:LED_D5.0mm" V 4750 3500 50  0001 C CNN
F 3 "" V 4750 3500 50  0001 C CNN
	1    4750 3500
	1    0    0    1   
$EndComp
Entry Wire Line
	5600 3600 5500 3500
Text Label 5475 3500 2    60   ~ 0
USER
Wire Wire Line
	5150 3500 5500 3500
$Comp
L Device:Jumper_NO_Small JP4
U 1 1 5E3E3DB1
P 1825 4550
F 0 "JP4" H 1825 4630 50  0000 C CNN
F 1 "BYPASS" H 1835 4490 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 1825 4550 50  0001 C CNN
F 3 "" H 1825 4550 50  0001 C CNN
	1    1825 4550
	-1   0    0    1   
$EndComp
Wire Wire Line
	1925 4550 2125 4550
Wire Notes Line
	2425 4425 1625 4425
Wire Notes Line
	1625 4850 2425 4850
Wire Notes Line
	2425 4850 2425 4425
Wire Notes Line
	1625 4425 1625 4850
$Comp
L Device:R R8
U 1 1 5E3E6FC5
P 9425 850
F 0 "R8" V 9505 850 50  0000 C CNN
F 1 "4k7" V 9425 850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 9355 850 50  0001 C CNN
F 3 "" H 9425 850 50  0001 C CNN
	1    9425 850 
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 5E3E72A5
P 9600 850
F 0 "R9" V 9680 850 50  0000 C CNN
F 1 "4k7" V 9600 850 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 9530 850 50  0001 C CNN
F 3 "" H 9600 850 50  0001 C CNN
	1    9600 850 
	-1   0    0    1   
$EndComp
$Comp
L i2c_voltage_select:I2C_VOLTAGE_SELECT JP5
U 1 1 5E3E91C2
P 6475 1025
F 0 "JP5" H 6525 925 50  0000 L CNN
F 1 "I2C_VOL" H 6475 1125 50  0000 C BNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 6475 1025 50  0001 C CNN
F 3 "" H 6475 1025 50  0001 C CNN
	1    6475 1025
	1    0    0    1   
$EndComp
Wire Wire Line
	9425 1000 9425 1075
Connection ~ 9425 1075
Wire Wire Line
	9600 1000 9600 1175
Connection ~ 9600 1175
Wire Wire Line
	6150 950  6150 1025
Wire Wire Line
	6150 1025 6225 1025
$Comp
L power:+5V #PWR018
U 1 1 5E3EA726
P 6800 950
F 0 "#PWR018" H 6800 800 50  0001 C CNN
F 1 "+5V" H 6800 1090 50  0000 C CNN
F 2 "" H 6800 950 50  0001 C CNN
F 3 "" H 6800 950 50  0001 C CNN
	1    6800 950 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6800 950  6800 1025
Wire Wire Line
	6800 1025 6725 1025
Wire Wire Line
	9600 625  9600 700 
Wire Wire Line
	6475 625  8825 625 
Wire Wire Line
	9425 625  9425 700 
Connection ~ 9425 625 
Wire Wire Line
	6475 625  6475 925 
Connection ~ 8825 625 
$Comp
L power:GND #PWR019
U 1 1 5E3ED47A
P 5750 1900
F 0 "#PWR019" H 5750 1650 50  0001 C CNN
F 1 "GND" H 5750 1750 50  0000 C CNN
F 2 "" H 5750 1900 50  0001 C CNN
F 3 "" H 5750 1900 50  0001 C CNN
	1    5750 1900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5750 1900 5750 1825
Wire Wire Line
	5750 1825 5150 1825
Wire Notes Line
	9275 1250 9275 575 
Wire Notes Line
	9275 575  9700 575 
Wire Notes Line
	9700 575  9700 1250
Wire Notes Line
	9700 1250 9275 1250
Text Notes 9725 925  0    60   ~ 0
OLEDs usually include\nthese, no need to\ninstall unless needed.
Wire Notes Line
	6000 575  6950 575 
Wire Notes Line
	6950 575  6950 1250
Wire Notes Line
	6950 1250 6000 1250
Wire Notes Line
	6000 1250 6000 575 
Text Notes 5925 1025 2    60   ~ 0
OLEDs usually work\nin either position,\nlink pins 1-2 for 3.3v.
Text Notes 7000 7025 0    60   ~ 0
Based on the DigiWavuino, but I wanted to build my own version of it with a lot of\nfeatures no one would ever need - mostly because I wanted to play around with\nvarious things Arduino. There is an option for using either an 128x32 or 128x64 OLED,\ninstall whichever you want and hope that the software supports it - alternatively, use\none of the available faceplates and install the display there instead.
Wire Wire Line
	9150 5575 9150 5650
Wire Wire Line
	9150 5225 9150 5575
Wire Wire Line
	9150 4875 9150 5225
Wire Wire Line
	9150 4525 9150 4875
Wire Wire Line
	6700 4625 6700 4700
Wire Wire Line
	4625 5275 4700 5275
Wire Wire Line
	4175 5275 4250 5275
Wire Wire Line
	3725 5275 3800 5275
Wire Wire Line
	4175 5725 4625 5725
Wire Wire Line
	3725 5725 4175 5725
Wire Wire Line
	4625 5725 4625 5800
Wire Wire Line
	3350 5275 3450 5275
Wire Wire Line
	3350 5275 3350 5350
Wire Wire Line
	3350 5725 3725 5725
Wire Wire Line
	5075 5275 5500 5275
Wire Wire Line
	5075 5275 5075 6250
Wire Wire Line
	3050 5725 3350 5725
Wire Wire Line
	2775 5400 2775 5725
Wire Wire Line
	2500 4050 2500 4300
Wire Wire Line
	2500 4300 2500 4725
Wire Wire Line
	1525 4550 1525 4650
Wire Wire Line
	1525 4300 1525 4550
Wire Wire Line
	1500 5025 1825 5025
Wire Wire Line
	8450 1175 8675 1175
Wire Wire Line
	8825 1075 8825 1250
Wire Wire Line
	8975 1075 8975 1250
Wire Wire Line
	9125 1175 9125 1250
Wire Wire Line
	9425 1075 9975 1075
Wire Wire Line
	9600 1175 9975 1175
Wire Wire Line
	9425 625  9600 625 
Wire Wire Line
	8825 625  9425 625 
Wire Bus Line
	10075 4275 10075 4975
Wire Bus Line
	10075 4975 10075 5675
Wire Bus Line
	10075 2850 10075 3150
Wire Bus Line
	7650 4050 7650 4350
Wire Bus Line
	5750 3650 5750 4150
Wire Bus Line
	7650 3250 7650 4050
Wire Bus Line
	5600 2025 5600 5375
$EndSCHEMATC
