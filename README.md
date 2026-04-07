# Lora Battery Node
## Solder WorkShop *Advanced Track*

### PCB

Check out the PCB files with [Kicad 10](https://www.kicad.org/)

- Open the kicad\_pro project file
- Look at the schematic with the "Schematic Editor"
- Proceed to the "PCB editor" and push Alt-F3 to get into the 3D viewer

### Assembly

The interactive [BOM
webpage](https://htmlpreview.github.io/?https://github.com/acseka360/sws_lsbn/blob/master/bom/ibom.html)
helps during assembly. You can mark components placed and check their exact
types.

### 3D printed case

[Freecad 1.1](https://www.freecad.org/) made the 3d printed case files.


### Bringup

Initially a [J-Link](https://www.segger.com/products/debug-probes/j-link/) or
equivalent swd flasher is needed to load the bootloader on the virgin chip.

Use the *pca10056* type from the
[Adafruit](https://github.com/adafruit/Adafruit_nRF52_Bootloader/releases) repo.


### Software

You will need [PlatformIO](https://platformio.org/) to compile and install it.

First the bootstrapping firmware is needed, to set the IO voltages to 3.3V
permanently from the default 1.8V.

Then you can get the upstream
[Meshtastic](https://github.com/meshtastic/firmware) repo, that you should merge 
into the firmware folder, where our custom variant files already describe the 
board.
