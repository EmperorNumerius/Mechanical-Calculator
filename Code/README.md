# Calculator Firmware

This firmware implements a basic calculator using a 4x4 matrix keyboard with Cherry MX switches.

## Features

- 4x4 matrix keyboard support
- Debouncing for reliable key input
- Basic arithmetic operations (+, -, *, /)
- Clear function (C key)
- Decimal number support
- Error handling for division by zero

## Implementation Details

### Hardware Requirements

- Microcontroller with at least 8 GPIO pins (4 rows + 4 columns)
- 4x4 matrix of Cherry MX switches
- Pull-up or pull-down resistors for the matrix

### Key Matrix Layout

```
1 2 3 +
4 5 6 -
7 8 9 *
C 0 = /
```

### Debouncing

The firmware implements software debouncing with a 20ms delay to ensure reliable key detection and prevent false triggers.

### Calculator Logic

- Numbers can be entered sequentially to form multi-digit values
- Operations are performed when a new operator is pressed or when equals is pressed
- Division by zero is handled gracefully with an error message
- Clear button (C) resets all calculator states

## Customization

To adapt this firmware for your specific microcontroller:

1. Implement the GPIO initialization in the `setup()` function
2. Add proper pin reading logic in the `scan_keys()` function
3. Implement an actual timer function for debouncing
4. Modify the output methods according to your display system

## Building

Compile the firmware using your microcontroller's toolchain. Ensure all GPIO and timer dependencies are properly configured for your specific hardware.