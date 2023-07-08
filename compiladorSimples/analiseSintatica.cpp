#include <iostream>
#include <string>
#include <ctype.h>
#include <regex>
#include "analiseSintatica.h"
#include "tokens.h"
#include "parser.h"
#include <cstring>
#include <fstream>

using namespace std;

analiseSintatica::analiseSintatica(){
    //cout << "construindo o analisador..." << endl;
}

Parser parser;
ofstream result;


void analiseSintatica::validaExpressao(string expressao){
    regex expr("(for\\([a-z|A-Z]* in range\\([0[ ]*-[ ]*9]*\\)\\)\\{)|([a-z|A-Z]*[ ]*[=][ ]*[a-z|A-Z|0-9]*;)|(if\\([a-z|A-Z|0-9]+[ ]*[\\+|\\-|<|>|=][=]{0,1}[ ]*[a-z|A-Z|0-9]+\\)\\{)|(\\}[ ]*else if\\([a-z|A-Z|0-9]+[ ]*[\\+|\\-|<|>|=][=]{0,1}[ ]*[a-z|A-Z|0-9]+\\)\\{)|(\\}else[ ]*\\{)|(print\\('[a-z|A-Z|0-9| ]*'\\);)|(print\\('[a-z|A-Z|0-9| ]*'(,[ ]*[a-z|A-Z|0-9]+)*\\);)|\\}");

    if(!regex_match(expressao, expr)){
        //cout << "Sintaxe inválida: " << expressao << endl;
        exit(0);
    }
}

void analiseSintatica::remove_spaces(string *expressao){
    //Erases the spaces
    while(!expressao->empty() && isspace((*expressao)[0])){
        expressao->erase(0, 1);
    }
}

