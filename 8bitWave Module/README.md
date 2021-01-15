# 8BIT Wave Module

The 8BIT Wave module is the main heart of the project, it contains most of the active components found within the project. Building the module requires that you take some time to consider to which options you require, some in the case of the chosen amplifier are mutually exclusive and they both have their plusses and minuses. If you're still in the process of ordering components, skip to the BOM section of the document and start there - note that other modules such has the faceplate will have their documents detailing their construction and part specifications.

- [1> Building the module]
  - 1.1> Installing common components
  - 1.2> Installing low-pass filter
  - 1.3> Installing amplifier
    - 1.3.1 LM386 amplifier option
    - 1.3.2 GF1002 amplifier option
- 2> Schematic
- 3> BOM
  - 3.1> Common components
  - 3.2> LM386 (amplifier)
  - 3.3> GF1002 (amplifier)
  - 3.4> Low-pass filter

## 1> Building the module
So you've decided that you want the 8BIT Wave in your life, a bold choice and might I go so far as smile that someone took the time to build something I designed. The first step before breaking out the soldering iron, you can't use a glue-gun for this unless you do some extreme overclocking on the thing, is going through and ordering all the little bits you'll need. This should all be detailed inside the section later in this document, called the [BOM](#3-bom) (bill of manufacturing). Note that you will however have to make some decisions about a few of the options, mainly the amplification used and whether you want to install components for the low-pass filter. Read each section carefully before you commit to something, components are always harder to desolder than it is to solder them into place (when in doubt and have the extra PCB, just build another one - twice the solder fumes for just about the same price).

Got everything needed? Awesome. Break out your soldering iron, add some water to the sponge and start soldering at a reasonably controlled temperature. I have my iron set around 340 degrees Celsius, in Fahrenheit that would be too cold to accomplish much [cue laugh track]!

