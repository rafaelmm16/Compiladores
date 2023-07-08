#include <iostream>
#include <string>
#include <ctype.h>
#include <regex>
#include "analiseSintatica.h"
#include "tokens.h"
#include <cstring>

#include "parser.h"

using namespace std;

Parser::Parser(){
}

string Parser::translateToken(string expressao, string token){
	analiseSintatica analise;
	string translatedToken;

	//Translate tokens to c++

	if(token == "IDENT"){
		translatedToken = "int " + expressao;
	} else if(token == LOOP){

		//Takes a complete for loop
		translatedToken = "for";
		analise.verify_token(&expressao, LOOP);

		translatedToken += "(";
		analise.verify_token(&expressao, OPENED_PAR);
		

		string variable = "";
		//gets the variable
		while(!isspace(expressao[0])){
			variable.push_back((expressao)[0]);
			expressao.erase(0, 1);
		}

		//Variable starts with zero
		translatedToken = translatedToken + "int " + variable + " = 0";

		//Removes the IN
		analise.verify_token(&expressao, IN);

		//Removes the Range
		analise.verify_token(&expressao, RANGE);

		//Removes the opened par
		analise.verify_token(&expressao, OPENED_PAR);

		string number = "";
		//gets the number
		while(!((expressao)[0] == ')')){
			number.push_back((expressao)[0]);
			expressao.erase(0, 1);
		}

		//Adds a for number with the specified number
		translatedToken = translatedToken + "; " + variable + " < " + number + ";" + "i++" + ")";

	} else {
		translatedToken += expressao;
	}

	return translatedToken;
}