void analiseSintatica::verify_token(string *expressao, string token){

    remove_spaces(expressao);

    if(token == "IDENT"){

        //Erases the whole identifier
        while(!expressao->empty() && IDENT.contains((*expressao)[0])){
            expressao->erase(0, 1);
        }

    } else if(token == "NUM"){

        while(!expressao->empty() && NUM.contains((*expressao)[0])){
            expressao->erase(0, 1);
        }

        //Verifies if there's a ident after a number. ex; 156456aa
        if(!expressao->empty() && IDENT.contains((*expressao)[0])){
            cout << "Found " << (*expressao)[0] << ", expected int" << endl;
            exit(1);
        }

    } else if(token == OPENED_PAR){

        //Verifies if there is a parenthesis
        if(!expressao->empty() && (*expressao)[0] == OPENED_PAR[0]){
            expressao->erase(0, 1);
        } else {
            // Otherwise, it is a sintax error
            cout << "Found " << (*expressao)[0] << ", expected '('" << endl;
            exit(1);
        }  

    } else if(token == CLOSED_PAR){

        //Verifies if there is a parenthesis
        if(!expressao->empty() && (*expressao)[0] == CLOSED_PAR[0]){
            expressao->erase(0, 1);
        } else {
            // Otherwise, it is a sintax error
            cout << "Found " << (*expressao)[0] << ", expected ')'" << endl;
            exit(1);
        }
    } else if(token == OPENED_CHA){

        //Verifies if there is a parenthesis
        if(!expressao->empty() && (*expressao)[0] == OPENED_CHA[0]){
            expressao->erase(0, 1);
        } else {
            // Otherwise, it is a sintax error
            cout << "Found " << (*expressao)[0] << ", expected '{'" << endl;
            exit(1);
        }   

    } else if(token == CLOSED_CHA){

        //Verifies if there is a parenthesis
        if(!expressao->empty() && (*expressao)[0] == CLOSED_CHA[0]){
            expressao->erase(0, 1);
        } else {
            // Otherwise, it is a sintax error
            cout << "Found " << (*expressao)[0] << ", expected '}'" << endl;
            exit(1);
        }

    } else if(token == LOOP){

        //Erases the for of the string
        if(expressao->size() >= 3){
            string token_for = expressao->substr(0, 3);

            if(token_for == LOOP){
                expressao->erase(0, 3);
            } else {
                // Otherwise, it is a lexical error
                exit(1);
            }

        } else {
            // Otherwise, it is a sintax error
            cout << "Found " << (*expressao)[0] << ", expected 'for'" << endl;
            exit(1);
        }

    } else if(token == IN){

        //Erases the in of the string
        if(expressao->size() >= 2){
            string token_for = expressao->substr(0, 2);

            if(token_for == IN){
                expressao->erase(0, 2);
            } else {
                // Otherwise, it is a lexical error
                exit(1);
            }

        } else {
            cout << "Found " << (*expressao)[0] << ", expected 'in'" << endl;
            // Otherwise, it is a sintax error
            exit(1);
        }

    } else if(token == RANGE){

        //Erases the range of the string
        if(expressao->size() >= 5){
            string token_for = expressao->substr(0, 5);

            if(token_for == RANGE){
                expressao->erase(0, 5);
            } else {
                // Otherwise, it is a lexical error
                exit(1);
            }

        } else {
            cout << "Found " << (*expressao)[0] << ", expected 'range'" << endl;
            // Otherwise, it is a sintax error
            exit(1);
        }

    } else if(token == IF){

        //Erases the if of the string
        if(expressao->size() >= 2){
            string token_for = expressao->substr(0, 2);

            if(token_for == IF){
                expressao->erase(0, 2);
            } else {
                // Otherwise, it is a lexical error
                cout << "Found " << (*expressao)[0] << ", expected 'if'" << endl;
                exit(1);
            }

        } else {
            // Otherwise, it is a sintax error
            exit(1);
        }

    } else if(token == ELSE){

        //Erases the else of the string
        if(expressao->size() >= 4){
            string token_for = expressao->substr(0, 4);

            if(token_for == ELSE){
                expressao->erase(0, 4);
            } else {
                // Otherwise, it is a lexical error
                exit(1);
            }

        } else {
            // Otherwise, it is a sintax error
            cout << "Found " << (*expressao)[0] << ", expected 'else'" << endl;
            exit(1);
        }

    } else if(token == PRINT){

        //Erases the print of the string
        if(expressao->size() >= 5){
            string token_for = expressao->substr(0, 5);

            if(token_for == PRINT){
                expressao->erase(0, 5);
            } else {
                // Otherwise, it is a lexical error
                exit(1);
            }

        } else {
            // Otherwise, it is a sintax error
            exit(1);

            cout << "Found " << (*expressao)[0] << ", expected 'print'" << endl;
        }

    } else if(token == SEMICOLON){

        //Verifies if there is a semicolon
        if(!expressao->empty() && (*expressao)[0] == SEMICOLON[0]){
            expressao->erase(0, 1);
        } else {
            cout << "Erro léxico. Faltou ponto e virgula." << endl;
            exit(1);
        }

    } else if(token == EQUAL){

        //Verifies if there is an equal
        if(!expressao->empty() && (*expressao)[0] == EQUAL[0]){
            expressao->erase(0, 1);
        } else {
            // Otherwise, it is a sintax error
            cout << "Found " << (*expressao)[0] << ", expected =" << endl;
            exit(1);
        }

    } else if(token == "COMP"){

        //Verifies possible conditionals
        if(!expressao->empty() && expressao->size() >= 2){

            if(COMP_GREATER_E.contains((*expressao).substr(0, 2)) || 
                COMP_LOWER_E.contains((*expressao).substr(0, 2)) || 
                COMP_EQUAL.contains((*expressao).substr(0, 2))){
                expressao->erase(0, 2);
            } else if(COMP_GREATER[0] == (*expressao)[0] || COMP_LOWER[0] == (*expressao)[0]){
                expressao->erase(0, 1);
            } else {
                cout << "Found " << (*expressao)[0] << ", expected conditionals" << endl;
                exit(1);
            }
        }

    } else if(token == Q_MARKS){

        //Verifies strings inside a print
        if(!expressao->empty() && (*expressao)[0] == Q_MARKS[0]){
            expressao->erase(0, 1);
        } else {
            cout << "\"" << (*expressao)[0] << ", expected quotation marks" << endl;
            exit(1);
        }

        //Erases the whole string
        while(!expressao->empty() && !((*expressao)[0] == Q_MARKS[0])){
            expressao->erase(0, 1);
        }

        if((*expressao)[0] == Q_MARKS[0]){
            expressao->erase(0, 1);
        }

    } else if(token == COMMA){

        //Verifies if there is a semicolon
        if(!expressao->empty() && (*expressao)[0] == COMMA[0]){
            expressao->erase(0, 1);
        } else {
            cout << "Found " << (*expressao)[0] << ", expected comma" << endl;
            exit(1);
        }

    }
    remove_spaces(expressao);
}


