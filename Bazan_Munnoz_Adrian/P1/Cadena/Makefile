CXX=g++
CXXFLAGS=-std=c++0x
OBJETOS1= cadena.o test-auto.o
OBJETOS2= cadena.o test-consola.o

all: auto consola

auto:$(OBJETOS1)
	$(CXX) -o $@ $(LDFFLAGS) $(OBJETOS1)

consola:$(OBJETOS2)
	$(CXX) -o $@ $(LDFFLAGS) $(OBJETOS2)
check: cadena_check 
	./$< cadena.cpp -- -std=c++11

fecha.o: cadena.h

prueba-auto.o: fct.h


clean:
	$(RM) auto $(OBJETOS1) core *~
	$(RM) consola $(OBJETOS2) core *~
