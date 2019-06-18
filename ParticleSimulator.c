#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_OK      0
#define NO_INPUT 	  1
#define TOO_LONG 	  2
#define DIM_BUFF_LEN  10
#define RANGE_LOW	  1
#define RANGE_HIGH 	  20
#define SUCCESS		  0
#define ERROR		  -1

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


/* Initiates gravity on particles in current grid state
    param:  ps - a pointer to a ParticleSimulator struct
    pre:    ParticleSimulator grid is initialized.
    post:   ParticleSimulator grid is transformed by
                gravity.
    ret:    0 if success, -1 if error.
*/
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
                    // then increment j to 1 cell above the table
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
                    // then increment j to 1 cell above the table
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

            //printParticleSimulatorState(*ps);
        }
    }

    return SUCCESS;
}


/* Prints a ParticleSimulator grid in its current state to stdout.
    param:  ps - a ParticleSimulator struct.
    pre:    ParticleSimulator grid is initialized.
    post:   ParticleSimulator grid is printed to stdout in its
                current state.
    ret:    0 if success, -1 if error.
*/
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


/* Free all allocated memory in a ParticleSimulator struct.
    param:  ps - a pointer to a ParticleSimulator struct.
    pre:    ParticleSimulator grid has memory allocated.
    post:   ParticleSimulator grid memory is freed.
    ret:    none
*/
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


/* Retrieves Particle Simulator grid row inputs from user and
        validates the row inputs for length and character validity.
    param:  ps - a pointer to a ParticleSimulator struct
    pre:    ParticleSimulator width and height values are set and grid
                memory has been allocated.
    post:   ParticleSimulator grid is initialized to initial state.
    ret:    ParticleSimulator struct with initialized grid by reference
                and 0 if success, -1 if error.
*/
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
        // to make sure its not too short
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


/* Custom error printing function
    param:  msg - error message to print to stderr.
    pre:    none.
    post:   error message is printed to stderr.
    ret:    none.
*/
void printError(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    fflush(stderr);
}
