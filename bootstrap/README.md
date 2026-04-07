# E73 REGOUT0 3.3V Provisioner

Minimal PlatformIO project for your E73/nRF52840 board.

## What it does
- Brings up USB CDC serial at 115200
- Enables both nRF52840 DC/DC stages at runtime
- Prints current POWER/UICR state
- Programs `UICR->REGOUT0` to 3.3V
- Reads it back and keeps blinking `P0.05`

## Important
This changes UICR persistently. After flashing and seeing `setRegout0To3V3() = OK`, power-cycle the board and re-measure `VDD`.

## Build
```bash
pio run -v
```

## Serial
Open `/dev/ttyACM0` at 115200.

## After programming
1. Unplug power
2. Power the board again
3. Measure E73 `VDD`
4. Retry the radio firmware once `VDD` is near 3.3V
