TARGET=sim
OBJS=sim.o Simulation.o Time.o
LIBS=
INCLUDES=
COMPILER=g++46
CFLAGS=-Wall -std=c++0x

$(TARGET):$(OBJS)
	$(COMPILER) -o $@ $^ $(LIBS)

%.o:%.cc
	$(COMPILER) $(CFLAGS) -c $^ $(INCLUDES)

clean:
	rm $(TARGET)
	rm $(OBJS)
