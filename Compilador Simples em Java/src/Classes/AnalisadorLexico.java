/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


package Classes;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author paabl
 */
public class AnalisadorLexico {
    
    private final String _codigoFonte;
    private String _codeFonteReduzido = "";
    private List<Token> _tokens;

    public AnalisadorLexico(String _codigoFonte){
       
        this._codigoFonte = _codigoFonte;
        _tokens = new ArrayList<>();
    }
    
    public List<Token> getTokens(){
        removeIncludesEComents();
        addConstantes();
        addPalavrasReservadas();          
        addCadeias();
        addIdentificadores();
        addSeparadoresEOperadoresArit(); //Operadores aritméticos e separadores
        addOpAtribERelac();
        return _tokens;
    }
    
    //Remover qualquer #include<> e qualquer comentário
     private void removeIncludesEComents() {
        _codeFonteReduzido =  _codigoFonte;
        Pattern pattern = Pattern.compile("#(.*?)>"); //Encontra #includes<...>
        Matcher matcher = pattern.matcher(_codigoFonte);
       
        while(matcher.find())
        {
            _codeFonteReduzido =_codeFonteReduzido.replaceAll(matcher.group(0),""); //remove
            pattern.matcher(_codeFonteReduzido);
        } 
        
        //Enconra qualquer string entre // e \n
        pattern = Pattern.compile("//(.*?)\\n"); 
        matcher = pattern.matcher(_codeFonteReduzido);
        
         while(matcher.find())
        {
            _codeFonteReduzido =_codeFonteReduzido.replaceAll(matcher.group(0),"");
            pattern.matcher(_codeFonteReduzido);
        }

    }
    
    private void addConstantes(){
   
        Pattern pattern = Pattern.compile("[-]?[0-9]*\\.?[0-9]+");
        Matcher matcher = pattern.matcher(_codeFonteReduzido);
        while(matcher.find())
        {
           _tokens.add(new Token(matcher.group(0),"CTE",matcher.group(0)));
            _codeFonteReduzido = _codeFonteReduzido.replaceAll(matcher.group(0), "");
        }
    }
     
     String palavrasReservadas;
     private void addPalavrasReservadas(){
        
        palavrasReservadas = "\\sauto|\\sbreak\\s*|\\scase\\s*|\\schar\\s|\\sconst\\s|\\scontinue\\s|\\sdefault\\s|\\sdo\\s*\\s|\\sdouble\\s|\\selse\\s*|"+       
            "\\senum\\s*|\\sextern\\s*|\\sfloat\\s|\\sfor\\s*|\\sgoto\\s*|\\sif\\s*\\s|\\sint\\s|\\slong\\s|\\sregister\\s*|\\sreturn\\s* "+
             "|\\sshort\\s*|\\ssigned\\s*|\\ssizeof\\s*|\\sstatic\\s*|\\sstruct\\s*|\\sswitch\\s*|\\stypedef\\s*|\\sunion\\s*|\\sunsigned\\s|\\svoid\\s|\\svolatile\\s*|\\swhile\\s";
         
        Pattern pattern = Pattern.compile(palavrasReservadas);
        Matcher matcher = pattern.matcher(_codeFonteReduzido);
 
        String aux = "";
        String aux2 = "";
        while(matcher.find()){
            _tokens.add(new Token(matcher.group(0),matcher.group(0),"-"));
           _codeFonteReduzido =  _codeFonteReduzido.replaceAll(matcher.group(0), "");  
        }         
    }
     
