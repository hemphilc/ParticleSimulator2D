#include "ParticleSimulator.h"


int initParticleSimulatorGravity(ParticleSimulator *ps) {
    if(!ps) {
        printError("initParticleSimulatorGravity() - Error: ParticleSimulator pointer is null.\n");
        return ERROR;
    }

    if(!ps->grid) {
        printError("initParticleSimulatorGravity() - Error: ParticleSimulator grid pointer is null.\n");
        return ERROR;
    }

    unsigned int i;
    int j, k; // Since j and k count downward, allow them to go below 0
    // For each column in the grid starting from the left
    for(i = 0; i < ps->width; i++) {

        // For each cell in the column starting from the
        // bottom and working upward by row
        j = ps->height - 1;
        while(j > 0) {
            // If the current cell is an empty space (' ')
            if(ps->grid[j][i] == ' ') {

                // Search for the next occupied cell above the current
                for(k = j - 1; k >= 0; k--) {

                    // If next occupied cell above is a table
                    // then decrement j to 1 cell above the table
                    if(ps->grid[k][i] == 'T') {
                        j = k - 1;
                        break;
                    }

                    // If next occupied cell above is 2 rocks
                    // then move the 2 rocks into the empty
                    // space and empty the space in which
                    // they originated
                    else if(ps->grid[k][i] == ':') {
                        ps->grid[k][i] = ' ';
                        ps->grid[j][i] = ':';
                        break;
                    }

                    // If next occupied cell above is 1 rock
                    // then move the 1 rock into the empty
                    // space and empty the space in which
                    // it originated
                    else if(ps->grid[k][i] == '.') {
                        ps->grid[k][i] = ' ';
                        ps->grid[j][i] = '.';
                        break;
                    }

                    // If we've reached 0, we've cycled
                    // through the entire column
                    if(k == 0) { j--; }
                }
            }

            // If the current cell is 1 rock ('.')
            else if(ps->grid[j][i] == '.') {

                // Search for the next occupied cell above the current
                for(k = j - 1; k >= 0; k--) {

                    // If next occupied cell above is a table
                    // then decrement j to 1 cell above the table
                    if(ps->grid[k][i] == 'T') {
                        j = k - 1;
                        break;
                    }

                    // If next occupied cell above is 2 rocks
                    // then merge 1 of the rocks into the 1 rock
                    // space below thus making it 2 rocks and
                    // change the 2 rock we merged from to a 1 rock
                    else if(ps->grid[k][i] == ':') {
                        ps->grid[k][i] = '.';
                        ps->grid[j][i] = ':';
                        break;
                    }

                    // If next occupied cell above is 1 rock
                    // then merge 1 rock into the 1 rock space
                    // thus making it 2 rocks and change the
                    // 1 rock we merged from to an empty space
                    else if(ps->grid[k][i] == '.') {
                        ps->grid[k][i] = ' ';
                        ps->grid[j][i] = ':';
                        break;
                    }

                    // If we've reached 0, we've cycled
                    // through the entire column
                    if(k == 0) { j--; }
                }
            }

            // If the current cell is a 2 rock (':') or a table ('T')
            // nothing can be done to it so move on.
            else if(ps->grid[j][i] == ':' || ps->grid[j][i] == 'T') {
                j--;
            }
        }
    }

    return SUCCESS;
}


int printParticleSimulatorState(ParticleSimulator ps) {
    if(!ps.grid) {
        printError("printParticleSimulatorState() - Error: ParticleSimulator grid pointer is null.\n");
        return ERROR;
    }

    unsigned int i;
    for(i = 0; i < ps.height; i++) {
        printf("%s\n", ps.grid[i]);
    }
    printf("\n");

    return SUCCESS;
}


int initParticleSimulator(ParticleSimulator *ps, unsigned int w, unsigned int h) {
    ps->width = w;
    ps->height = h;
    ps->grid = malloc(ps->height * sizeof(char*));

    // Ensure memory allocation didn't fail
    if(!ps->grid) {
        perror("initParticleSimulator() - malloc Error");
        return ERROR;
    }

    // Allocate space for each row in the grid
    unsigned int i;
    for(i = 0; i < ps->height; i++) {
        // + 1 is for the null terminator
        ps->grid[i] = malloc((ps->width + 1) * sizeof(char));

        // Ensure memory allocation didn't fail
        if(!ps->grid[i]) {
            perror("initParticleSimulator() - malloc Error");
            free(ps->grid); // Free the grid before bailing out
            return ERROR;
        }
    }

    return SUCCESS;
}


void freeParticleSimulatorGrid(ParticleSimulator *ps) {
    if(!ps) {
        printError("freeParticleSimulatorGrid() - Error: ParticleSimulator pointer is null.\n");
        return;
    }

    if(!ps->grid) {
        printError("freeParticleSimulatorGrid() - Error: ParticleSimulator grid pointer is null.\n");
        return;
    }

    unsigned int i;
    for(i = 0; i < ps->height; i++) {
        free(ps->grid[i]); // Free each string pointer
    }
    free(ps->grid); // Free the array of pointers
}


