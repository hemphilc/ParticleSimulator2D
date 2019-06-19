#include <assert.h>

#include "ParticleSimulator.h"

int main(void)
{
    unsigned int i;

    printf("\nParticle Simulator 2D Unit Tests\n\n");

    printf("######## TEST initParticleSimulator() ########\n\n");

    ParticleSimulator ps1;
    unsigned int w1 = 7;
    unsigned int h1 = 4;

    assert(initParticleSimulator(&ps1, w1, h1) == 0);
    printf("TEST 1 PASSED\n\n");

    assert(ps1.width == 7);
    printf("TEST 2 PASSED\n\n");

    assert(ps1.height == 4);
    printf("TEST 3 PASSED\n\n");

    assert(ps1.grid != NULL);
    printf("TEST 4 PASSED\n\n");

    freeParticleSimulatorGrid(&ps1);

    ParticleSimulator ps2;
    unsigned int w2 = 0;
    unsigned int h2 = 0;

    assert(initParticleSimulator(&ps2, w2, h2) == -1);
    printf("TEST 5 PASSED\n\n");

    w2 = 1;
    assert(initParticleSimulator(&ps2, w2, h2) == -1);
    printf("TEST 6 PASSED\n\n");

    h2 = 1;
    ParticleSimulator *ps3 = NULL;
    assert(initParticleSimulator(ps3, w2, h2) == -1);
    printf("TEST 7 PASSED\n\n");

    printf("##############################################\n\n\n");



    printf("##### TEST printParticleSimulatorState() #####\n\n");

    ParticleSimulator ps4;
    unsigned int w4 = 7;
    unsigned int h4 = 4;

    ps4.grid = NULL;
    assert(printParticleSimulatorState(ps4) == -1);
    printf("TEST 1 PASSED\n\n");

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
    printf("TEST 2 PASSED\n\n");

    freeParticleSimulatorGrid(&ps4);

    printf("##############################################\n\n\n");



    printf("##### TEST initParticleSimulatorGravity() #####\n\n");

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
    printf("TEST 1 PASSED\n\n");

    freeParticleSimulatorGrid(&ps5);
    freeParticleSimulatorGrid(&ps5Test);


    ParticleSimulator ps6;
    unsigned int w6 = 15;
    unsigned int h6 = 10;

    assert(initParticleSimulator(&ps6, w6, h6) == 0);

    strcpy(ps6.grid[0], ".........::::::");
    ps6.grid[0][w6] = '\0';
    strcpy(ps6.grid[1], ".T:T.T:T.T:T.T:");
    ps6.grid[1][w6] = '\0';
    strcpy(ps6.grid[2], "               ");
    ps6.grid[2][w6] = '\0';
    strcpy(ps6.grid[3], ".T .T .T .T .T ");
    ps6.grid[3][w6] = '\0';
    strcpy(ps6.grid[4], "               ");
    ps6.grid[4][w6] = '\0';
    strcpy(ps6.grid[5], "               ");
    ps6.grid[5][w6] = '\0';
    strcpy(ps6.grid[6], "...............");
    ps6.grid[6][w6] = '\0';
    strcpy(ps6.grid[7], ":::::::::::::::");
    ps6.grid[7][w6] = '\0';
    strcpy(ps6.grid[8], " . . . . . . . ");
    ps6.grid[8][w6] = '\0';
    strcpy(ps6.grid[9], " : : : : : : : ");
    ps6.grid[9][w6] = '\0';

    ParticleSimulator ps6Test;
    assert(initParticleSimulator(&ps6Test, w6, h6) == 0);

    strcpy(ps6Test.grid[0], " . . . . : : : ");
    ps6Test.grid[0][w6] = '\0';
    strcpy(ps6Test.grid[1], " T T T T T:T T ");
    ps6Test.grid[1][w6] = '\0';
    strcpy(ps6Test.grid[2], "    :     :    ");
    ps6Test.grid[2][w6] = '\0';
    strcpy(ps6Test.grid[3], " T  T  T  T  T ");
    ps6Test.grid[3][w6] = '\0';
    strcpy(ps6Test.grid[4], "               ");
    ps6Test.grid[4][w6] = '\0';
    strcpy(ps6Test.grid[5], "               ");
    ps6Test.grid[5][w6] = '\0';
    strcpy(ps6Test.grid[6], "   .  .  .  . .");
    ps6Test.grid[6][w6] = '\0';
    strcpy(ps6Test.grid[7], ":::: :::.: ::::");
    ps6Test.grid[7][w6] = '\0';
    strcpy(ps6Test.grid[8], "::::.:::::.::::");
    ps6Test.grid[8][w6] = '\0';
    strcpy(ps6Test.grid[9], ":::::::::::::::");
    ps6Test.grid[9][w6] = '\0';

    assert(initParticleSimulatorGravity(&ps6) == 0);
    for(i = 0; i < h6; i++) {
        assert(strcmp(ps6.grid[i], ps6Test.grid[i]) == 0);
    }
    assert(printParticleSimulatorState(ps6) == 0);
    assert(printParticleSimulatorState(ps6Test) == 0);
    printf("TEST 2 PASSED\n\n");

    freeParticleSimulatorGrid(&ps6);
    freeParticleSimulatorGrid(&ps6Test);

    ps6.grid = NULL;
    assert(initParticleSimulatorGravity(&ps5) == -1);
    printf("TEST 3 PASSED\n\n");

    ParticleSimulator *ps7 = NULL;
    assert(initParticleSimulatorGravity(ps7) == -1);
    printf("TEST 4 PASSED\n\n");

    printf("##############################################\n\n\n");



    printf("##### TEST freeParticleSimulatorGrid() #####\n\n");

    ParticleSimulator ps8;
    unsigned int w8 = 12;
    unsigned int h8 = 16;

    assert(initParticleSimulator(&ps8, w8, h8) == 0);
    assert(ps8.grid != NULL);
    freeParticleSimulatorGrid(&ps8);
    assert(ps8.grid == NULL);
    printf("TEST 1 PASSED\n\n");

    freeParticleSimulatorGrid(&ps8);
    printf("TEST 2 PASSED\n\n");

    ParticleSimulator *ps9 = NULL;
    freeParticleSimulatorGrid(ps9);
    printf("TEST 3 PASSED\n\n");

    printf("##############################################\n\n\n");



    printf("############### TEST printError() #############\n\n");

    char *msg = "THIS IS A TEST STRING\n";
    printError(msg);
    printf("TEST 1 PASSED\n\n");

    msg = NULL;
    printError(msg);
    printf("TEST 2 PASSED\n\n");

    printError("THIS IS ALSO A TEST STRING\n");
    printf("TEST 3 PASSED\n\n");

    printf("##############################################\n\n\n");



    printf("End of Unit Tests -- All Tests Passed!\n\n");

    return 0;
}
