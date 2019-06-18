default: ParticleSimulator

program.o: ParticleSimulator.c ParticleSimulator.h
    gcc -c ParticleSimulator.c -o ParticleSimulator.o

program: ParticleSimulator.o
    gcc ParticleSimulator.o -o ParticleSimulator

clean:
    -rm -f ParticleSimulator.o
    -rm -f ParticleSimulator
