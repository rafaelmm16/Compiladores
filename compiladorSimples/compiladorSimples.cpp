#include <iostream>
#include <string>
#include <ctype.h>
#include <regex>
#include "analiseSintatica.h"

using namespace std;

string carregaArq(){
    FILE *arq = fopen("entrada.txt", "r");

    string texto;
    char c = ' ';

    while(!feof(arq)){
        fscanf(arq, "%c", &c);

        if(c != '\n'){
            texto += c;
        }
            
    }

    fclose(arq);

    return texto.erase(texto.size() - 1, 1);
}

string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(){

    analiseSintatica analise;

    string texto = carregaArq();

    analise.analisadorSintatico(texto);

    system("g++ result.cpp");
    cout << exec("./a.out") << endl;

    return 0;
}