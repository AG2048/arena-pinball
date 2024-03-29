# I2C design

## States:
We let the master microcontroller to memorize the states, and tell the slave boards what their state is. The boards themselves process this state information.
- Power On
- Idle
- Game Initialize
- Game Process (ball in field, no score yet)
- Scoring
- Ball retrieval in process
- Game Over (Left wins)
- Game Over (Right wins)
- Game Over (No winner)
- Error State (When a microcontroller did not respond or the ball is lost)

## Devices:
- Camera
- Ball Dispenser
- Sensors (IR Ball Detection)
- Controller Board (Controlling automatic / player control obstacles)
- Floor Lights
- Wall Lights
- Player Controls (Joystick, Buttons, etc)

## Communication:
Input: The device send a message to the CPU

Output: The CPU sends a message to the device

### Camera
- Input: `Ball Detected` + `Ball Position`

### Ball Dispenser
- Output: `Dispense Ball`

### Sensors (IR Ball Detection)
- Input: `Ball Detected` (goal detection & ball retrieval confirmation)

### Controller Board (Controlling automatic / player control obstacles)
- Output: `Current Game State` / `Buttons pressed` / `Relevant Sensor Info`

### Scoreboard
- Output: `State`
- Output: `Scores`

### Floor Lights
- Output: `Floor Light State`
- Output: `Obstacle ID` + `Obstacle State`
- Output: `Ball Detected` + `Ball Position`
- Output: `Score event` + `Score`

### Wall Lights
- Output: `Wall Light State`
- Output: `Current Game Score`

### Player Controls (Joystick, Buttons, etc)
SPECIAL NOTE: THIS IS HARD WIRED TO THE I2C MASTER - SO NO I2C NEEDED HERE
- Input: `Player Control Input`
- Output: `Controller Light State`

## Expected Input
Format: 

Board - Input to Master/Output from Master - byte number: purpose

The CPU should only "keep track" of states, and send the states to all output devices.

### Obstacles
- 0: state
- 1-3: x-coordinate (expecting integer less then 2048)
- 4-6: y-coordinate (expecting integer less than 2048)
