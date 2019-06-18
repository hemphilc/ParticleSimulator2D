CC		= gcc
CFLAGS 		= -Wall
OBJFILES1 	= ParticleSimulator.o main.o
OBJFILES2 	= ParticleSimulator.o testMain.o
TARGET1 	= ParticleSimulator
TARGET2 	= TestParticleSimulator

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJFILES1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(OBJFILES1)

$(TARGET2): $(OBJFILES2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(OBJFILES2)

clean:
	rm -f $(OBJFILES1) $(TARGET1) *~
	rm -f $(OBJFILES2) $(TARGET2) *~
