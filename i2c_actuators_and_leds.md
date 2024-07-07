# Data format for sending information to actuators and LEDs
## Guiding Principles
1. I2C is fast, an 11 bytes information transfer (from the camera PI to Arduino) only take about 2 ms.
2. Processing should not cause significant delays.

Therefore, we can allow slightly more processing on the master microcontroller. 

## What will the master do
The master will now be processing information, instead of simply relaying messages.

Based on the ball position received from the Raspberry Pi and the controls received from button presses, the master will decide what actuators should be turned on and what LEDs should be in what state (taking into consideration of the game state). The master then tells each devices what it should be doing, every cycle.

## What will the master send
Considering that the I2C protocol is quite fast, and that we only have <20 solenoids and moving devices, we will do the following:

INDEX|INFO
-----|----
0|GAME STATE
1|LED / SOLENOID 1 STATUS (STATE)
2|LED / SOLENOID 2 STATUS (STATE)
3|...

Each information can be a single byte, or can have multiple information merged into 1 byte if they are short.

## What will the slave do
When receiving the information, it should parse the game state and each Solenoid or LED's state. 

### Solenoid
Solenoid will just be a flip on or flip off operation (1 or 0). 

We have 2 types of solenoids: Flippers and Bumpers

#### Flippers
User controlled, we designed it to be "edge sensitive" -- it only turn on at the "pressing edge" of the button and turns off shortly after (say, 250 ms). 

So the master will send a "flipper on" message every "pressing edge" of the button press, and the flippers controller will do the following:

- If the flipper is already on (timer is not 0), don't do anything
- If the flipper is off, start a 250 ms timer
- If the timer reached zero, turn off.

#### Bumpers
Computer controlled obstacles, it will do the same thing as the flippers. Only this case, the master wouldn't be that worried about only sending info on the "rising edge", it just keeps sending. 

### LED
LED will light up based on the state it received.

Each LED will be represented in slave code as an enum.

Make an array, using the LED enum as index, that stores the LED's start index and end index so a function can easily control the LEDs. (Example: start[i] and end[i] and lighting_states[i] and states[i], we make the LED strip between index start[i] and end[i] change based on lighting_states[i] and states[i], here states[i] is the general instruction, and lighting_states[i] records specific light of each LED)

Each LED state will be coded as an enum.

#### LED STATES
States can include: solid colour (R, G, B, ...), OFF, Flashing, Progress bar...