int getGridRowInputs(ParticleSimulator *ps) {
    if(!ps) {
        printError("getGridRowInputs() - Error: ParticleSimulator pointer is null.\n");
        return ERROR;
    }

    if(!ps->grid) {
        printError("getGridRowInputs() - Error: ParticleSimulator grid pointer is null.\n");
        return ERROR;
    }

    int returnVal;
    unsigned int i, j;
    char buffer[ps->width + 1]; // + 1 is for the null terminator

    // Each line of user input describes one row of cells in the simulation.
    // Using the following text representation, each character should be
    // one of the following:
    // 		'.'  - one single rock.
    // 		':'  - two rocks.
    // 		' '  - empty space, into which rocks may fall.
    // 		'T'  - table, through which rocks may not fall.
    for(i = 0; i < ps->height; i++) {
        // Prompt the user for each row in the grid
        printf("Please provide a row of length %d consisting only of ' ', '.', ':', and 'T' characters.\n", ps->width);
        returnVal = getLine("> ", buffer, sizeof(buffer));

        if(returnVal == NO_INPUT) {
            printError("Error: No input provided.\n");
            return ERROR;
        }
        else if(returnVal == TOO_LONG) {
            printError("Error: Input provided was too long.\n");
            return ERROR;
        }

        // We know the input is not too long, so if the input is not
        // equal to the specified width, then it is too short.
        if(strlen(buffer) != ps->width) {
            printError("Error: Input provided was too short.\n");
            return ERROR;
        }

        // Validate characters for each input string
        for(j = 0; j < strlen(buffer); j++) {
            char ch = buffer[j];
            if(ch != '.' && ch != ':' && ch != 'T' && ch != ' ') {
                printError("Error: Input contains invalid characters.\n");
                return ERROR;
            }
        }

        // Copy the contents of the row buffer into the
        // ParticleSimulator grid
        if(!ps->grid[i]) {
            printError("getGridRowInputs() - Error: ParticleSimulator grid row pointer is null.\n");
            return ERROR;
        }
        else {
            strncpy(ps->grid[i], buffer, sizeof(buffer));
        }
    }

    return SUCCESS;
}


int getGridDimensionInput(unsigned int *width, unsigned int *height) {
    int returnVal;
    char buffer[DIM_BUFF_LEN];

    // Prompt the user for the initial dimensional input for the grid
    printf("Please enter two integers, which represent width and height, separated by a single space.\n");
    printf("The range of these integer values must be from %d to %d.\n", RANGE_LOW, RANGE_HIGH);
    returnVal = getLine("> ", buffer, sizeof(buffer));

    // Check to see if user provide empty string
    if(returnVal == NO_INPUT) {
        printError("Error: No input provided.\n");
        return ERROR;
    }
    // Check to see if the string the user provided is too long
    else if(returnVal == TOO_LONG) {
        printError("Error: Input provided was too long.\n");
        return ERROR;
    }

    // Use sscanf on the input buffer to validate the input
    if(sscanf(buffer, "%d %d", width, height) != 2) {
        printError("Error: Input provided is invalid.\n");
        return ERROR;
    }

    // Validate the width value
    if(*width < RANGE_LOW || *width > RANGE_HIGH) {
        printError("Error: Width is out of specified range.\n");
        return ERROR;
    }

    // Validate the height value
    if(*height < RANGE_LOW || *height > RANGE_HIGH) {
        printError("Error: Height is out of specified range.\n");
        return ERROR;
    }

    return SUCCESS;
}


int getLine(const char *prompt, char *buffer, size_t sz) {
    int ch, overRun;

    // Prompt user for input from stdin
    if(prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }

    // Clear the input buffer
    memset(buffer, '\0', sz);

    // Get user input and if NULL is returned,
    // then no input was retrieved
    if(fgets(buffer, sz, stdin) == NULL) {
        return NO_INPUT;
    }

    // If the buffer only contains a newline
    // character, then no input was retrieved
    if(strcmp(buffer, "\n") == 0) {
        return NO_INPUT;
    }

    // Check for a newline character.
    // If the input was too long, there will be no newline.
    // In that case, flush to end of line so that excess
    // doesn't affect the next call.
    if(buffer[strlen(buffer) - 1] != '\n') {
        overRun = 0;
        while(((ch = getchar()) != '\n') && (ch != EOF)) {
            overRun = 1;
        }
        return (overRun == 1) ? TOO_LONG : INPUT_OK;
    }

    // Otherwise strip newline and give string back to
    // caller with null termination.
    buffer[strlen(buffer) - 1] = '\0';

    return INPUT_OK;
}


void printError(const char *msg) {
	if(msg != NULL)
		fprintf(stderr, "%s\n", msg);
		fflush(stderr);
	}
}
