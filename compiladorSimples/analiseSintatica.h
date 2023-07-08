#include <iostream>

using namespace std;

class analiseSintatica{
    public:

        analiseSintatica();

        void validaExpressao(string);
        void writeResult(string);

        void verify_token(string*, string);

        void remove_spaces(string *expressao);

        void E(string*);
        void E1(string*);
        void E2(string*);
        void E3(string*);

        void R(string*);
        void R1(string*);
        void R2(string*);
        void R3(string*);

        void T(string*);
        void T1(string*);

        void analisadorSintatico(string);

        
};