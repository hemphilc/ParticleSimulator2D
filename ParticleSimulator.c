#include <stdio.h>


struct ParticleSimulatorGrid {
    int rows;
    int columns;
    char** grid;
};

int main(void)
{
    char* inputLine = NULL;

    // Retrieve the first line from STDIN
    // This should be two integers, separated by a space.
    // These values specify the number of cells in a
	// given simulation (width and height).
//    if(!(getline(&inputLine, &size, stdin))) {
//        return 0;
//    }

    fgets(inputLine, 32, stdin);





    printf("input: %s", inputLine);

    return 0;
}

