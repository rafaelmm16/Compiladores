CFLAGS=-O0 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -std=c++2b
LIBS=-lm
EXECUTAVEL=compilador

all: $(EXECUTAVEL)

$(EXECUTAVEL): analiseSintatica.o compiladorSimples.o parser.o
	g++ analiseSintatica.o compiladorSimples.o parser.o $(LIBS) -o $(EXECUTAVEL)

compiladorSimples.o: compiladorSimples.cpp
	g++ $(CFLAGS) -c compiladorSimples.cpp

analiseSintatica.o: analiseSintatica.cpp
	g++ $(CFLAGS) -c analiseSintatica.cpp

parser.o: parser.cpp
	g++ $(CFLAGS) -c parser.cpp

clean:
	rm -rf *.o $(EXECUTAVEL)

memcheck: $(EXECUTAVEL)
	valgrind --tool=memcheck --leak-check=full ./$(EXECUTAVEL)

run: $(EXECUTAVEL)
	./$(EXECUTAVEL)