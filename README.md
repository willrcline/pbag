# Digital Punching Bag Alarm Clock and Game System Using Arduino Nano
## Contents
### pbag
(Main arduino sketch)
* Alarm software uses system of current_loop variable as gate keeper for various "millis()" loops being pinged within "loop()". Performs "timer_loop" until the time is within a couple seconds of that which the alarm is set for.

### pbag_ios
Mobile application files (sends bluetooth to arduino module)
### Orientation
Contains:
* Processing visualization code
* mpu9250 orientation sensor raw code

### Wiring Diagrams
Self explanatory. Images that will help reproducability of the hardware wiring necessary for the product.
