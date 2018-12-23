.PHONY: clean

Menu.ex: Trajet.o TrajetSimple.o TrajetCompose.o Menu.o Catalogue.o

Test.ex: Trajet.o TrajetSimple.o TrajetCompose.o Test.o Catalogue.o


Test.o: Test.cpp

Trajet.o: Trajet.cpp Trajet.h

TrajetSimple.o: TrajetSimple.cpp TrajetSimple.h

TrajetCompose.o: TrajetCompose.cpp TrajetCompose.h

Catalogue.o: Catalogue.cpp Catalogue.h

%.ex: 
	g++ -g $^ -o $@
	./$@
	#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --max-stackframe=10485760 ./$@

%.o: %.cpp 
	g++ -ansi -pedantic -Wall -std=c++11 -c $< -o $@ 

clean : 
	rm -rf Test.ex Menu.ex *.o core
