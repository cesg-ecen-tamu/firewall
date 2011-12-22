TARGET=sim
OBJS=sim.o Simulation.o
LIBS=
INCLUDES=
COMPILER=g++
CFLAGS=-Wall

$(TARGET):$(OBJS)
	$(COMPILER) -o $@ $^ $(LIBS)

%.o:%.cc
	$(COMPILER) $(CFLAGS) -c $^ $(INCLUDES)

clean:
	rm $(TARGET)
	rm $(OBJS)
