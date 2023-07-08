/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Classes;
/**
 *
 * @author paabl
 */

public class Token {  
    private String _atomo;
    private String _tipo;
    private String _atributo;      

    public Token(String _atomo, String _tipo, String _atributo) {
        this._atomo = _atomo;
        this._tipo = _tipo;
        this._atributo = _atributo;
    }

    @Override
    public String toString() {
        return String.format(_atomo + "     " +_tipo + "     " + _atributo +'\n');
    }

    public String getAtomo() {
        return _atomo;
    }

    public String getTipo() {
        return _tipo;
    }

    public String getAtributo() {
        return _atributo;
    }
 
}
