all: main.o MyPSOBehavior.o Particle.o PSO.o
	g++ -o PSO_Demo main.o MyPSOBehavior.o Particle.o PSO.o
main.o: main.cpp
	g++ -c main.cpp
MyPSOBehavior.o: MyPSOBehavior.h MyPSOBehavior.cpp
	g++ -c MyPSOBehavior.cpp
Particle.o: Particle.h Particle.cpp
	g++ -c Particle.cpp
PSO.o: PSO.h PSO.cpp
	g++ -c PSO.cpp
clean:
	rm -f *.o PSO_Demo
