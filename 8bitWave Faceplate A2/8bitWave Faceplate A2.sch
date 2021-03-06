EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "8BIT WAVE Faceplate"
Date ""
Rev "B"
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
L I2C_OLED:0.96_I2C_OLED IC1
U 1 1 5E3B718A
P 7000 4525
F 0 "IC1" H 7000 4350 60  0000 C CNN
F 1 "0.96_I2C_OLED" H 6975 4475 43  0000 C CNN
F 2 "i2c_oled:0.96_I2C_OLED2" H 7000 5150 60  0001 C CNN
F 3 "" H 7000 5150 60  0001 C CNN
	1    7000 4525
	-1   0    0    -1  
$EndComp
Text Label 5950 3900 0    60   ~ 0
SCL
Entry Wire Line
	5825 4000 5925 3900
Text Label 5950 4000 0    60   ~ 0
SDA
Entry Wire Line
	5825 4100 5925 4000
Wire Wire Line
	6925 3900 5925 3900
Wire Wire Line
	6775 4000 5925 4000
Wire Bus Line
	5825 4100 5825 4000
$Comp
L extension:Extension J3
U 1 1 5E3D299E
P 3850 3800
F 0 "J3" H 3850 4200 50  0000 C CNN
F 1 "EXTENSION" V 3950 3800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x07_Pitch2.54mm" H 3850 3800 50  0001 C CNN
F 3 "" H 3850 3800 50  0001 C CNN
	1    3850 3800
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5E3D3470
P 4125 4175
F 0 "#PWR01" H 4125 3925 50  0001 C CNN
F 1 "GND" H 4125 4025 50  0000 C CNN
F 2 "" H 4125 4175 50  0001 C CNN
F 3 "" H 4125 4175 50  0001 C CNN
	1    4125 4175
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4125 4175 4125 4100
Wire Wire Line
	4125 4100 4050 4100
Entry Wire Line
	4800 4000 4700 3900
Wire Wire Line
	4050 3900 4700 3900
Entry Wire Line
	4800 4100 4700 4000
Wire Wire Line
	4050 4000 4700 4000
Text Label 4675 4000 2    60   ~ 0
SCL
Text Label 4675 3900 2    60   ~ 0
SDA
$Comp
L i2c_voltage:I2C_VOLTAGE J1
U 1 1 5E3E91C2
P 925 2300
F 0 "J1" H 875 2500 50  0000 L CNN
F 1 "I2C_VOL" V 1050 2300 50  0000 C BNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 925 2300 50  0001 C CNN
F 3 "" H 925 2300 50  0001 C CNN
	1    925  2300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1200 2200 1125 2200
$Comp
L power:GND #PWR03
U 1 1 5E3ED47A
P 4175 3575
F 0 "#PWR03" H 4175 3325 50  0001 C CNN
F 1 "GND" H 4175 3425 50  0000 C CNN
F 2 "" H 4175 3575 50  0001 C CNN
F 3 "" H 4175 3575 50  0001 C CNN
	1    4175 3575
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4175 3500 4175 3575
$Comp
L power:VCC #PWR04
U 1 1 5E3EF557
P 1350 2225
F 0 "#PWR04" H 1350 2075 50  0001 C CNN
F 1 "VCC" H 1350 2375 50  0000 C CNN
F 2 "" H 1350 2225 50  0001 C CNN
F 3 "" H 1350 2225 50  0001 C CNN
	1    1350 2225
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 2225 1350 2300
Wire Wire Line
	1350 2300 1200 2300
Wire Wire Line
	6925 3900 6925 4075
Wire Wire Line
	6775 4000 6775 4075
Wire Wire Line
	1200 2200 1200 2300
Connection ~ 1200 2300
Text Notes 7000 6750 0    60   ~ 0
Over-engineered by design, but it's all in a days fun so extended it to include some SMD\nblinkenlights. The only needed components is just the OLED display.
Wire Wire Line
	1200 2300 1125 2300
$Comp
L Connector_Generic:Conn_01x10 J2
U 1 1 5E5F2F04
P 925 1375
F 0 "J2" H 843 1992 50  0000 C CNN
F 1 "SPI" H 843 1901 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10_Pitch2.54mm" H 925 1375 50  0001 C CNN
F 3 "~" H 925 1375 50  0001 C CNN
	1    925  1375
	-1   0    0    -1  
