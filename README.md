# Sensor Motor
The Sensor Motor reads in temperature and humidity using the HDC1080 device. These values can be display on the 7 Segment Display and manipulate the Stepper Motor. Alternatively, buttons on the Vandalino board can also be used to change 7 Segment Display and Stepper Motor settings. Neopixels on the Vandalino board also reflect the state of the system.

### Installations
- FreeRTOS
- PicoSDK

### Quick Start
FreeRTOS and PicoSDK are used in this project. To build this project on your machine, follow the [Installations](#installations) section.

1. Enter the following commands in your terminal to clone
- over HTTP
```
git clone https://github.com/jennaluz/SensorMotor.git
```

- over SSH
```
git clone git@github.com:jennaluz/SensorMotor.git
```

2. In the prject directory, set the PicoSDK environment variable using the following command
```
export PICO_SDK_PATH=Path/To/PicoSDK
```

3. To build the executable, enter the following commands
```
cmake -B build
cmake --build build
```

4. Flash the executable on the Pico Feather using the following command
```
cp build/SensorMotor.uf2
```

The Sensor Motor program is now running on your Pico Feather! View the [Quick Controls](#quick-controls) section for an overview on how to use the buttons on the Vandalino board to manipulate the system.

### Quick Controls
__Button 1__
- _1 Push_: The Stepper Motor...
  - Moves clockwise when temperature increases.
  - Moves counterclockwise when temperature decreases.
  - Does not move when temperature does not change.
- _2 Pushes_: The Stepper Motor...
  - Moves clockwise when humidity increases.
  - Moves counterclockwise when humidity decreases.
  - Does not move when humidity does not change.
- _3 Pushes_: The 7 Segment Display switches between displaying decimal and hexadecimal.
- _4 Pushes_: The Emergency Stop mechanism is activated. If the Emergency Stop mechanism is already active, it is deactivated.

__Button 2__
- _1 Push_: Continuously moves the Stepper Motor clockwise.
- _2 Pushes_: Continuously moves the Stepper Motor counterclockwise.
- _3 Pushes_: Alternates the Stepper Motor between clockwise and counterclockwise revolutions.

__Button 3__
- _1 Push_: The 7 Segment Display shows the current temperature.
- _2 Pushes_: The 7 Segment Displays shows the current humidity.
- _3 Pushes_: The 7 Segment Display shows the Stepper Motor status...
  - Displays (cc) when moving clockwise.
  - Displays (ↄↄ) when moving counterclockwise.
  - Displays (oo) when not moving.

__NeoPixel__
- _Pixel 1_ (topmost): Reflects temperature. Displays...
  - _Bright red_ when temperature is increasing.
  - _Dim read_ when temperature is decreasing.
- _Pixel 2_: Reflects humidity. Displays...
  - _Bright yellow_ when temperature is increasing.
  - _Dim yellow_ when temperature is decreasing.
- _Pixel 3_: Reflects the status of the 7 Segment Display. Displays...
  - _Red_ when showing the current temperature.
  - _Yellow_ when showing the current humidity.
  - _Purple_ when showing the Stepper Motor status.
- _Pixel 4_ (bottommost): Reflects the status of the Stepper Motor. Displays...
  - _Green_ when moving clockwise.
  - _Yellow_ when moving counterclockwise.
  - _Orange_ when not moving.
  
__Error Messages__
The 7 Segment Display shows error messages. Displays...
- (三三) with _Unknown Input_.
- (OF) when the Display Queue _Overflows_.
- (EE) when the _Emergency Stop_ mechanism is triggered.
