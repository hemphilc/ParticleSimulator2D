#include "ParticleSimulator.h"

int main(void)
{
    printf("\nWelcome to Particle Simulator 2D!\n\n");

    unsigned int width, height;

    // Retrieve the first line from STDIN
    // This should be two integers, separated by a space.
    // These values specify the number of cells in a
    // given simulation (width and height).
    if(getGridDimensionInput(&width, &height) == ERROR) {
        return EXIT_FAILURE;
    }

    // Initialize the Particle Simulator struct using the
    // width and height obtained from the user.
    ParticleSimulator ps;
    if(initParticleSimulator(&ps, width, height) == ERROR) {
        freeParticleSimulatorGrid(&ps);
        return EXIT_FAILURE;
    }

    // Retrieve Particle Simulator grid row inputs from
    // the user and validate the row length and characters.
    if(getGridRowInputs(&ps) == ERROR) {
        freeParticleSimulatorGrid(&ps);
        return EXIT_FAILURE;
    }

    // Print initial grid state.
    printf("\nPrinting initial state...\n\n");
    if(printParticleSimulatorState(ps) == ERROR) {
        freeParticleSimulatorGrid(&ps);
        return EXIT_FAILURE;
    }

    // Initiate gravity on grid.
    if(initParticleSimulatorGravity(&ps) == ERROR) {
        freeParticleSimulatorGrid(&ps);
        return EXIT_FAILURE;
    }

    // Print post-gravity grid state.
    printf("\nPrinting post-gravity state...\n\n");
    if(printParticleSimulatorState(ps) == ERROR) {
        freeParticleSimulatorGrid(&ps);
        return EXIT_FAILURE;
    }

    // Free the ParticleSimulator struct resources.
    freeParticleSimulatorGrid(&ps);

    return 0;
}
