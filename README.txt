# Particle Simulator 2D

Simulates how little rocks would fall in a 2D world. 

**NOTE: This program was developed using gcc compiler on an Linux Ubuntu machine. 
The Makefile provided will compile the program correctly using the gcc compiler. 
MinGW for Windows may also work as long as the dependencies for using Makefile are 
installed.**

**NOTE: The current program is set to allow a width and height from 1 to 20. This 
can be changed by going into the ParticleSimulator.h file and adjusting the 
RANGE_LOW and RANGE_HIGH constant definitions. In addition to adjusting RANGE_LOW 
and RANGE_HIGH, you may be required to adjust the DIM_BUFF_LEN constant as well. 
DIM_BUFF_LEN depends on how many digits RANGE_HIGH contains. For example, if 
RANGE_HIGH is 20, then the buffer should be able to hold 2 digits + space + 2 digits
+ null terminator = 6. Another example, if RANGE_HIGH is 2000, then the buffer 
should be able to hold 4 digits + space + 4 digits + null terminator = 10. Failing 
to follow this convention will cause undefined behaviour or outright failure.**


**Instructions for compiling and executing Particle Simulator 2D**

1: Place ParticleSimulator.c, ParticleSimulator.h, main.c, testMain.c, and Makefile 
into your current working directory.

2: To compile both the Particle Simulator and the unit tests, enter 'make' into the 
command line. You should now see two binary executables in your working directory: 
ParticleSimulator and TestParticleSimulator

3: Execute ParticleSimulator with the following command and follow the prompts for 
user input: ./ParticleSimulator 

4: Execute TestParticleSimulator unit tests with the following command: 
./TestParticleSimulator

5: Entering the following will clean the directory: make clean


**Testing**

Testing the program involves unit tests, as well as some manual testing to test input 
from stdin and the validation of that input.

The unit test suite, TestParticleSimulator, tests a number of different functions 
individually, however, it does not test any of the three functions that involve 
retrieving input from stdin. TestParticleSimulator covers the following:

  - initParticleSimulator()
  - printParticleSimulatorState()
  - initParticleSimulatorGravity()
  - freeParticleSimulatorGrid()
  - printError()

For the manual testing, test input validation by providing different inputs. Invalid 
inputs will provide error messages to the user regarding what was wrong with the input.

For example, the first prompt requires the user to provide two integer values with a 
space between them for a given range. The current default RANGE_HIGH is set to 20 and 
can be easily changed if necessary. If the user provides "4 21" as input, they will 
receive an input error and the program will die due to input out of range. Furthermore, 
the input can only be integers for the initial input, so providing "x 12" will also 
provide an error and cause the program to die.

The main concern of manual testing should be the following:
  - format validation - is the input provided in the correct format (i.e. with a space 
    between two integers)?
  - range validation - do the values provided fall into the specified range (i.e. 
    1 <= n <= 20)? 
  - input type validation - is the input provided the correct type (i.e. integer or 
    character)?
  - character validation - are the input characters valid (i.e. a ' ', '.', ':', or 'T')?
  - string length validation - are the input strings provided for each grid row too 
    short or too long?
  - are error messages relevant and do they prompt the user to provide the correct input?


**Test Plan**

1: Compile and execute TestParticleSimulator unit tests.
  - Pass: all tests complete successfully
  - Fail: assertion causes unit tests to die
  
2: Compile and execute ParticleSimulator. The program will prompt for two integers, which 
represent width and height, separated by a single space. The range of these integer values 
must be from 1 to 20 by default (unless changed in the source - see notes above). Test this 
by entering in different inputs.

  - Pass: 7 4
  - Pass: 1 20
  - Fail: x 20
  - Fail: 3 xjf
  - Fail: 1 21
  - Fail: 0 11
 
 3: Compile and execute ParticleSimulator. Provide valid input for the first prompt. For the 
 next prompt(s), the program will ask the user to provide a row of length x consisting only 
 of ' ', '.', ':', and 'T' characters. For example, if the user provided 7 4 as the 
 dimensional input, then x would be 7 and they will be prompted to provide 4 rows of strings 
 with length 7. Test this by entering in different inputs. The example inputs below assume 
 width: 7 and height: 4.
 
  - Pass:  .....::
           .T    :
             .T .:
             .   .
  - Fail:  .....::
           .T    :
             .T .:
           x  . x.
  - Fail:  .....:::::::
  - Fail:  .x...g:
  - Fail:  ...
  - Fail:  ...::.:
           .2x T
  
  
The combination of manual testing for stdin input and unit-tests should be comprehensive 
enough to validate the program's accuracy and functionality.
