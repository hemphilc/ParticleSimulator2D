#include <assert.h>

#include "ParticleSimulator.h"

int main(void)
{
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
	
	
	
	printf("##### Test printParticleSimulatorState() #####n\n");
	
	ParticleSimulator ps3;
	unsigned int w3 = 7;
	unsigned int h3 = 4;
	ps3.grid = NULL;
	
	assert(printParticleSimulatorState(ps3) == -1);
	printf("TEST 1 PASS\n\n");
	
	assert(initParticleSimulator(&ps3, w3, h3) == 0);
	
	strcpy(ps3.grid[0], ".....::");
	ps3.grid[0][w3] = '\0';
	strcpy(ps3.grid[1], ".T    :");
	ps3.grid[1][w3] = '\0'; 
	strcpy(ps3.grid[2], "  .T .:");
	ps3.grid[2][w3] = '\0';
	strcpy(ps3.grid[3], "  .   .");   
	ps3.grid[3][w3] = '\0';
	
	assert(printParticleSimulatorState(ps3) == 0);
	
	printf("TEST 2 PASS\n\n");
	
	freeParticleSimulatorGrid(&ps3);
	
	
	
	printf("##### Test printParticleSimulatorState() #####n\n");
	
	ParticleSimulator ps3;
	unsigned int w3 = 7;
	unsigned int h3 = 4;
	ps3.grid = NULL;
	
	
	
	
	
	
	
	
	
	
	
	

	printf("End of Unit Tests -- All Tests Passed!\n\n");

    return 0;
}
