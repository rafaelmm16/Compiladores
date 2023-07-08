#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/archive/basic_xml_archive.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>

using namespace std;

//Essa função repete uma string s dada n vezes
string pref(string s, int n){
    string ret;    
    ret.reserve(s.size() * n);
    while(n--)
        ret += s;
    return ret;
}

int main(){
    string expressao;
    vector<string> result;
    long long int resultado = 0;

    boost::regex separa("(\?(DEFINE)(\?'numeros'[1-9]\\d*)(\?'operador'[+|\\-|\\*|/]))((?P>numeros)|(?P>operador)(?P>numeros))+\?");
    boost::regex num("[1-9]\\d*");
    boost::regex op("[+|\\-|\\*|/]"); 
    
    cout << "Digite a expressao: ";
    cin >> expressao;

    if(boost::regex_match(expressao, separa)){
        cout << "Expressao inserida e valida!" << endl;
        //Criando a arvore
        boost::property_tree::ptree pt;

        //Separando os elementos da regex avaliada
        boost::regex_token_iterator<string::iterator> iterador{
            expressao.begin(), expressao.end(), separa, 0
        };
        //criando um iterador para servir de ponto de parada para a recursão
        boost::regex_token_iterator<string::iterator> end;
        
        //percorrendo as ocorrencias e adicionando-as num vetor
        while(iterador != end){
            string temp = *iterador;
            result.push_back(temp);
            *iterador++;
        }

        for (int i=0; i<result.size();i++){
            if(i==0){//add como numero no xml o primeiro elemento                
                pt.add("Exp.Num", result[i]);
                resultado += stoi(result[i]);
            }else{
                /* Enquanto houverem elementos, por conta do modo que foi separado, 
                vai sempre ter um sinal e numero, sabemos que funciona pois a 
                expressao foi validada pela regex. Então percorremos esse 
                elemento da lista de resultados procurando por operador
                */
                boost::regex_token_iterator<string::iterator> sinal{
                    result[i].begin(), result[i].end(), op, 0
                };
                //Adicionamos o sinal ao lado do numero atual na arvore
                pt.add(pref("Exp.", i)+"Op", *sinal);
                //Percorremos esse elemento da lista de resultados procurando por numeros
                boost::regex_token_iterator<string::iterator> numm{
                    result[i].begin(), result[i].end(), num, 0
                };
                //Adicionamos o numero num nivel abaixo na arvore
                pt.add(pref("Exp.", i+1)+"Num", *numm);
                //Calculando o resultado da operação
                if(*sinal=="+"){
                    resultado += stoi(*numm);
                }else if(*sinal=="-"){
                    resultado -= stoi(*numm);
                }else if(*sinal=="*"){
                    resultado *= stoi(*numm);
                }else if(*sinal=="/"){
                    resultado /= stoi(*numm);
                }
            }
        }

        boost::property_tree::write_xml("resultado.xml", pt);
        cout << "Resultado: " << resultado << endl;
    }else{
        cout << "Expressao inserida e INVALIDA!" << endl;
    }
    return 0;
}