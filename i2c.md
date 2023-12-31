# I2C design

## States:
- Idle
- Game Initialize
- Ball Retrieve
- Game Process
- Scoring
- Game Over

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
- Input: `Obstacle ID` + `Obstacle State`
- Output: `Enable/Disable Automatic Obstacle`
- Output: `Player Controlled Obstacle ID` + `Player Control Input`

### Floor Lights
- Output: `Floor Light State`
- Output: `Obstacle ID` + `Obstacle State`
- Output: `Ball Detected` + `Ball Position`
- Output: `Score event` + `Score`

### Wall Lights
- Output: `Wall Light State`
- Output: `Current Game Score`

### Player Controls (Joystick, Buttons, etc)
- Input: `Player Control Input`
- Output: `Controller Light State`