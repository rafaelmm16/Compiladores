#include<string>
#include <iostream>
#include <boost/regex.hpp>
#define endl '\n';

using namespace std;

int main(void){
	int result;	
	string input;

	cin >> input;
	cout << "Expressao digitada: " << input << endl;
	
	/*
	    Tentei aplicar a tokenização como mostrada no outro arquivo, mas pelo jeito
que tá a expressão regular, ele retornou toda a expressão como token (pelo que entendi).
	    Como a expressão só permite os caracteres numéricos e de operações, se ela for compatível com a expressão regular, ela automaticamente passou pela análise léxica e sintática.
	    Situação parecida aconteceu com o resultado das operações. Até seria possível implementar por fora, mas como não consegui alcançar com o boost, preferi não incluir.
	*/
	boost::regex expr{"(\\-{0,1}[1-9][0-9]*([+|\\-|\\*|/][1-9][0-9]*)+)"};

	cout << "Passou na analise lexica/sintatica: ";
	cout << boolalpha << boost::regex_match(input, expr) << endl;

	return 0;
}


