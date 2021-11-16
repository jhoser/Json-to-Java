parametrosCompilacao=-Wall -g#-Wshadow
nomePrograma=GeradorClasses

all: $(nomePrograma)

$(nomePrograma): main.o GeradorClasses.o
	g++ -o $(nomePrograma) main.o GeradorClasses.o $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

GeradorClasses.o: GeradorClasses.hpp GeradorClasses.cpp
	g++ -c GeradorClasses.cpp $(parametrosCompilacao)

#Console.o: Console.hpp Console.cpp
#	g++ -c Console.cpp $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
