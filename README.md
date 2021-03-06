# 8BIT Wave
8BIT Wave is a project I started in order to build a digital cassette deck for my old 8-bit retro computers, my starting point was the schematic provided as part of the [DigiWavuino](https://github.com/rickyelqasem/DigiWavuino) project by Ricky ElQasem though it's more or less grown towards being its own thing since then. Later versions also support the [Maxduino](https://github.com/rcmolina/MaxDuino_v1.66)-firmware (includes tzxduino and arduitape functionality), that way I can use it with most - if not all of my vintage computers using one device (refer to maxduino documentation). Anyway, enough of all that - here is a picture of the device loading a game on ZX Spectrum:

![8Bit Wave](https://github.com/tebl/8BIT-Wave/raw/master/gallery/2020-06-22%2022.42.22.jpg)

One of my goals with the project has been to build the device I always wanted, the idea was to have something that looked like a cassette tape yet had all the functionality of maxduino and similar firmware. There is a firmware in the software-directory of this repository, but that was more a way of playing around with the Arduino without ever intending to finish it (it is only there in case someone wants to study and laugh at my cut-and-paste style of coding).

So my major contribution for this projection, to the world in general, is in the form of the three PCBs and some added amplifier options not found on any of the other open tzxduino clones I've looked at. The other goal, apart from looking cool was having a case without actually fixing my 3d-printer so for that reason the project also includes a backplate - this allows the user to avoid having to touch bare electronics when they handle it.

![Module stacking](https://github.com/tebl/8BIT-Wave/raw/master/gallery/2020-06-16%2018.38.42.jpg)

It is my belief that this project can be put together by anyone with moderate skills at soldering together components, but take care that you read through all of the documentation provided and not just start somewhere in the middle. All the components I've used are from chinese vendors such as AliExpress, banggood and ebay so the descriptions will reflect this (none of those sites have consistent part descriptions, so treat the parts list as general search terms and try to match them to pictures).

Further details will be available as part of the documentation for each of the [modules](#2-modules), see below for links.

## 1> Project status
There will always be things to do and polish, but at the current state it is an open design that can be used with the [MaxDuino](https://github.com/rcmolina/MaxDuino_v1.54). Note that different computers have that special sweet spot, so that you will need to do some tweaking in order to find what works best with your specific setup. 

## 2> Modules
The project has been split into several modules, these will be stacked together to a complete player. Faceplates and backplates can be considered optional, but normally you would only need one of each (some variants will be added later to match various displays so check out the description for each module before you commit).

| Module    |  | Order |
| --------- | ---------- | ----- |
| [8BitWave Module](https://github.com/tebl/8BIT-Wave/tree/master/8bitWave%20Module) | required | [PCBWay](https://www.pcbway.com/project/shareproject/8BitWave_Module.html) |
| [8BitWave Faceplate A1](https://github.com/tebl/8BIT-Wave/tree/master/8bitWave%20Faceplate%20A1) | optional | |
| [8BitWave Faceplate A2](https://github.com/tebl/8BIT-Wave/tree/master/8bitWave%20Faceplate%20A2) | recommended | [PCBWay](https://www.pcbway.com/project/shareproject/8BitWave_Faceplate.html) |
| [8BitWave Backplate](https://github.com/tebl/8BIT-Wave/tree/master/8bitWave%20Backplate) | optional | [PCBWay](https://www.pcbway.com/project/shareproject/8BitWave_Backplate.html) |

I'm using PCBway because I get a discount for every PCB ordered via them, so if you want to support this project then that is the way to do it. For other fabrication houses you would normally need to do is zip-up the contents of the export directory for each module and hand them those files (these are what is known as Gerber files). Note that the latest Gerber files may contain changes not yet tested by me, so if you want the ones I've tested then checkout my [PCBway shared projects](https://www.pcbway.com/project/shareproject/?tag=8BIT-Wave) relating to this project.