void analiseSintatica::T(string *texto){
    remove_spaces(texto);
    string expressao = *texto;
    string variable = "";

    if(isdigit((*texto)[0])){

        verify_token(texto, "NUM");

        //Writes on file
        while(!expressao.empty() && NUM.contains((expressao)[0])){
            variable.push_back((expressao)[0]);
            expressao.erase(0, 1);
        }
        writeResult(parser.translateToken(variable, NUM));

    } else if(IDENT.contains((*texto)[0])){
        

        verify_token(texto, "IDENT");

        //Writes on file
        while(!expressao.empty() && IDENT.contains((expressao)[0])){
            variable.push_back((expressao)[0]);
            expressao.erase(0, 1);
        }

        writeResult(parser.translateToken(variable, "IDENT WITHOUT INT"));

    } else {
        cout << "Found " << (*texto)[0] << ", expected int or char" << endl;
        exit(1);
    }

}

void analiseSintatica::T1(string *texto){
    remove_spaces(texto);


    if(texto->size() >= 4 && texto->substr(0, 4) == ELSE){
        verify_token(texto, ELSE);

        //Writes on file
        writeResult(parser.translateToken(ELSE + " ", ELSE));


        //Verifies if there is another if
        if (texto->size() >= 2 && texto->substr(0, 2) == IF){
            E(texto);
        } else {
            verify_token(texto, OPENED_CHA);

            //Writes on file
            writeResult(parser.translateToken(OPENED_CHA, OPENED_CHA));

            E(texto);

            verify_token(texto, CLOSED_CHA);

            //Writes on file
            writeResult(parser.translateToken(CLOSED_CHA, CLOSED_CHA));

            E(texto);
        }
    } else {
        E(texto);
    }
}

void analiseSintatica::R(string *texto){
    remove_spaces(texto);

    T(texto);
    verify_token(texto, SEMICOLON);

    //Writes on file
    writeResult(parser.translateToken(";", SEMICOLON));

    E(texto);
}

void analiseSintatica::R1(string *texto){
    remove_spaces(texto);

    verify_token(texto, OPENED_CHA);

    //Writes on file
    writeResult(parser.translateToken("{", OPENED_CHA));

    E(texto);

    //Writes on file
    writeResult(parser.translateToken("}", CLOSED_CHA));

    verify_token(texto, CLOSED_CHA);
    E(texto);
}

void analiseSintatica::R2(string *texto){
    remove_spaces(texto);

    //Writes on file
    writeResult(parser.translateToken(OPENED_CHA, OPENED_CHA));

    verify_token(texto, OPENED_CHA);
    E(texto);

    //Writes on file
    writeResult(parser.translateToken(CLOSED_CHA, CLOSED_CHA));
    
    verify_token(texto, CLOSED_CHA);
    T1(texto);
}

void analiseSintatica::R3(string *texto){
    remove_spaces(texto);


    if(texto->size() > 0 && (*texto)[0] == COMMA[0]){
        verify_token(texto, COMMA);

        //writes on a file;
        writeResult(parser.translateToken(" << ", COMMA));

        T(texto);
        R3(texto);
    }
}


