#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define OK       	0
#define NO_INPUT 	1
#define TOO_LONG 	2
#define DIM_LEN    	10
#define RANGE_LOW	1
#define RANGE_HIGH 	20


// Define Boolean operators
typedef int bool;
enum {
	false,
	true
};


typedef struct {
    unsigned int width;
    unsigned int height;
    char** grid;
} ParticleSimulator;


int getLine(char *prompt, char *buffer, size_t sz, bool isSimRow);
ParticleSimulator initParticleSimulator(unsigned int w, unsigned int h);
void getGridDimensionInput(int *width, int *height);
void getGridRowInputs(ParticleSimulator *ps);
void initParticleSimulatorGravity(ParticleSimulator *ps);
void printParticleSimulatorState(const ParticleSimulator ps);
void freeParticleSimulatorGrid(ParticleSimulator *ps);


int main(void)
{
	printf("\nWelcome to Particle Simulator 2D!\n\n");
	
	unsigned int width, height;
	
	// Retrieve the first line from STDIN
    // This should be two integers, separated by a space.
    // These values specify the number of cells in a
	// given simulation (width and height).
	getGridDimensionInput(&width, &height);
	
	// Initialize the Particle Simulator struct using the 
	// width and height obtained from the user.
	ParticleSimulator ps = initParticleSimulator(width, height);
	
	// Retrieve Particle Simulator grid row inputs from 
	// the user and validate the row length and characters.
	getGridRowInputs(&ps);
	
	// Print initial grid state.
	printf("\nPrinting initial state...\n\n");
	printParticleSimulatorState(ps);

	// Initiate gravity on grid.
	//initParticleSimulatorGravity(&ps);

	// Print post-gravity grid state.
	printf("\nPrinting post-gravity state...\n\n");
	printParticleSimulatorState(ps);

	// Free the ParticleSimulator struct resources.
	freeParticleSimulatorGrid(&ps);

    return 0;
}


/* Initializes a ParticleSimulator struct using width and height.
    param:  ps - a pointer to a ParticleSimulator struct
    pre:    ParticleSimulator grid is initialized.
    post:   ParticleSimulator grid is printed to stdout in its 
				current state.
    ret:    none.
*/
void initParticleSimulatorGravity(ParticleSimulator *ps) {
	if(!ps) {
		fprintf(stderr, "ParticleSimulator pointer is null.\n");
		return;
	}
	
	
}


/* Prints a ParticleSimulator grid in its current state to stdout.
    param:  ps - a ParticleSimulator struct
    pre:    ParticleSimulator grid is initialized.
    post:   ParticleSimulator grid is printed to stdout in its 
				current state.
    ret:    none.
*/
void printParticleSimulatorState(ParticleSimulator ps) {
	if(!ps.grid) {
		fprintf(stderr, "ParticleSimulator grid pointer is null.\n");
		return;
	}
	
	unsigned int i;
	for(i = 0; i < ps.height; i++) {
		printf("%s\n", ps.grid[i]);
	}
	printf("\n");
}


