/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Classes;

import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author paabl
 */
public class Main {

    public static void main(String[] args) {
    
//        String _codigo = "#include <stdio.h>\n" +
//"\n" +
//"int main()\n" +
//"{\n" +
//"    char line[150];\n" +
//"    int i, vowels, consonants, digits, spaces;\n" +
//"\n" +
//"    vowels =  consonants = digits = spaces = 0;\n" +
//"\n" +
//"    printf(\"Enter a line of string: \");\n" +
//"    scanf(\"%[^\\n]\", line);\n" +
//"\n" +
//"    for(i=0; line[i]!='\\0'; ++i)\n" +
//"    {\n" +
//"        if(line[i]=='a' || line[i]=='e' || line[i]=='i' ||\n" +
//"           line[i]=='o' || line[i]=='u' || line[i]=='A' ||\n" +
//"           line[i]=='E' || line[i]=='I' || line[i]=='O' ||\n" +
//"           line[i]=='U')\n" +
//"        {\n" +
//"            ++vowels;\n" +
//"        }\n" +
//"        else if((line[i]>='a'&& line[i]<='z') || (line[i]>='A'&& line[i]<='Z'))\n" +
//"        {\n" +
//"            ++consonants;\n" +
//"        }\n" +
//"        else if(line[i]>='0' && line[i]<='9')\n" +
//"        {\n" +
//"            ++digits;\n" +
//"        }\n" +
//"        else if (line[i]==' ')\n" +
//"        {\n" +
//"            ++spaces;\n" +
//"        }\n" +
//"    }\n" +
//"\n" +
//"    printf(\"Vowels: %d\",vowels);\n" +
//"    printf(\"\\nConsonants: %d\",consonants);\n" +
//"    printf(\"\\nDigits: %d\",digits);\n" +
//"    printf(\"\\nWhite spaces: %d\", spaces);\n" +
//"\n" +
//"    return 0;\n" +
//"}";
        
//        String[] ctes = _codigo.split("\\D+");
//        for (int i = 0; i < ctes.length; i++){
//           System.out.println(ctes[i]);      
//       }
        
        
        
       //AnalisadorLexico a = new AnalisadorLexico(_codigo);
       //System.out.print(String.format("Átomo" + "          " + "Tipo"+ "          " + "Atributo" +'\n'));
       //System.out.print(a.getTokens());
       
       
//       String[] words = _codigo.split("\\s+");
//       String words2 = "";
//       int a = 0;
//         String[] _wordAux1  = _codigo.split("\\s+");
//         for (String wordAux1 : _wordAux1) {
//            wordAux1 = wordAux1.replaceAll("\\w", "");
//            System.out.println(wordAux1); 
//         
//         }
//            
            
            
//       words = words2.split("");
//        for (int i = 0; i < words.length; i++){
//          System.out.println(words[i]);
//       }  
//       
//       String[] _wordAux = words.clone();
//       for (int i = 0; i < _wordAux.length; i++){
//           System.out.println(_wordAux[i]);      
//       }
       
//       for (int i = 0; i < words.length; i++) {
//            // You may want to check for a non-word character before blindly
//            // performing a replacement
//            // It may also be necessary to adjust the character class
//            //words[i] = words[i].replaceAll("[^\\w]", "");  
//       }
//       
//       for (int i = 0; i < words.length; i++){
//           if(words[i].matches("\\d"))
//                System.out.println(words[i]);     
//           //System.out.println(words[i]);      
//       }
        

        // String mydata = "some string with 'the data i want' inside";
//        Pattern pattern = Pattern.compile("[a-zA-Z][a-zA-Z0-9]*");
//        Matcher matcher = pattern.matcher(_codigo);
//        while(matcher.find())
//        {
//            System.out.println(matcher.group(0));
//        }
//        String[] words = _codigo.split("\\s+");
//         for (int i = 0 ; i < words.length ; i++){
//         
//              System.out.println(words[i]);
//         }
//    
         
         Pattern pattern = Pattern.compile("for\\s*");
        Matcher matcher = pattern.matcher("for(int i = 10 ; i < 50; i++)");
 
        String aux = "";
        String aux2 = "";
        while(matcher.find())
        {
            aux += matcher.group(0);
           
            
        }
        
        System.out.println(aux);
}}
