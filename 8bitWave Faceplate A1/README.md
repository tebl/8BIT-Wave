# 8BIT Wave Faceplate A1

The faceplate is mainly what separates the *8BIT Wave* from all other tzxduino clones, it makes it *really really cool* (to quote a really really cool comedy about male supermodels)! You could actually do without the thing entirely as the OLED-display could potentially be installed on the main module instead, but what would the fun be in building a unit that'd be less than what it could be.

![Faceplate](https://github.com/tebl/8BIT-Wave/raw/master/gallery/build_faceplate_001.jpg)

## 1> Building the module

Start by checking out the [BOM](#3-bom) and verify that you have the components needed before continuing, it's beyond frustrating to realize you need just that single item before being able to complete the build - with shipping times from China as they are, better to get it right the first time (if it's very cheap I tend to order several just in case one gets delayed somewhere).

Before building the faceplate you need to first determine which variation of the 128x64 SSD1306 OLED-display (0.96") you actually have, there is the **original** one used by this faceplate - the newer variation is slightly smaller and incompatible with this PCB as the mounting is different. Refer to the picture below when ordering, one giveaway is that the newer variation have a narrower ribbon cable at the bottom.

![OLED-display variations](https://github.com/tebl/8BIT-Wave/raw/master/gallery/build_faceplate_displays.jpg)

The actual display usually comes with pin headers already installed, which is unfortunate as they are on the wrong side - refer to the pictures below to see how it is meant to fit into the mounting. You could always try desoldering the pins, but I've found that this is a rather cumbersome step - even with the suitable tools available to me. The easiest solution however is to melt the solder on a single pin using your soldering iron, then pushing the pin through the PCB using something metal like a pair of pliers (remember: hot metal burns - a lot).

![Faceplate](https://github.com/tebl/8BIT-Wave/raw/master/gallery/build_faceplate_002.jpg)

Align the pins with the front of the PCB and solder it in place. Use M2 nylon screws and nuts to affix the bottom, this keeps people from accidentally pushing the display into the case. On the back of the faceplate, there are two solder connections that need to be made - JP1 and JP2. These need to be shorted according to the order of pins used on the OLED-display, solder accross *1-2* if the first one is marked **GND**. Pins *2-3* if it is marked **VCC**.

![Faceplate](https://github.com/tebl/8BIT-Wave/raw/master/gallery/build_faceplate_003.jpg)

As the last step, solder into place the female pin headers on the underside of the faceplate - like pictured. There are extra pads on one of them, this is just there because I wanted it to be symmetrical (*I KNOW*). Theoretically you could install extra long pin headers here and solder it directly to the module under, but that is only recommended when building several units at once and the components being used have been verified.

Earlier revisions have pads for SMD LEDs that can be lit up using a couple of shift registers, I've not included these in the BOM as this is features not supported in any of the firmwares available. I might remove them entirely at a later point in order to keep everything through-hole components.

# 2> Schematic
The supplied KiCad files should be sufficient as both a schematic and as a  starting point for ordering PCBs (basically you could just zip the contents of the export folder and upload that on a fabrication site), the schematic is also available in [PDF-format](https://github.com/tebl/8BIT-Wave/tree/master/documentation/schematic) found within the schematics-part of the [documentation](https://github.com/tebl/8BIT-Wave/tree/master/documentation).

# 3> BOM
Most parts should be easy to get a hold of from your favourite local electronic component shop, but given that I don't have access to such shops where I live so everything was based on whatever I could get cheapest from eBay/AliExpress (free shipping, plan on waiting 3-4 weeks for delivery though).

| Reference    | Item                                                 | Count |
| ------------ | ---------------------------------------------------- | ----- |
| PCB          | Fabricate using Gerber files                         |    (1)|
| IC1          | SSD1306 I2C OLED 128x64 (0.96") (**"Original"**)     |    (1)|
| J1 *         | Female 3 pin header                                  |     1 |
| J2           | Female 10 pin header                                 |    (1)|
| J3 *         | Female 7 pin header                                  |     1 |

*) J1 and J3 are placed right next to eachother, so you could just install a female 10 pin header here. That'll also reduce number of parts needed by one, if that matters.