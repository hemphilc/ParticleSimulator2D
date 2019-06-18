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

int getLine(const char *prompt, char *buffer, size_t sz);
int initParticleSimulator(ParticleSimulator *ps, unsigned int w, unsigned int h);
int getGridDimensionInput(unsigned int *width, unsigned int *height);
int getGridRowInputs(ParticleSimulator *ps);
int initParticleSimulatorGravity(ParticleSimulator *ps);
int printParticleSimulatorState(const ParticleSimulator ps);
void freeParticleSimulatorGrid(ParticleSimulator *ps);
void printError(const char *msg);

#endif
