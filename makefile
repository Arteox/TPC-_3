CC = g++
CFLAGS = -ansi -pedantic -Wall -std=c++11
OBJ = Trajet.o TrajetSimple.o TrajetCompose.o Menu.o Catalogue.o
OBJ_TEST = Trajet.o TrajetSimple.o TrajetCompose.o Test.o Catalogue.o
DEPS = Trajet.h TrajetSimple.h TrajetCompose.h Catalogue.h 

Menu.ex: $(OBJ)

Test.ex: $(OBJ_TEST)

%.ex: 
	$(CC) -g $^ -o $@
	#./$@
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --max-stackframe=10485760 ./$@

%.o: %.cpp $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)
	
.PHONY: clean

clean : 
	rm -rf *.ex *.o core
