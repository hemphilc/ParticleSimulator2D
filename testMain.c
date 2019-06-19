#include <assert.h>

#include "ParticleSimulator.h"

int main(void)
{
    printf("\nParticle Simulator 2D Unit Tests\n\n");
	
	printf("#################### TEST 1 #######################\n\n");
	
	ParticleSimulator ps1;
	unsigned int w1 = 7;
	unsigned int h1 = 4;
	
	initParticleSimulator(&ps1, w1, h1);
	
	assert(ps1.width == 7);
	assert(ps1.height == 4);
	assert(ps1.grid != NULL);
	
	printf("TEST 1 PASS\n\n");
	
	printf("#################### TEST 2 #######################\n\n");
	
	ParticleSimulator ps2;
	unsigned int w2 = -1;
	unsigned int h2 = -1;
	
	initParticleSimulator(&ps2, w2, h2);
	
	assert(ps2.width == 0);
	assert(ps2.height == 0);
	assert(ps2.grid == NULL);
	
	printf("TEST 2 PASS\n\n");
		
	printf("#################### TEST 3 #######################\n\n");
	
	
	
	
	
	printf("TEST 3 PASS\n\n");
	
	printf("#################### TEST 4 #######################\n\n");
	
	
	printf("TEST 4 PASS\n\n");

    return 0;
}
