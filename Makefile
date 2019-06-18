#default: ParticleSimulator

#program.o: ParticleSimulator.c ParticleSimulator.h
#	gcc -c ParticleSimulator.c -o ParticleSimulator.o

#program: ParticleSimulator.o
#	gcc ParticleSimulator.o -o ParticleSimulator

#clean:
#	-rm -f ParticleSimulator.o
#	-rm -f ParticleSimulator

CC 			= gcc
CFLAGS 		= -Wall
LDFLAGS 	=
OBJFILES 	= ParticleSimulator.o main.o
TARGET 		= ParticleSimulator

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