void analiseSintatica::E(string *texto){
    string expressao = *texto;
    string variable = "";

    if(texto->empty()){
        cout << "No errors found." << endl;
    }

    remove_spaces(texto);

    if(texto->size() >= 3 && LOOP.contains(texto->substr(0, 3))){

        verify_token(texto, LOOP);
        verify_token(texto, OPENED_PAR);
        E1(texto);
        verify_token(texto, CLOSED_PAR);

        //Writes on file
        writeResult(parser.translateToken(expressao, LOOP));

        R1(texto);

    } else if(texto->size() >= 2 && IF.contains(texto->substr(0, 2))){
        verify_token(texto, IF);

        //Writes on file
        writeResult(parser.translateToken(IF, IF));

        verify_token(texto, OPENED_PAR);

        //Writes on file
        writeResult(parser.translateToken(OPENED_PAR, OPENED_PAR));

        E2(texto);

        verify_token(texto, CLOSED_PAR);

        //Writes on file
        writeResult(parser.translateToken(CLOSED_PAR, CLOSED_PAR));

        R2(texto);
    } else if(texto->size() >= 5 && PRINT.contains(texto->substr(0, 2))){
        verify_token(texto, PRINT);

        //Writes on file
        writeResult(parser.translateToken("cout <<", PRINT));

        verify_token(texto, OPENED_PAR);

        E3(texto);
        verify_token(texto, CLOSED_PAR);

        verify_token(texto, SEMICOLON);

        //Writes on file
        writeResult(parser.translateToken(SEMICOLON, SEMICOLON));

        E(texto);
    }

    if(IDENT.contains((*texto)[0])){

        verify_token(texto, "IDENT");

        //Writes on file
        while(!expressao.empty() && IDENT.contains((expressao)[0])){
            variable.push_back((expressao)[0]);
            expressao.erase(0, 1);
        }

        writeResult(parser.translateToken(variable, "IDENT"));

        verify_token(texto, EQUAL);

        //Writes on file
        writeResult(parser.translateToken("=", EQUAL));
        R(texto);
    }
}

void analiseSintatica::E1(string *texto){

    remove_spaces(texto);

    verify_token(texto, "IDENT");
    verify_token(texto, IN);
    verify_token(texto, RANGE);
    verify_token(texto, OPENED_PAR);
    verify_token(texto, "NUM");
    verify_token(texto, CLOSED_PAR);

}

void analiseSintatica::E2(string *texto){

    remove_spaces(texto);

    T(texto);

    string expressao = *texto;
    verify_token(texto, "COMP");

    //Writes on file

    

    if(expressao.substr(0, 2) == "==" || expressao.substr(0, 2) == ">=" || expressao.substr(0, 2) == "<=")
        writeResult(parser.translateToken(expressao.substr(0, 2), "COMP"));
    else{
        writeResult(parser.translateToken(expressao.substr(0, 1), "COMP"));
    }

    T(texto);
}

void analiseSintatica::E3(string *texto){


    remove_spaces(texto);

    string expressao = *texto;
    verify_token(texto, Q_MARKS);

    //Writes on file
    int count = 0;
    string variable = "";

    while(count < 2){

        if(expressao[0] == Q_MARKS[0]){
            count++;
        }

        variable.push_back(expressao[0]);

        expressao.erase(0, 1);

    }

    writeResult(parser.translateToken(variable, "STRING"));

    R3(texto);

}

void analiseSintatica::analisadorSintatico(string texto){

    string linha = "";

    for(int i = 0; i < texto.length(); i++){



        if(texto[i] == '\n' || texto[i] == '\0'){
            //cout << linha << "====";
            //validaExpressao(linha);
            linha = "";
        }else{
            linha += texto[i];
        }
    }
    //Starts the analysis

    result.open("result.cpp");

    if( !result ) { // file couldn't be opened
      cerr << "Error: file could not be opened" << endl;
      exit(1);
    }

    //Add file c++

    writeResult(parser.translateToken(" #include <iostream>\n", "STRING"));
    writeResult(parser.translateToken(" using namespace std; ", "STRING"));
    writeResult(parser.translateToken(" int main(){ ", "STRING"));


    E(&texto);

    writeResult(parser.translateToken(" return 0;}", "STRING"));
    result.close();
}

void analiseSintatica::writeResult(string expressao){
    result << expressao;
}