     private void addCadeias() {
        Pattern pattern = Pattern.compile("\"(.*?)\"");
        Matcher matcher = pattern.matcher(_codeFonteReduzido);
        
        while(matcher.find())
        {
           _tokens.add(new Token(matcher.group(1),"CADEIA",matcher.group(0)));
           _codeFonteReduzido= _codeFonteReduzido.replace(matcher.group(0), "");
  
        }
    }
     
     
     private void addSeparadoresEOperadoresArit() {

        Pattern pattern = Pattern.compile("\\*|\\+|-|/|%|,|;|(|)|[|]");
        Matcher matcher = pattern.matcher(_codeFonteReduzido);
        
         while(matcher.find())
        {
            switch(matcher.group(0)){
                    case "*": _tokens.add(new Token("*","OP_MULT","MULT"));break;
                    case "+": _tokens.add(new Token("+","OP_ADIT","MAIS"));break;
                    case "-": _tokens.add(new Token("-","OP_ADIT","MENOS"));break;
                    case "/": _tokens.add(new Token("/","OP_MULT","DIV"));break;
                    case "%": _tokens.add(new Token("%","OPMULT","RESTO"));break;
                    case ";": _tokens.add(new Token(";","P_VIRG","-"));break;
                    case ",": _tokens.add(new Token(",","VIRG","-"));break;
                    case "(": _tokens.add(new Token("(","AB_PAR","-"));break;
                    case ")": _tokens.add(new Token(")","FE_PAR","-"));break;
                    case "[": _tokens.add(new Token("[","AB_COL","-"));break;
                    case "]": _tokens.add(new Token("]","FE_COL","-"));break;    
            }  
             
            if(matcher.group(0).equals("*") || matcher.group(0).equals("+"))
                _codeFonteReduzido = _codeFonteReduzido.replaceAll("\\"+matcher.group(0), ""); 
            else
                _codeFonteReduzido = _codeFonteReduzido.replaceAll(matcher.group(0), "");
        }
    }
  
     private void addIdentificadores() {
       
        Pattern pattern = Pattern.compile("[a-zA-Z][a-zA-Z0-9]*");
        Matcher matcher = pattern.matcher(_codeFonteReduzido);
        
        List<String> aux = new ArrayList();
        
        
        
        while(matcher.find())
        {
             
            if(!aux.contains(matcher.group(0)) && !palavrasReservadas.contains(matcher.group(0))){
                
                _tokens.add(new Token(matcher.group(0),"ID",matcher.group(0)));
                aux.add(matcher.group(0));
            }        
        }        

    } 

    private void addOpAtribERelac() {
        
        Pattern pattern = Pattern.compile("/=|\\*=|--|-=|\\+\\+|\\+=|>=|<=|==|!=|>|<");
        Matcher matcher = pattern.matcher(_codeFonteReduzido);
        
         while(matcher.find())
        {
            switch(matcher.group(0)){
                case ">": _tokens.add(new Token(matcher.group(0),"OP_REL","MAIOR"));break;
                case "<": _tokens.add(new Token(matcher.group(0),"OP_REL","MENOR"));break;
                case ">=":_tokens.add(new Token(matcher.group(0),"OP_REL","MAIOR_IG"));break;
                case "<=":_tokens.add(new Token(matcher.group(0),"OP_REL","MENOR_IG"));break;
                case "==":_tokens.add(new Token(matcher.group(0),"OP_REL","IGUAL"));break;
                case "!=":_tokens.add(new Token(matcher.group(0),"OP_REL","DIFERENTE"));break;
                case "+=":_tokens.add(new Token(matcher.group(0),"OP_ATRIB","INCREMENTO"));break;  
                case "++":_tokens.add(new Token(matcher.group(0),"OP_ATRIB","INCREMENTO"));break;  
                case "-=":_tokens.add(new Token(matcher.group(0),"OP_ATRIB","DECREMENTO"));break;  
                case "--":_tokens.add(new Token(matcher.group(0),"OP_ATRIB","DECREMENTO"));break;
                case "*=":_tokens.add(new Token(matcher.group(0),"OP_ATRIB","INCREMENTO"));break;
                case "/=":_tokens.add(new Token(matcher.group(0),"OP_ATRIB","DECREMENTO"));
                
            }
            
            if(matcher.group(0).equals("+=") || matcher.group(0).equals("++") || matcher.group(0).equals("*=") )
                _codeFonteReduzido = _codeFonteReduzido.replaceAll("\\"+matcher.group(0), "");
            else
                _codeFonteReduzido = _codeFonteReduzido.replaceAll(matcher.group(0), "");
        }
         
         pattern = Pattern.compile("=");
         matcher = pattern.matcher(_codeFonteReduzido);
          while(matcher.find())
              _tokens.add(new Token(matcher.group(0),"OP_ATRIB","ATRIB"));
    }    

 
}
