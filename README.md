# 8BIT Wave
8BIT Wave is a project in an early stage, my goals for it is building a digital cassette deck for my old 8-bit retro computers with the [DigiWavuino](https://github.com/rickyelqasem/DigiWavuino) project by Ricky ElQasem as my starting point. Given what they are and how they were originally designed everything here should be familiar to all who've taken a look at a Tzxduino/Arduitape schematic as well, but where they differ is mainly in the way they amplify the signal.

![8Bit Wave](https://github.com/tebl/8BIT-Wave/raw/master/gallery/2020-02-25%2000.56.09.jpg)

I've included the option of using a cheap standalone GF1002 module, building an onboard LM386-based solution or simply running the signal more or less direct from the Arduino Nano. Certainly complicates the heck out of everything, but it should allow for more than one option when attempting to make it all work with your specific setup. A MicroSD Card Adapter module for Arduino was chosen for this project as they are often sold in packs of three, they come with right-angle pin headers that are simply straightened and then inserted into the board (use adhesive pad for support).

While all major components can be installed on the main module, I've also taken the time to add a faceplate and a backplate for use with the module. While the former adds a nice way of framing the OLED display, the latter is simply there in order to keep the user from having to handle the soldered contacts on the bottom of the module (in place of a 3d-printed case).

![Module stacking](https://github.com/tebl/8BIT-Wave/raw/master/gallery/2020-06-16%2018.38.42.jpg)

The Arduino Nano (Atmega328 variety) can be soldered directly onto the board in order to reduce the overall height when compared with using male and female pin-headers, preferably you should ensure that it is working before doing so. Refer to the picture above in order to get an idea of how the modules are stacked together, take care to always install the 3.5mm and 2.5mm jacks before the GF1002 module if you are going that route as they would be sitting below the module.

Further details and lists of required components can be found below under "modules".

## Project status
Currently it does not seem to load much of anything anywhere, but I managed to make it load one game on the Dragon 32 using the [MaxDuino](https://github.com/rcmolina/MaxDuino_v1.54) firmware so there is hope that someday I'll be able to make it reliable enough for general use. Different computers do however require finding that special sweet spot in order to even attempting to look like they're loading something, so in that respect it should for the most part be familiar to all who owned one back when they were new. 

## Modules
The project has been split into several modules, these will be stacked together to a complete player. Faceplates and backplates are optional, but normally you would only need one of each (some variants to be added later to match various displays).

| Module    |  | Order |
| --------- | ---------- | ----- |
| [8BitWave Module](https://github.com/tebl/8BIT-Wave/tree/master/8bitWave%20Module) | required | [PCBWay]() |
| [8BitWave Faceplate](https://github.com/tebl/8BIT-Wave/tree/master/8bitWave%20Faceplate) | recommended | [PCBWay]() |
| [8BitWave Backplate](https://github.com/tebl/8BIT-Wave/tree/master/8bitWave%20Backplate) | optional | [PCBWay]() |