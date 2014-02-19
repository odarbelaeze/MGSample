OBJECTS = Atom.o VirtualGrain.o main.o
FLAGS = -O2

main: $(OBJECTS)
	g++ -std=c++11 $(FLAGS) -o main $(OBJECTS)

main.o: main.cc
	g++ -std=c++11 $(FLAGS) -c $<

%.o: %.cc %.h
	g++ -std=c++11 $(FLAGS) -c $<

profile: FLAGS=-pg
profile: main
	@true
.PHONY: profile

debug: FLAGS=-g3
debug: main
	@true
.PHONY: debug

clear:
	rm *.o main
