#include <assert.h>

#include "ParticleSimulator.h"

int main(void)
{
	unsigned int i;

	printf("\nParticle Simulator 2D Unit Tests\n\n");

	printf("######## Test initParticleSimulator() ########\n\n");

	ParticleSimulator ps1;
	unsigned int w1 = 7;
	unsigned int h1 = 4;

	assert(initParticleSimulator(&ps1, w1, h1) == 0);
	printf("TEST 1 PASS\n\n");

	assert(ps1.width == 7);
	printf("TEST 2 PASS\n\n");

	assert(ps1.height == 4);
	printf("TEST 3 PASS\n\n");

	assert(ps1.grid != NULL);
	printf("TEST 4 PASS\n\n");

	freeParticleSimulatorGrid(&ps1);

	ParticleSimulator ps2;
	unsigned int w2 = 0;
	unsigned int h2 = 0;

	assert(initParticleSimulator(&ps2, w2, h2) == -1);
	printf("TEST 5 PASS\n\n");

	w2 = 1;
	assert(initParticleSimulator(&ps2, w2, h2) == -1);
	printf("TEST 6 PASS\n\n");

	h2 = 1;
	ParticleSimulator *ps3 = NULL;
	assert(initParticleSimulator(ps3, w2, h2) == -1);
	printf("TEST 7 PASS\n\n");

	printf("##############################################\n\n\n");



	printf("##### Test printParticleSimulatorState() #####\n\n");

	ParticleSimulator ps4;
	unsigned int w4 = 7;
	unsigned int h4 = 4;

	ps4.grid = NULL;
	assert(printParticleSimulatorState(ps4) == -1);
	printf("TEST 1 PASS\n\n");

	assert(initParticleSimulator(&ps4, w4, h4) == 0);

	strcpy(ps4.grid[0], ".....::");
	ps4.grid[0][w4] = '\0';
	strcpy(ps4.grid[1], ".T    :");
	ps4.grid[1][w4] = '\0'; 
	strcpy(ps4.grid[2], "  .T .:");
	ps4.grid[2][w4] = '\0';
	strcpy(ps4.grid[3], "  .   .");   
	ps4.grid[3][w4] = '\0';

	assert(printParticleSimulatorState(ps4) == 0);
	printf("TEST 2 PASS\n\n");

	freeParticleSimulatorGrid(&ps4);

	printf("##############################################\n\n\n");



	printf("##### Test initParticleSimulatorGravity() #####\n\n");

	ParticleSimulator ps5;
	unsigned int w5 = 7;
	unsigned int h5 = 4;

	assert(initParticleSimulator(&ps5, w5, h5) == 0);

	strcpy(ps5.grid[0], ".....::");
	ps5.grid[0][w5] = '\0';
	strcpy(ps5.grid[1], ".T    :");
	ps5.grid[1][w5] = '\0'; 
	strcpy(ps5.grid[2], "  .T .:");
	ps5.grid[2][w5] = '\0';
	strcpy(ps5.grid[3], "  .   .");   
	ps5.grid[3][w5] = '\0';

	ParticleSimulator ps5Test;
	assert(initParticleSimulator(&ps5Test, w5, h5) == 0);

	strcpy(ps5Test.grid[0], " .    .");
	ps5Test.grid[0][w5] = '\0';
	strcpy(ps5Test.grid[1], " T .  :");
	ps5Test.grid[1][w5] = '\0'; 
	strcpy(ps5Test.grid[2], "  .T .:");
	ps5Test.grid[2][w5] = '\0';
	strcpy(ps5Test.grid[3], ": : .::");
	ps5Test.grid[3][w5] = '\0';

	assert(initParticleSimulatorGravity(&ps5) == 0);	
	for(i = 0; i < h5; i++) {
		assert(strcmp(ps5.grid[i], ps5Test.grid[i]) == 0);
	}
	assert(printParticleSimulatorState(ps5) == 0);
	assert(printParticleSimulatorState(ps5Test) == 0);
	printf("TEST 1 PASS\n\n");

	freeParticleSimulatorGrid(&ps5);
	freeParticleSimulatorGrid(&ps5Test);

	ps5.grid = NULL;
	assert(initParticleSimulatorGravity(&ps5) == -1);
	printf("TEST 2 PASS\n\n");

	ParticleSimulator *ps6 = NULL;	
	assert(initParticleSimulatorGravity(ps6) == -1);
	printf("TEST 3 PASS\n\n");

	printf("##############################################\n\n\n");



	printf("##### Test freeParticleSimulatorGrid() #####\n\n");

	ParticleSimulator ps7;
	unsigned int w7 = 12;
	unsigned int h7 = 16;

	assert(initParticleSimulator(&ps7, w7, h7) == 0);
	assert(ps7.grid != NULL);
	freeParticleSimulatorGrid(&ps7);
	assert(ps7.grid == NULL);
	printf("TEST 1 PASS\n\n");

	freeParticleSimulatorGrid(&ps7);
	printf("TEST 2 PASS\n\n");

	ParticleSimulator *ps8 = NULL;
	freeParticleSimulatorGrid(ps8);
	printf("TEST 3 PASS\n\n");

	printf("##############################################\n\n\n");



	printf("End of Unit Tests -- All Tests Passed!\n\n");

    return 0;
}

