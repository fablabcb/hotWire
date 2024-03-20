# Hot Wire

This is the code for the HotWire tool developed and build at FabLab Cottbus. It's a skill game where you have to trace a
winding path without touching the wire. There are 2 game modes as described below.

## Manual

### Setup

Connect the USB port to a good power source.
There are 2 ports on the back of the case. The left one has to connect to the rod, the right one is for the Y-Cable.

The game starts with the rod at the right. Be sure the rod is not touching the wire when starting. Trace the path all
the way to the left without touching it and then hit the horizontal metal ring. That's when the game ends.

### Display

The LED display is used to show the current runtime as well as the highscore values. Milliseconds are displayed on the
right, seconds on the left. Once over 99s, two dots will appear on the left. The bottom one indicates 100s, the top one
200s.

Please note that, since normaly it is never used in alarm clocks, the top left LED of the leftmost block does NEVER
light up. Here you cannot distinguish between a 9 and a 3. Be careful.

### Buttons

There are 6 buttons on the radio clock:

Big one: Start/Reset the game
Row of 2: Switch to Hardcore mode (left) or Timed Mode (right)
Row of 3: Hold Left and Right to reset session highscore

### Game Modes

The two game modes are Hardcore and Timed. In Hardcore the game is over as soon as you touch the wire even once. In
Timed mode you get a time penalty for each contact you make with the wire. The game is won if you can reach the metal
ring on the other side.

After powering on the clock displays zeros. You are ready to start a game (by pressing start) or change the game mode
when in this state.

### Highscore

The device stores the highscore (lowest time) for each game mode in persistant memory. When you finish a game and break
the current highscore, the melody played will be different. You can reset the highscore of the current game mode only.

This all is primarily used to track the highscore reached in a single event/day and then reset for the next event.

## Hardware

TODO Martin

## Software

The software is written for the Arduiono ESP32 platform. There is a makefile to build and also deploy the project.
There also is 'make testSetup' to see if your setup should work. Linux support only.

To get rid of the annoying password request, go to ~/.arduino15/packages/esp32/hardware/esp32/2.0.11/platform.txt (or
your matching platform) and comment out both lines with "tools.esp_ota.upload.field.password=".
