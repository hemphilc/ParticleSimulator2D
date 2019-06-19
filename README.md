# Particle Simulator 2D

Simulates how little rocks would fall in a 2D world. 

***** Instructions for compiling and executing Particle Simulator 2D *****

**NOTE: This program was developed using gcc compiler on an Linux Ubuntu machine. The Makefile provided will only compile the program correctly using the gcc compiler. MinGW for Windows may also work as long as the dependencies for using Makefile are installed.**

1: Place ParticleSimulator.c, ParticleSimulator.h, main.c, testMain.c, and Makefile into your current working directory.

2: To compile both the Particle Simulator and the unit tests, enter 'make' into the command line. You should now see two binary executables in your working directory: ParticleSimulator and TestParticleSimulator

3: Execute ParticleSimulator with the following command and follow the prompts for user input: ./ParticleSimulator 

4: Execute TestParticleSimulator unit tests with the following command: ./TestParticleSimulator

**_Example Input and Output_**

**Input:**
7 4
.....::
.T    :
  .T .:
  .   .
  
**Output:**
 .    .
 T .  :
  .T .:
: : .::
