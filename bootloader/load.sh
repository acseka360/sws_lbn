# download from https://github.com/adafruit/Adafruit_nRF52_Bootloader
nrfjprog --recover -f nrf52
#Recovering device. This operation might take 30s.
#Erasing user code and UICR flash areas.
nrfjprog --program pca10056_bootloader-0.10.0_s140_6.1.1.hex --verify -f nrf52
#[ #################### ]   1.268s | Program file - Done programming
#[ #################### ]   1.442s | Verify file - Done verifying
nrfjprog --reset -f nrf52
#Applying system reset.
#Run.

