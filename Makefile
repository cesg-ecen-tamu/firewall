TARGET=sim
OBJS=sim.o Simulation.o Schedule.o Schedulable.o
LIBS=
INCLUDES=
COMPILER=g++46
CFLAGS=-Wall -std=c++0x

$(TARGET):$(OBJS)
	$(COMPILER) -o $@ $^ $(LIBS)

%.o:%.cc
	$(COMPILER) $(CFLAGS) -c $^ $(INCLUDES)

clean:
	rm -f *.o
	rm -f $(TARGET)
	rm -rf latex
	rm -rf html

docs:
	doxygen *.h
	doxygen *.cc
