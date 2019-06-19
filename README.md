# Particle Simulator 2D

Simulates how little rocks would fall in a 2D world. 

**Instructions for compiling and executing Particle Simulator 2D**

**NOTE: This program was developed using gcc compiler on an Linux Ubuntu machine. The Makefile provided will compile the program correctly using the gcc compiler. MinGW for Windows may also work as long as the dependencies for using Makefile are installed.**

1: Place ParticleSimulator.c, ParticleSimulator.h, main.c, testMain.c, and Makefile into your current working directory.

2: To compile both the Particle Simulator and the unit tests, enter 'make' into the command line. You should now see two binary executables in your working directory: ParticleSimulator and TestParticleSimulator

3: Execute ParticleSimulator with the following command and follow the prompts for user input: ./ParticleSimulator 

4: Execute TestParticleSimulator unit tests with the following command: ./TestParticleSimulator

5: Entering the following will clean the directory: make clean


**Testing**

Testing the program involves unit tests, as well as some manual testing to test input from stdin and the validation of that input.

The unit test suite, TestParticleSimulator, tests a number of different functions individually, however, it does not test any of the three functions that involve retrieving input from stdin. TestParticleSimulator covers the following:
  - initParticleSimulator()
  - printParticleSimulatorState()
  - initParticleSimulatorGravity()
  - freeParticleSimulatorGrid()
  - printError()

For the manual testing, test input validation by providing different inputs. Invalid inputs will provide error messages to the user regarding what was wrong with the input.

For example, the first prompt requires the user to provide two integer values with a space between them for a given range. The current default RANGE_HIGH is set to 20 and can be easily changed if necessary. If the user provides "4 21" as input, they will receive an input error and the program will die due to input out of range. Furthermore, the input can only be integers for the initial input, so providing "x 12" will also provide an error and cause the program to die.

The main concern of manual testing should be the following:
  - format validation - is the input provided in the correct format (i.e. with a space between two integers)?
  - range validation - do the values provided fall into the specified range (i.e. 1 <= n <= 20)? 
  - input type validation - is the input provided the correct type (i.e. integer or character)?
  - character validation - are the input characters valid (i.e. a ' ', '.', ':', or 'T')?
  - string length validation - are the input strings provided for each grid row too short or too long?
  - are error messages relevant and do they prompt the user to provide the correct input?

The combination of manual testing for stdin input and unit-tests should be comprehensive enough to validate the program's accuracy and functionality.