$EndComp
NoConn ~ 1125 1675
NoConn ~ 1125 1775
NoConn ~ 1125 975 
NoConn ~ 1125 1075
NoConn ~ 1125 1175
NoConn ~ 1125 1275
NoConn ~ 1125 1375
NoConn ~ 1125 1475
NoConn ~ 1125 1575
NoConn ~ 1125 1875
Text Notes 1200 1625 0    60   ~ 0
Not actually used at\nthis point, it is here\nas an option for\nmounting (and\nsymmetry).
$Comp
L I2C_OLED:Polarity_Select JP2
U 1 1 5ED85DD0
P 7775 3700
F 0 "JP2" H 7775 3904 50  0000 C CNN
F 1 "PIN1_GND" H 7775 3813 50  0000 C CNN
F 2 "wire_pads:OLED_SEL" H 7775 3700 50  0001 C CNN
F 3 "~" H 7775 3700 50  0001 C CNN
	1    7775 3700
	1    0    0    -1  
$EndComp
$Comp
L I2C_OLED:Polarity_Select JP1
U 1 1 5ED8BDDA
P 7775 3100
F 0 "JP1" H 7775 3304 50  0000 C CNN
F 1 "PIN2_VCC" H 7775 3213 50  0000 C CNN
F 2 "wire_pads:OLED_SEL" H 7775 3100 50  0001 C CNN
F 3 "~" H 7775 3100 50  0001 C CNN
	1    7775 3100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5ED9181E
P 7450 3775
F 0 "#PWR0101" H 7450 3525 50  0001 C CNN
F 1 "GND" H 7450 3625 50  0000 C CNN
F 2 "" H 7450 3775 50  0001 C CNN
F 3 "" H 7450 3775 50  0001 C CNN
	1    7450 3775
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7450 3775 7450 3700
Wire Wire Line
	7450 3700 7525 3700
Wire Wire Line
	8025 3700 8100 3700
Wire Wire Line
	8100 3700 8100 3625
$Comp
L power:VCC #PWR0102
U 1 1 5EDA6198
P 8100 3625
F 0 "#PWR0102" H 8100 3475 50  0001 C CNN
F 1 "VCC" H 8100 3775 50  0000 C CNN
F 2 "" H 8100 3625 50  0001 C CNN
F 3 "" H 8100 3625 50  0001 C CNN
	1    8100 3625
	-1   0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0103
U 1 1 5EDABD2C
P 7450 3025
F 0 "#PWR0103" H 7450 2875 50  0001 C CNN
F 1 "VCC" H 7450 3175 50  0000 C CNN
F 2 "" H 7450 3025 50  0001 C CNN
F 3 "" H 7450 3025 50  0001 C CNN
	1    7450 3025
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7450 3025 7450 3100
Wire Wire Line
	7450 3100 7525 3100
$Comp
L power:GND #PWR0104
U 1 1 5EDB6E50
P 8100 3175
F 0 "#PWR0104" H 8100 2925 50  0001 C CNN
F 1 "GND" H 8100 3025 50  0000 C CNN
F 2 "" H 8100 3175 50  0001 C CNN
F 3 "" H 8100 3175 50  0001 C CNN
	1    8100 3175
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8100 3175 8100 3100
Wire Wire Line
	8100 3100 8025 3100
Wire Wire Line
	7775 4000 7225 4000
Wire Wire Line
	7225 4075 7225 4000
Wire Wire Line
	7775 3250 7775 3325
Wire Wire Line
	7775 3325 7075 3325
Wire Wire Line
	7775 3850 7775 4000
Wire Wire Line
	7075 3325 7075 4075
Entry Bus Bus
	5725 3900 5825 4000
Entry Bus Bus
	4900 3900 4800 4000
Wire Bus Line
	4800 4100 4800 4000
Wire Bus Line
	4900 3900 5725 3900
NoConn ~ 4050 3600
NoConn ~ 4050 3700
NoConn ~ 4050 3800
NoConn ~ 1125 2400
Wire Wire Line
	4175 3500 4050 3500
$EndSCHEMATC
