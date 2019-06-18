#ifndef PARTICLESIMULATOR
#define PARTICLESIMULATOR

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_OK      0
#define NO_INPUT      1
#define TOO_LONG      2
#define DIM_BUFF_LEN  10
#define RANGE_LOW     1
#define RANGE_HIGH    20
#define SUCCESS       0
#define ERROR         -1

typedef struct {
    unsigned int width;
    unsigned int height;
    char** grid;
} ParticleSimulator;

/* Custom get line function with buffer overrun protection.
    param:  prompt - a user input prompt.
    param:  buffer - a buffer for returning user input from stdin.
    param:  sz - the size of the input buffer.
    param:  isSimRow - bool indicator for differentiating the
                initial dimensional input from the individual
                grid row inputs.
    pre:    user input buffer is empty.
    post:   user input retrieved and stored in buffer.
    ret:    an integer indicating 0 for INPUT_OK, 1 for no input
            or 2 for an over-exceeded buffer length.
*/
int getLine(const char *prompt, char *buffer, size_t sz);

/* Initializes a ParticleSimulator struct using width and height.
    param:  ps - a ParticleSimulator struct pointer reference.
    param:  width - the width of each row in the ParticleSimulator
                grid.
    param:  height - the height of each column in the ParticleSimulator
                grid.
    pre:    ParticleSimulator is uninitialized and grid owns no memory.
    post:   ParticleSimulator members are initialized and grid is
                malloced accordingly by width and height.
    ret:    an initialized ParticleSimulator struct by reference, and
                0 if success, -1 if error.
*/
int initParticleSimulator(ParticleSimulator *ps, unsigned int w, unsigned int h);

/* Retrieves Particle Simulator grid dimension inputs from user
        and validates the inputs.
    param:  width - the width of each row in the ParticleSimulator
                grid.
    param:  height - the height of each column in the ParticleSimulator
                grid.
    pre:    None.
    post:   Width and height values are retrieved from stdin and
                validated.
    ret:    width and height by reference and 0 if success, -1 if error.
*/
int getGridDimensionInput(unsigned int *width, unsigned int *height);

/* Retrieves Particle Simulator grid row inputs from user and
        validates the row inputs for length and character validity.
    param:  ps - a pointer to a ParticleSimulator struct
    pre:    ParticleSimulator width and height values are set and grid
                memory has been allocated.
    post:   ParticleSimulator grid is initialized to initial state.
    ret:    ParticleSimulator struct with initialized grid by reference
                and 0 if success, -1 if error.
*/
int getGridRowInputs(ParticleSimulator *ps);

/* Initiates gravity on particles in current grid state
    param:  ps - a pointer to a ParticleSimulator struct
    pre:    ParticleSimulator grid is initialized.
    post:   ParticleSimulator grid is transformed by
                gravity.
    ret:    0 if success, -1 if error.
*/
int initParticleSimulatorGravity(ParticleSimulator *ps);

/* Prints a ParticleSimulator grid in its current state to stdout.
    param:  ps - a ParticleSimulator struct.
    pre:    ParticleSimulator grid is initialized.
    post:   ParticleSimulator grid is printed to stdout in its
                current state.
    ret:    0 if success, -1 if error.
*/
int printParticleSimulatorState(const ParticleSimulator ps

/* Free all allocated memory in a ParticleSimulator struct.
    param:  ps - a pointer to a ParticleSimulator struct.
    pre:    ParticleSimulator grid has memory allocated.
    post:   ParticleSimulator grid memory is freed.
    ret:    none
*/
void freeParticleSimulatorGrid(ParticleSimulator *ps);

/* Custom error printing function
    param:  msg - error message to print to stderr.
    pre:    none.
    post:   error message is printed to stderr.
    ret:    none.
*/
void printError(const char *msg);

#endif
