#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Pin definitions for matrix keyboard
#define ROWS 4
#define COLS 4

// Debounce delay in milliseconds
#define DEBOUNCE_DELAY 20

// Key states
static bool current_key_state[ROWS][COLS] = {0};
static bool last_key_state[ROWS][COLS] = {0};
static uint32_t last_debounce_time[ROWS][COLS] = {0};

// Calculator state
float current_number = 0;
float stored_number = 0;
char current_operation = 0;
bool new_number_flag = true;

// Key mapping for 4x4 matrix
const char keymap[ROWS][COLS] = {
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'C', '0', '=', '/'}
};

// Function prototypes
void setup(void);
void scan_keys(void);
void process_key(char key);
float perform_calculation(void);
void clear_calculator(void);

int main(void) {
    setup();
    
    while(1) {
        scan_keys();
        // Add any additional main loop processing here
    }
    
    return 0;
}

void setup(void) {
    // Initialize GPIO pins for matrix keyboard
    // This will need to be implemented according to your specific microcontroller
    printf("Calculator Initialized\n");
}

void scan_keys(void) {
    uint32_t current_time = 0; // Replace with actual timer function
    
    for(int row = 0; row < ROWS; row++) {
        for(int col = 0; col < COLS; col++) {
            bool current_state = false; // Replace with actual pin reading
            
            if(current_state != last_key_state[row][col]) {
                last_debounce_time[row][col] = current_time;
            }
            
            if((current_time - last_debounce_time[row][col]) > DEBOUNCE_DELAY) {
                if(current_state != current_key_state[row][col]) {
                    current_key_state[row][col] = current_state;
                    
                    if(current_state) { // Key press detected
                        process_key(keymap[row][col]);
                    }
                }
            }
            
            last_key_state[row][col] = current_state;
        }
    }
}

void process_key(char key) {
    if(key >= '0' && key <= '9') {
        if(new_number_flag) {
            current_number = (float)(key - '0');
            new_number_flag = false;
        } else {
            current_number = current_number * 10 + (key - '0');
        }
        printf("Current number: %f\n", current_number);
    } else {
        switch(key) {
            case 'C':
                clear_calculator();
                break;
            case '=':
                current_number = perform_calculation();
                printf("Result: %f\n", current_number);
                new_number_flag = true;
                current_operation = 0;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                if(current_operation) {
                    stored_number = perform_calculation();
                } else {
                    stored_number = current_number;
                }
                current_operation = key;
                new_number_flag = true;
                break;
        }
    }
}

float perform_calculation(void) {
    float result = stored_number;
    
    switch(current_operation) {
        case '+':
            result += current_number;
            break;
        case '-':
            result -= current_number;
            break;
        case '*':
            result *= current_number;
            break;
        case '/':
            if(current_number != 0) {
                result /= current_number;
            } else {
                printf("Error: Division by zero\n");
                clear_calculator();
            }
            break;
    }
    
    return result;
}

void clear_calculator(void) {
    current_number = 0;
    stored_number = 0;
    current_operation = 0;
    new_number_flag = true;
    printf("Calculator cleared\n");
}