Continue by following sections [1.1](#11-installing-common-components) to install common common components, [1.2](#12-installing-low-pass-filter) to install a low-pass filter (if needed) and finally the amplifier option you require by following on in section [1.3](#13-installing-amplifier).

- [1.1> Installing common components](#11-installing-common-components)
- [1.2> Installing low-pass filter]((#12-installing-low-pass-filter))
- [1.3> Installing amplifier](#13-installing-amplifier)

### 1.1> Installing common components
Solder parts specified in [common components](#31-common-components) into place, but take note that depending on the build you're going for you'll probably need to use some hex standoffs between this module and the faceplate - the ones I'm using is 12mm tall. You might get away with substituting the long pin headers with the regular ones if you opt to install the Arduino directly without anything in between, but doing so requires you to do some dry-fitting along the way to make sure nothing becomes too short (a long pin can be cut, a short one can be heated and pushed a bit through to make up for it).

![Some components](https://github.com/tebl/8BIT-Wave/raw/master/gallery/build_001.jpg)

The modules that can be installed directly on the board is shown above, both of them usually come with pin headers already attached - we'll deal with those along the way. The display you can probably put aside as you've most likely opted for installing it on one of my beautiful faceplates instead (I can't blame you, that was really what this project was all about). If you however do not want the faceplate (why though?), make sure you install the display as the last thing you ever do - otherwise you'll have problems installing components below it (add some electrical tape between the modules to avoid accidentally shorting things).

The MicroSD Card Adapter will come with right-angle header attached to it, just straighten them using some pliers. Add some double-sided tape to the top of the MicroSD-slot, turn it upside down and solder it into place on the module.

![Common components installed](https://github.com/tebl/8BIT-Wave/raw/master/gallery/build_002.jpg)


### 1.2> Installing low-pass filter
Solder in the parts for the [low-pass filter](#34-low-pass-filter), unless you know you'll need them. They have been shown to make programs easier to load on the MSX-line of computers though it's the only place I think it is needed. If you chose to skip the installation, feel free to install a wire-link across J5 pins 1-2. With the filter installed, add some dual-row header pins to J5 - disable the filter by placing a jumper across pins 1-2 as before. When enabling the feature you'll need to remove this jumper, instead add jumpers across pins 3-4 and 5-6. 

### 1.3> Installing amplifier
With this step out of the way, we're ready to install one of the amplifier options, the easiest one is simply using the module without an amplifier - install jumpers across J7 pins 1-2 as well as 11-12 to use the output directly (this will also allow you to bypass an installed amplifier). The following sections assume that you've chosen to install either LM386 or GF1002 amplifier, they operate at different voltages and should not be installed in the same system.

- [1.3.1> LM386 amplifier option](#131-lm386-amplifier-option)
- [1.3.2> GF1002 amplifier option](#132-gf1002-amplifier-option)

#### 1.3.1 LM386 amplifier option
Using the classic LM386 amplifier is more or less the goto choice for any amateur hardware tinkerer, thinking mostly about me here - you're probably awesome so don't worry about it! It is also a common option found on other tzxduino boards, but note that the module really requires 9v to function properly with a few vintage systems, even just specific revisions may require this as opposed to the 5v provided by the Arduino.

Try it out, it might work perfectly at 5v too so you need to try out which works best for the systems you have. If you explicitly don't want to add a 9v power supply into the mix, the [GF1002 amplifier](#132-gf1002-amplifier-option) is a different option that has been designed to operate at 5v.

Still here? 9v center positive power supply it is then. Install components specified in the [BOM](#33-fg1002-amplifier). Link pins JP6 pins 2-3 and make a checkmark in the 9v checkbox on the back of the module, this is here so you don't accidentally connect the wrong voltage to the module. Note that with JP6 in the wrong position, this will more than likely fry most of the components on the board - do it right or watch it burn (probably a lot less spectacular than that)! Refer to the picture below if in doubt.

![LM386 Install](https://github.com/tebl/8BIT-Wave/raw/master/gallery/build_lm386_001.jpg)

Most components can be installed as shown, but in order to keep the spacing between the module and faceplate as little as possible (12mm by my count) you'll need to install some of the components on their side - the capactitors especially can be tall, by putting them on the side you have a bit more room to work with. The same goes for the volume control, this is the same 10k bourns 3296w potentiometer most usually have in their parts bin - what I've done is simply mount it on the side by bending the pins. It is then anchored to the board by using some leftover wire-cuttings from one of the LEDs.

As mentioned before, J7 configures the amplification used by the system. You can use jumper pins 1-2 to bypass the LM386 if needed, but since you're here you probably want to enable the thing - this is done by adding jumpers across 5-6 instead (assuming you still have a jumper in place across pins 11-12).

#### 1.3.2 GF1002 amplifier option
The GF1002 amplifier module, based on PAM8403 module, is a stereo amplifier that's been designed for use with 5v (LM386 requires 9v) power sources so it is a good match for the *8BIT Wave*. For the most part it is easy to install, but feel free to refer to section [3.3](#33-gf1002-amplifier) for a list of parts needed and install them as you see fit - a picture of the completed module can be seen below.

![GF1002 Install](https://github.com/tebl/8BIT-Wave/raw/master/gallery/build_gf1002_001.jpg)

The most important thing to remember when installing it is that the audio jacks must be in place before you attempt to install the GF1002, mainly because they will be partially covered by the module. You will also need to have the module in part recessed into the cutout on the PCB, this was done so that the overall thickness of all the PCBs can be kept to a minimum. Use long pin headers, break them into sections and use those when soldering it in at the correct height - ideally it'll be resting comfortably on top of the 3.5mm audio jack.

![GF1002 Install](https://github.com/tebl/8BIT-Wave/raw/master/gallery/build_gf1002_002.jpg)
![GF1002 Install](https://github.com/tebl/8BIT-Wave/raw/master/gallery/build_gf1002_003.jpg)

Power can also be supplied directly by plugging in a 5v DC (center positive) power supply into the barrel connector, this require JP6 to have a wire-ling across pins 1-2. These components are listed as optional (in parenthesis), so make a checkmark in the corresponding box on the back of the module board to mark it as such.

As mentioned before, J7 configures the amplification used by the system. You can use jumper pins 1-2 to bypass the GF1002 if needed, but since you're here you probably want to enable the thing - this is done by adding jumpers across J7 pins 7-8 as well as pins 9-10. Note that no other J7 pins should be jumpered here, the GF1002 needs to have it's own ground and shorting it using pins 11-12 will cause it to overheat and shut down.

# 2> Schematic
The supplied KiCad files should be sufficient as both a schematic and as a  starting point for ordering PCBs (basically you could just zip the contents of the export folder and upload that on a fabrication site), the schematic is also available in [PDF-format](https://github.com/tebl/8BIT-Wave/tree/master/documentation/schematic) found within the schematics-part of the [documentation](https://github.com/tebl/8BIT-Wave/tree/master/documentation).

# 3> BOM
Most parts should be easy to get a hold of from your favourite local electronic component shop, but given that I don't have access to such shops where I live so everything was based on whatever I could get cheapest from eBay/AliExpress (free shipping, plan on waiting 3-4 weeks for delivery though).

As described in the section *building the module*, the BOM will also need to be divided into various sections depending on the chosen build - these difference between these is the choice of amplifier installed. Common components are needed for all of them, refer to the rest for a different choice - do note however that the option of no amplification similar to what is found on the tzxduino compact is also an option. Components listen in parenthesis is to be considered optional, some of them will be obsolete when using a faceplate (only one display needed).

# 3.1> Common components
These are the components that will be required on all variants of the 8BIT Wave, do note that depending on options chosen the design may be simplified by doing part substitutions. In particular the long pin can be substituted by ordinary pin headers if all components are soldered directly to the PCB without using sockets, LM386 or no amplifier etc. Refer to the following [picture](https://github.com/tebl/8BIT-Wave/raw/master/gallery/2020-02-22%2000.55.06.jpg) if you're wondering what the MicroSD Card Adapter module looks like.

| Reference    | Item                                                 | Count |
| ------------ | ---------------------------------------------------- | ----- |
| PCB          | Fabricate using Gerber files                         |     1 |
| A1           | Arduino Nano or Every                                |     1 |
| A2           | MicroSD Card Adapter for Arduino                     |     1 |
| C10          | 100uF 16V electrolytic capacitor                     |     1 |
| D1,D2 **     | 5mm LED                                              |    (2)|
| IC1          | SSD1306 I2C OLED 128x64 (0.96")                      |    (1)|
| J1           | PJ-210 2.5mm audio socket                            |    (1)|
| J2           | PJ-307 3.5mm audio socket (5 pin)                    |     1 |
| J6,JP5       | 3 pin straight header (long pins)                    |     2 |
| J3           | 7 pin header (long pins)                             |     1 |
| J5 *         | 2x3 straight pin header                              |     1 |
| J7           | 2x7 straight dual row pin header                     |     1 |
| R6,R7 **     | 330 Ohm resistor                                     |    (2)|
| R8,R9 ***    | 4k7 (4700) Ohm resistor                              |    (2)|
| SW1-SW5      | 6x6x5mm right-angle momentary button                 |     5 |
| Jumpers      | Pin header jumper caps                               |     5 |

*) This is used to enable/disable the low-pass filter, if you don't need or want to install the components listed in section 3.4 you can just install a wire link across pins 1-2 to permanently bypass it.

**) These components are only on the 8BIT-Wave, the Maxduino firmware does not support them so they are listed as optional.

***) These are I2C pull-ups, these are normally needed as the OLED-displays tend to already come with those installed there. Only install if you've verified that this is the issue.

# 3.2> LM386 (amplifier)
The classic option for amplifying the audio signal on a tzxduino. No amplification at all is also an option that can be considered, but with some systems and even revisions of specific systems there will be different audio requirements that will require active amplification (see 3.3 for a different option).

Note that the LM386 really needs more than 5v to function properly, so you'll need to power the system with a 9v DC (center positive) using the barrel connector. This requires JP6 to have a wire-link between pins 2-3, pins 1-2 should only be linked if you mean to use a different amplification option and a 5v DC (center positive) power supply. Make a checkmark on the 9v section on the back of the board.

| Reference    | Item                                                 | Count |
| ------------ | ---------------------------------------------------- | ----- |
| C5           | 100nF ceramic capacitor (5mm)                        |     1 |
| C6,C8        | 10uF 16V electrolytic capacitor                      |     2 |
| C7           | 100uF 16V electrolytic capacitor                     |     1 |
| C9           | 47nF ceramic capacitor (5mm)                         |     1 |
| C11          | 220uF 16V electrolytic capacitor                     |     1 |
| D3           | 1n4001 diode (DO-41)                                 |     1 |
| J4           | 5.5mm x 2.1mm barrel connector (PCB mount)           |     1 |
| R5           | 10 Ohm resistor                                      |     1 |
| RV2          | Bourns 3296W 10k ohm potentiometer                   |     1 |
| JP1,JP6      | 3 pin straight header with jumper                    |     2 |
| JP4          | 2 pin straight header with jumper                    |     1 |


# 3.3> GF1002 (amplifier)
This amplifier option is available as a separate option, it comes with the PAM8403 chip that has the added advantage that it only requires 5v - this allows everything to be powered by the voltage regulator on the Arduino Nano/Every.

It is however very power-hungry on startup so with some Arduino boards I've experienced reboots when it is clicked off and on again - not especially cool, but the Arduino recovers beautifully so I've not invested much energy into finding a solution. Some boards may have an easier time when 5v DC (center positive) is directly supplied to the board via the barrel connector - this require JP6 to have a wire-ling across pins 1-2. These components are listed in parenthesis, make a checkmark in the corresponding box on the back of the module board to mark it as such.

| Reference    | Item                                                 | Count |
| ------------ | ---------------------------------------------------- | ----- |
| A3           | GF1002 Amplifier module *                            |     1 |
|              | 1x9 pin long pin headers                             |     1 |
| C11          | 220uF 16V electrolytic capacitor                     |    (1)|
| D3           | 1n4001 diode (DO-41)                                 |    (1)|
| J4           | 5.5mm x 2.1mm barrel connector (PCB mount)           |    (1)|

*) If you can't find a cheap one, search for PAM8403 and look for one that has a green potentiometer on it.

# 3.4> Low-pass filter
These components are used to add low-pass filtering to the signal, from what I can read online these are generally only used with the MSX-line of computers. If you don't have an MSX and explicitly don't want one, you might as well add a wire link for positions 1-2 on J5. Add jumpers across 3-4 and 5-6 to enable this feature.

| Reference    | Item                                                 | Count |
| ------------ | ---------------------------------------------------- | ----- |
| R1-R4        | 4k7 (4700) Ohm resistor                              |     4 |
| C1           | 100nF ceramic capacitor (5mm)                        |     1 |
| C2-C4        | 4.7nF ceramic capacitor (5mm)                        |     3 |
