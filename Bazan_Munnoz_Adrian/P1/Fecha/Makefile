CXX=g++
CXXFLAGS=-std=c++0x
OBJETOS1= fecha.o test-auto.o
OBJETOS2= fecha.o test-consola.o

all: auto consola

auto:$(OBJETOS1)
	$(CXX) -o $@ $(LDFFLAGS) $(OBJETOS1)

consola:$(OBJETOS2)
	$(CXX) -o $@ $(LDFFLAGS) $(OBJETOS2)
check: fecha_check 
	./$< fecha.cpp -- -std=c++11

fecha.o: fecha.h

prueba-auto.o: fct.h


clean:
	$(RM) auto $(OBJETOS1) core *~
	$(RM) consola $(OBJETOS2) core *~