/* Initializes a ParticleSimulator struct using width and height.
    param:  width - the width of each row in the ParticleSimulator
				grid.
    param:  height - the height of each column in the ParticleSimulator
				grid.
    pre:    ParticleSimulator is uninitialized and grid owns no memory.
    post:   ParticleSimulator members are initialized and grid is 
				malloced accordingly by width and height.
    ret:    an initialized ParticleSimulator grid.
*/
ParticleSimulator initParticleSimulator(unsigned int w, unsigned int h) {
	ParticleSimulator ps;
	ps.width = w;
	ps.height = h;
	
	ps.grid = malloc(ps.height * sizeof(char*));
	
	// Ensure memory allocation didn't fail
	if(!ps.grid) {
		fprintf(stderr, "Memory allocation failed.\n");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	
	// Allocate space for each row in the grid
	unsigned int i;
	for(i = 0; i < ps.height; i++) {
		// + 1 is for the null terminator
		ps.grid[i] = malloc((ps.width + 1) * sizeof(char));
		
		// Ensure memory allocation didn't fail
		if(!ps.grid[i]) {
			fprintf(stderr, "Memory allocation failed.\n");
			fflush(stderr);
			exit(EXIT_FAILURE);
		}
	}
	
	return ps;
}


/* Free all allocated memory in a ParticleSimulator struct.
    param:  ps - a pointer to a ParticleSimulator struct.
    pre:    ParticleSimulator grid has memory allocated.
    post:   ParticleSimulator grid memory is freed.
    ret:    none
*/
void freeParticleSimulatorGrid(ParticleSimulator *ps) {
	if(!ps) {
		fprintf(stderr, "ParticleSimulator pointer is null.\n");
		return;
	}
	
	if(!ps->grid) {
		fprintf(stderr, "ParticleSimulator grid pointer is null.\n");
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
    ret:    ParticleSimulator struct with initialized grid by reference.
*/
void getGridRowInputs(ParticleSimulator *ps) {
	if(!ps) {
		fprintf(stderr, "ParticleSimulator pointer is null.\n");
		return;
	}
	
	if(!ps->grid) {
		fprintf(stderr, "ParticleSimulator grid pointer is null.\n");
		return;
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
		printf("Please provide a row of length %d consisting of ' ', '.', ':', and 'T' characters.\n", ps->width);
		returnVal = getLine("> ", buffer, sizeof(buffer), true);
		
		if(returnVal == NO_INPUT) {
			fprintf(stderr, "No input provided.\n");
			fflush(stderr);
			freeParticleSimulatorGrid(ps);
			exit(EXIT_FAILURE);
		}
		else if(returnVal == TOO_LONG) {
			fprintf(stderr, "Input provided was too long [%s]\n", buffer);
			fflush(stderr);
			freeParticleSimulatorGrid(ps);
			exit(EXIT_FAILURE);
		}
		
		// May be redundant to check length of buffer
		if(strlen(buffer) != ps->width) {
			fprintf(stderr, "Input provided was too long [%s]\n", buffer);
			fflush(stderr);
			freeParticleSimulatorGrid(ps);
			exit(EXIT_FAILURE);
		}

		// Validate characters for each input string
		for(j = 0; j < strlen(buffer); j++) {
			char ch = buffer[j];
			if(ch != '.' && ch != ':' && ch != 'T' && ch != ' ') {
				fprintf(stderr, "Input contains invalid characters [%s]\n", buffer);
				fflush(stderr);
				freeParticleSimulatorGrid(ps);
				exit(EXIT_FAILURE);
			}
		}
		
		// Copy the contents of the row buffer into the
		// ParticleSimulator grid
		if(!ps->grid[i]) {
			fprintf(stderr, "ParticleSimulator grid pointer is null.\n");
			return;
		}
		else {
			strncpy(ps->grid[i], buffer, sizeof(buffer));
		}
	}
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
    ret:    width and height by reference.
*/
void getGridDimensionInput(int *width, int *height) {
	int returnVal;
	char buffer[DIM_LEN];
	
	// Prompt the user for the initial dimensional input for the grid
	printf("Please enter two integers, which represent width and height, separated by a single space.\n");
	printf("The range of these integer values must be from %d to %d separated by a single space.\n", RANGE_LOW, RANGE_HIGH);
	returnVal = getLine("> ", buffer, sizeof(buffer), false);
	
	if(returnVal == NO_INPUT) {
		fprintf(stderr, "No input provided.\n");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	else if(returnVal == TOO_LONG) {
		fprintf(stderr, "Input provided was too long [%s]\n", buffer);
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	
	// Use sscanf on the input buffer to validate the input
	if(sscanf(buffer, "%d %d", width, height) != 2) {
		fprintf(stderr, "Input provided is invalid [%s]\n", buffer);
		fflush(stderr);
		exit(EXIT_FAILURE);
	}

	// Validate the width value
	if(*width < RANGE_LOW || *width > RANGE_HIGH) {
		fprintf(stderr, "Width is out of range [%d]\n", *width);
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	
	// Validate the height value
	if(*height < RANGE_LOW || *height > RANGE_HIGH) {
		fprintf(stderr, "Height is out of range [%d]\n", *height);
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
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
    ret:    an integer indicating 0 for OK, 1 for no input
			or 2 for an over-exceeded buffer length.
*/
int getLine(char *prompt, char *buffer, size_t sz, bool isSimRow) {
    int ch, overRun;

    if(prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }
	
	// Clear the input buffer
	memset(buffer, '\0', sizeof(buffer));
	
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

    // Check for a newline (\n) character.
	// If the input was too long, there will be no newline. 
	// In that case, flush to end of line so that excess 
	// doesn't affect the next call.
    if(buffer[strlen(buffer) - 1] != '\n') {
        overRun = 0;
        while(((ch = getchar()) != '\n') && (ch != EOF)) {
            overRun = 1;
		}
        return (overRun == 1) ? TOO_LONG : OK;
    }

	// Otherwise strip newline and give string back to 
	// caller with null termination.
	if(!isSimRow) {
		// If the input specifies width/height dimensions,
		// then it may be variable in length so we use
		// strlen to determine the length of the input
		buffer[strlen(buffer) - 1] = '\0';
	}
	else {
		// If the input specifies a row in the grid, the
		// the length of the row is fixed. The length of the
		// string will always be 1 less than the actual
		// size of the buffer, so always null terminate at
		// the end of the buffer to avoid eliminating the 
		// last character in the row.
		buffer[sizeof(buffer) - 1] = '\0';
	}
	
    return OK;
}